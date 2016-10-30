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
#include "Vector.h"
#include "pointLight.h"


#include <cstdlib>	//Nope! Don't need this!
#include <limits>

using namespace std;

std::vector<surface*> surfaceList = std::vector<surface*>();
std::vector<material*> materialList = std::vector<material*>();
std::vector<pointLight*> pointLightList = std::vector<pointLight*>();
camera cam;
ambientLight ambLight = ambientLight(.876,0,0);

static material *BACKSIDE_MATERIAL= new material(1, 1, 0, 0, 0, 0, 0, 0, 0, 0);

static int RECURSION_LIMIT = 20;

static int PRIMARY_RAY = 0; //This one tells you when to do ambient shading
static int REGULAR_RAY = 1;
static int SHADOW_RAY = 2;

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



rgbTriple L (ray inputRay, double minT, double maxT, int recursionLimit, int rayType, pointLight light){

	if(recursionLimit==0)
		return rgbTriple(0,0,0);

	  if (rayType == SHADOW_RAY) {
		  //bool intersectionFound = false; //I don't think I need it here at all
		  for(unsigned int k=0; k < surfaceList.size(); k++){
			  double tempT = surfaceList.at(k) -> intersectT(inputRay);
			  if (tempT > minT && tempT < maxT){
				  return rgbTriple(0,0,0);
			  }
		  }
		  return light.getLightValue();
	  }

	  //Get closest intersection with scene
	  bool intersectionFound = false;
	  int index = -1;
	  double closestT;
	  for(unsigned int k=0; k < surfaceList.size(); k++){
		  double tempT = surfaceList.at(k) -> intersectT(inputRay);
		  if(tempT < minT || tempT > maxT){
			  continue;
		  }
		  if(	(!intersectionFound && tempT > 0) || (intersectionFound && tempT < closestT && tempT != -1)	){
			  intersectionFound = true;
			  index = k;
			  closestT = tempT;
		  }
	  }
	  if(!intersectionFound)
		  return rgbTriple(0,0,0);

	  point p = inputRay.getPointFromT(closestT);

	  //We need these to determine which material to use.
	  surface *surfacePointer = surfaceList.at(index);
	  Vector surfaceNormal = surfacePointer ->getSurfaceNormal(p);
	  material *materialPointer = materialList.at(surfacePointer->getMaterialIndex());
	  bool isFlipped = surfaceNormal.dotProduct(inputRay.getDir()) > 0; //Check if you're hitting the backside

	  Vector tempSurfaceNormal = (isFlipped)? surfaceNormal.scalarMultiply(-1) : surfaceNormal;
	  materialPointer = (isFlipped) ? BACKSIDE_MATERIAL : materialPointer;

	  //Do lighting and shading calcuation now?
	  rgbTriple R;
	  for(unsigned int k=0; k < pointLightList.size(); k++){
		  Vector pToLight = pointLightList.at(k)->getPosition().subtract(p);
		  double s_maxT = pToLight.getMagnitude();
		  ray s_ray = ray(p,pToLight);
		  rgbTriple L_rgb = L(s_ray, 0.0001, s_maxT, 1, SHADOW_RAY, *pointLightList.at(k));
		  if(!L_rgb.isBlank()){
			  rgbTriple lambertianShading;
			  rgbTriple specularShading;
			  materialPointer -> lambertianShadingForPointLight(p, pointLightList.at(k), lambertianShading, tempSurfaceNormal);
			  materialPointer -> specularShadingForPointLight(p, pointLightList.at(k), specularShading, tempSurfaceNormal, inputRay.getDir().scalarMultiply(-1));
			  R.addRGBFrom(lambertianShading);
			  R.addRGBFrom(specularShading);
		  }
	  }

	  if(rayType == PRIMARY_RAY){
		  rgbTriple ambientShading;
		  materialPointer -> shadingFromAmbientLight(ambLight,ambientShading);
		  R.addRGBFrom(ambientShading);
	  }

//	  cout << "r" << materialPointer -> getIdealSpec().getR() << "g" << materialPointer -> getIdealSpec().getG() << endl;

	  if(materialPointer -> getIdealSpec().isBlank()){
		  return R;
	  }
	  else{
//		  cout << "reflections happening" << endl;
		  ray reflectedRay = ray(p, inputRay.getDir().subtract(		tempSurfaceNormal.scalarMultiply(2*inputRay.getDir().dotProduct(tempSurfaceNormal))		)	);
		  rgbTriple newL_rgb = L(reflectedRay, 0.0001, INFINITY, recursionLimit-1, REGULAR_RAY, pointLight());
		  //This shouldn't get a pointlight but i didn't know what to do.
				  //(ref_ray, .0001, +infinity, recurselimit - 1, REGULAR_RAY, ...)
		  R.addRGBFrom(materialPointer -> getIdealSpec().componentMultiplication(newL_rgb));
		  return R;
	  }
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

					rgbTriple pixelLight = L (pixelRay, 0.0001, INFINITY, RECURSION_LIMIT, PRIMARY_RAY, pointLight());
					Rgba &px = p[i][j];
					px.r = pixelLight.getR(); px.g = pixelLight.getG(); px.b =pixelLight.getB();
				}
	    		//writeRgba (outputName, &p[0][0], w, h);
				//writeRgba ("hw3.exr", &p[0][0], w, h);
				if(i%(h/10)==0 && i!=0)
						cout << "|" << i/(h/10)*10 << "|" ;
			}
			cout << "|100|" << endl;

			writeRgba (outputName, &p[0][0], w, h);
			//cout << "Didn't die while editing the pixels." << endl;

			cout << "Finished writing file" << endl;
}

