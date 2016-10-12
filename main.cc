#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
//My classes
#include "surface.h"
#include "sphere.h"
#include "plane.h"
#include "camera.h"
#include "material.h"
#include "ray.h"
#include "exr_test.h"

#include "readscene.h"
#include "vector.h"

#include <cstdlib>	//Nope! Don't need this!

using namespace std;

std::vector<surface*> surfaceList = std::vector<surface*>();
std::vector<material*> materialList = std::vector<material*>();
std::vector<pointLight*> pointLightList = std::vector<pointLight*>();
camera cam;

void writeRgba (const char fileName[], const Rgba *pixels, int width, int height)
{
    //
    // Write an RGBA image using class RgbaOutputFile.
    //
    //	- open the file
    //	- describe the memory layout of the pixels
    //	- store the pixels in the file
    //
    RgbaOutputFile file (fileName, width, height, WRITE_RGBA);
    file.setFrameBuffer (pixels, 1, width);
    file.writePixels (height);
}

void writePixels(){
	int w = cam.nx;
	int h = cam.ny;
	Array2D<Rgba> p (h,w);
	p.resizeErase(h,w);

	cout << "Progress: |0|";
	        for(int i=0; i < h; i++){
				for(int j=0; j < w; j++) {
					ray pixelRay = cam.generateRayForPixel(j,h-i);
					bool assigned = false;
					int index = -1;
					float minT = -1;
					for(unsigned int k=0; k < surfaceList.size(); k++){
						//We need to flip the y axis orientation because while our math uses a traditional x+ right, y+ up grid, the pixels are created with x+ right,y+ down
						//In this loop, I will represent the pixel index from the bottom, so since we want pixel index from the top, we calculate our rays with (h-i)
						//Another note: i is the vertical index, j is the horizontal index, so compared to the book, we must call generateRayForPixel with (j, h-i);
						if(	(!assigned && surfaceList.at(k) -> intersectT(pixelRay) > 0) || (assigned && surfaceList.at(k) -> intersectT(pixelRay) < minT	&& surfaceList.at(k) -> intersectT(pixelRay) != -1	)	){
							assigned=true;
							index = k;
							minT = surfaceList.at(k) -> intersectT(cam.generateRayForPixel(j,h-i));
						}
					}
					Rgba &px = p[i][j];
					if(assigned)
					{
						surface* surface = surfaceList.at((unsigned int)index);
						material* mat = materialList.at(surface->getMaterialIndex());
						point pnt = pixelRay.getPointFromT(minT);
						float ldr=0, ldg=0, ldb=0;
						for(unsigned int k=0; k < pointLightList.size(); k++){
							//lambertian shading
							float templsr, templsg, templsb;
							pointLightList.at(k)->lambertianShading(pnt, surface, mat, templsr, templsg, templsb);
							ldr += templsr;
							ldg += templsg;
							ldb += templsb;
							//specular shading
							float tempssr, tempssg, tempssb;
							pointLightList.at(k)->specularShading(pnt, pixelRay, surface, mat, tempssr, tempssg, tempssb);
							ldr += tempssr;
							ldg += tempssg;
							ldb += tempssb;
							
						}

						px.r=ldr; px.g=ldg; px.b=ldb;
//						px.r=mat->dr; px.g=mat->dg; px.b=mat->db;
					}
					else
					{
						px.r=0; px.g=0; px.b=0;
					}

				}
	    		//writeRgba (argv[2], &p[0][0], w, h);
				writeRgba ("hw1.exr", &p[0][0], w, h);
				if(i%(h/10)==0 && i!=0)
						cout << "|" << i/(h/10)*10 << "|" ;
			}
			cout << "|100|" << endl;



			//cout << "Didn't die while editing the pixels." << endl;

			cout << "Finished writing file" << endl;
}

int main (int argc, char *argv[])
{

    if (argc != 3) {
        cerr << "useage: raytra scenefilename writefilename" << endl;
        return -1;
    }

    cout << "no error before parsing" << endl;
    readscene RS;
    RS.parseSceneFile (argv[1]);
    RS.getData(&surfaceList, &materialList, &pointLightList, &cam);

    //cout << cam.nx << "\t" << cam.ny << endl;



    //cout << surfaceList -> at(0) -> intersectT(ray (0, 13.67, 0, 0, 0, -1)) << endl;
	//cout << surfaceList.at(0) -> intersectT(ray (0, 13.67, 0, 0, 0, -1)) << endl;


    try{
    	writePixels();
    }
    catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }





    return 0;
}
