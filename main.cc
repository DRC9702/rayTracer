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
#include "pointLight.h"


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

void writePixels(char* outputName){
	int w = cam.getNx();
	int h = cam.getNy();
	Array2D<Rgba> p (h,w);
	p.resizeErase(h,w);

	cout << "Progress: |0|";
	        for(int i=0; i < h; i++){
				for(int j=0; j < w; j++) {
					ray pixelRay = cam.generateRayForPixel(j,h-1-i);
					bool assigned = false;
					int index = -1;
					double minT = -1;
					for(unsigned int k=0; k < surfaceList.size(); k++){
						//We need to flip the y axis orientation because while our math uses a traditional x+ right, y+ up grid, the pixels are created with x+ right,y+ down
						//In this loop, I will represent the pixel index from the bottom, so since we want pixel index from the top, we calculate our rays with (h-i)
						//Another note: i is the vertical index, j is the horizontal index, so compared to the book, we must call generateRayForPixel with (j, h-i);
						double tempT = surfaceList.at(k) -> intersectT(pixelRay);
						if(	(!assigned && tempT > 0) || (assigned && tempT < minT && tempT != -1)	){
							assigned=true;
							index = k;
							minT = tempT;
						}
					}
					Rgba &px = p[i][j];
					if(assigned)
					{
						surface* surface = surfaceList.at((unsigned int)index);
						material* mat = materialList.at(surface->getMaterialIndex());
						point pnt = pixelRay.getPointFromT(minT);
						rgbTriple pixelLight;

						rgbTriple shadeLight = mat-> shading(pnt, cam, index, surfaceList, pointLightList);

//						for(unsigned int k=0; k < pointLightList.size(); k++){
//							//lambertian shading
//							rgbTriple lambertianShading;
//							//double templsr, templsg, templsb;
//							mat->lambertianShading(pnt, index, surfaceList, pointLightList.at(k), lambertianShading);
//							pixelLight.addRGBFrom(lambertianShading);
//							//specular shading
//							rgbTriple specularShading;
//							//double tempssr, tempssg, tempssb;
//							mat->specularShading(pnt, cam, index, surfaceList, pointLightList.at(k), specularShading);
//							pixelLight.addRGBFrom(specularShading);
//
//						}


						pixelLight.addRGBFrom(shadeLight);
						px.r = pixelLight.getR(); px.g = pixelLight.getG(); px.b =pixelLight.getB();
//						px.r=mat->dr; px.g=mat->dg; px.b=mat->db;

					}


					else
					{
						px.r=0; px.g=0; px.b=0;
					}

				}
	    		writeRgba (outputName, &p[0][0], w, h);
				//writeRgba ("hw3.exr", &p[0][0], w, h);
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

    //cout << "no error before parsing" << endl;
    readscene RS;
    RS.parseSceneFile (argv[1]);
    RS.getData(&surfaceList, &materialList, &pointLightList, &cam);

    //cout << cam.nx << "\t" << cam.ny << endl;



    //cout << surfaceList -> at(0) -> intersectT(ray (0, 13.67, 0, 0, 0, -1)) << endl;
	//cout << surfaceList.at(0) -> intersectT(ray (0, 13.67, 0, 0, 0, -1)) << endl;


    try{
    	writePixels(argv[2]);
    }
    catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    //Free surfaces pointed to in surface list
    for(surface* s : surfaceList){
    	delete(s);
    }
    //Free materials pointed to in material list
    for(material* m : materialList){
    	delete(m);
    }
    //Free pointLights pointed to in pointLight list
    for(pointLight* p : pointLightList){
    	delete(p);
    }

    return 0;
}