//void writePixels(char* outputName){
//	int w = cam.getNx();
//	int h = cam.getNy();
//	Array2D<Rgba> p (h,w);
//	p.resizeErase(h,w);
//
//	cout << "Progress: |0|";
//	        for(int i=0; i < h; i++){
//				for(int j=0; j < w; j++) {
//					ray pixelRay = cam.generateRayForPixel(j,h-1-i);
//					bool assigned = false;
//					int index = -1;
//					double minT = -1;
//					for(unsigned int k=0; k < surfaceList.size(); k++){
//						//We need to flip the y axis orientation because while our math uses a traditional x+ right, y+ up grid, the pixels are created with x+ right,y+ down
//						//In this loop, I will represent the pixel index from the bottom, so since we want pixel index from the top, we calculate our rays with (h-i)
//						//Another note: i is the vertical index, j is the horizontal index, so compared to the book, we must call generateRayForPixel with (j, h-i);
//						double tempT = surfaceList.at(k) -> intersectT(pixelRay);
//						if(	(!assigned && tempT > 0) || (assigned && tempT < minT && tempT != -1)	){
//							assigned=true;
//							index = k;
//							minT = tempT;
//						}
//					}
//					Rgba &px = p[i][j];
//					if(assigned)
//					{
//						surface* surface = surfaceList.at((unsigned int)index);
//						material* mat = materialList.at(surface->getMaterialIndex());
//						point pnt = pixelRay.getPointFromT(minT);
//						rgbTriple pixelLight;
//						Vector surfaceNormal = surface->getSurfaceNormal(pnt);
//						Vector pToSource = (pixelRay.getOrigin()).subtract(pnt).getNormalizedVector();
//						bool isFlipped = surfaceNormal.dotProduct(pixelRay.getDir()) > 0; //Check if you're hitting the backside
//
//
////						cout << "surfaceNormal[" << surfaceNormal.getX() << "," << surfaceNormal.getY() << "," << surfaceNormal.getZ()<< "]"<< endl;
////						cout << "pixelRayDir[" << pixelRay.getDir().getX() << "," << pixelRay.getDir().getY() << "," << pixelRay.getDir().getZ()<< "]"<< endl;
////
////						cout << "dotProduct[" << surfaceNormal.dotProduct(pixelRay.getDir()) << "]"<< endl;
////						cout << "isFlipped[" << isFlipped << "]"<< endl;
//						rgbTriple shadeLight;
//						if(!isFlipped){
////							cout << "shading with surface's material" << endl;
//							shadeLight = mat-> shading(pnt, cam, index, surfaceList, pointLightList, ambLight,surfaceNormal, pToSource, isFlipped);
//						}
//						else{
////							cout << "Shading with yellow material" << endl;
//							shadeLight = BACKSIDE_MATERIAL->shading(pnt, cam, index, surfaceList, pointLightList, ambLight, surfaceNormal, pToSource, isFlipped);
//							shadeLight = rgbTriple(1,1,0);
//						}
//
////						for(unsigned int k=0; k < pointLightList.size(); k++){
////							//lambertian shading
////							rgbTriple lambertianShading;
////							//double templsr, templsg, templsb;
////							mat->lambertianShading(pnt, index, surfaceList, pointLightList.at(k), lambertianShading);
////							pixelLight.addRGBFrom(lambertianShading);
////							//specular shading
////							rgbTriple specularShading;
////							//double tempssr, tempssg, tempssb;
////							mat->specularShading(pnt, cam, index, surfaceList, pointLightList.at(k), specularShading);
////							pixelLight.addRGBFrom(specularShading);
////
////						}
//
//
//						pixelLight.addRGBFrom(shadeLight);
//						px.r = pixelLight.getR(); px.g = pixelLight.getG(); px.b =pixelLight.getB();
////						px.r=mat->dr; px.g=mat->dg; px.b=mat->db;
//
//					}
//
//
//					else
//					{
//						px.r=0; px.g=0; px.b=0;
//					}
//
//				}
//	    		//writeRgba (outputName, &p[0][0], w, h);
//				//writeRgba ("hw3.exr", &p[0][0], w, h);
//				if(i%(h/10)==0 && i!=0)
//						cout << "|" << i/(h/10)*10 << "|" ;
//			}
//			cout << "|100|" << endl;
//
//			writeRgba (outputName, &p[0][0], w, h);
//			//cout << "Didn't die while editing the pixels." << endl;
//
//			cout << "Finished writing file" << endl;
//}

int main (int argc, char *argv[])
{

    if (argc != 3) {
        cerr << "useage: raytra scenefilename writefilename" << endl;
        return -1;
    }

    //cout << "no error before parsing" << endl;
    readscene RS;
    RS.parseSceneFile (argv[1]);

    RS.getData(&surfaceList, &materialList, &pointLightList, &cam, &ambLight);

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
