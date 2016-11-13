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

#include "Constants.h"

#include "BvhNode.h"

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

int RENDER_BOX_FLAG;
//int renderBoxFlag = -1;
int USE_BVH_TREE = 2;
int NO_BVH_TREE = 0;
int BBOXED = 1;

BvhNode root;

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


rgbTriple L2 (ray inputRay, double minT, double maxT, int recursionLimit, int rayType, pointLight light){
//	cout << "L2 says hi." << endl;
	if(recursionLimit==0)
		return rgbTriple(0,0,0);

	  if (rayType == SHADOW_RAY) {
		  //bool intersectionFound = false; //I don't think I need it here at all
		  Intersection intersect;
		  if(root.intersectHit(inputRay, maxT, intersect))
			  return rgbTriple(0,0,0);
		  else{
			  return light.getLightValue();
		  }
	  }

	  //Get closest intersection with scene
	  Intersection intersect;
	  bool intersectionFound = false;
//	  int index = -1;
	  double closestT = -1;
//	  for(unsigned int k=0; k < surfaceList.size(); k++){
//		  Intersection tempIntersect;
//		  if(!surfaceList.at(k) ->intersectHit(inputRay,closestT,tempIntersect)){
//			  continue;
//		  }
//
//		  double tempT = tempIntersect.getVal();
//		  if(tempT < minT || tempT > maxT){
//			  continue;
//		  }
//		  if(	(!intersectionFound && tempT > 0) || (intersectionFound && tempT < closestT && tempT != -1)	){
//			  intersect = tempIntersect;
//			  tempT = tempIntersect.getVal();
//			  intersectionFound = true;
//			  //index = k;
//			  closestT = tempT;
//		  }
//	  }
	  intersectionFound = (root.intersectHit(inputRay, maxT, intersect));
	  closestT = intersect.getVal();

	  if(!intersectionFound)
		  return rgbTriple(0,0,0);

	  point p = inputRay.getPointFromT(closestT);
	  Vector surfaceNormal = intersect.getSurfaceNormal();
	  material *materialPointer = materialList.at(intersect.getMaterialIndex());
	  bool isFlipped = surfaceNormal.dotProduct(inputRay.getDir()) > 0; //Check if you're hitting the backside

	  Vector tempSurfaceNormal = (isFlipped)? surfaceNormal.scalarMultiply(-1) : surfaceNormal;
	  materialPointer = (isFlipped) ? BACKSIDE_MATERIAL : materialPointer;

	  //Do lighting and shading calcuation now?

	  rgbTriple R;
	  for(unsigned int k=0; k < pointLightList.size(); k++){
		  Vector pToLight = pointLightList.at(k)->getPosition().subtract(p);
		  double s_maxT = pToLight.getMagnitude();
		  ray s_ray = ray(p,pToLight);
		  rgbTriple L_rgb = L2(s_ray, 0.0001, s_maxT, 1, SHADOW_RAY, *pointLightList.at(k));
		  if(!L_rgb.isBlank()){
//			  std::cout << "Beginning shading" << std::endl;
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
		  rgbTriple newL_rgb = L2(reflectedRay, 0.0001, INFINITY, recursionLimit-1, REGULAR_RAY, pointLight());
		  //This shouldn't get a pointlight but i didn't know what to do.
				  //(ref_ray, .0001, +infinity, recurselimit - 1, REGULAR_RAY, ...)
		  R.addRGBFrom(materialPointer -> getIdealSpec().componentMultiplication(newL_rgb));
		  return R;
	  }
}

rgbTriple L1 (ray inputRay, double minT, double maxT, int recursionLimit, int rayType, pointLight light){

	if(recursionLimit==0)
		return rgbTriple(0,0,0);

	  if (rayType == SHADOW_RAY) {
		  //bool intersectionFound = false; //I don't think I need it here at all
		  Intersection intersect;
		  for(unsigned int k=0; k < surfaceList.size(); k++){
			  //double tempT = surfaceList.at(k) -> intersectWithBBox(inputRay,renderBoxFlag==1);
//			  if(!surfaceList.at(k) -> intersectHit(inputRay,maxT,intersect))
//				  return rgbTriple(0,0,0);
			  surfaceList.at(k) -> intersectHit(inputRay,maxT,intersect);

			  double tempT = intersect.getVal();
			  if (tempT > minT && tempT < maxT){
				  return rgbTriple(0,0,0);
			  }
		  }
		  return light.getLightValue();
	  }

	  //Get closest intersection with scene
	  Intersection intersect;
	  bool intersectionFound = false;
//	  int index = -1;
	  double closestT = -1;
	  for(unsigned int k=0; k < surfaceList.size(); k++){
		  //double tempT = surfaceList.at(k) -> intersectWithBBox(inputRay,renderBoxFlag	==1);
		  //Intersection tempIntersect = surfaceList.at(k) ->checkIntersectWithBBox(inputRay,RENDER_BOX_FLAG);
		  Intersection tempIntersect;
		  if(!surfaceList.at(k) ->intersectHit(inputRay,closestT,tempIntersect)){
//			  std::cout << tempIntersect.isHit() << std::endl;
			  continue;
		  }

		  double tempT = tempIntersect.getVal();
//		  std::cout << tempT << std::endl;
		  if(tempT < minT || tempT > maxT){
			  continue;
		  }
		  if(	(!intersectionFound && tempT > 0) || (intersectionFound && tempT < closestT && tempT != -1)	){
			  intersect = tempIntersect;
			  tempT = tempIntersect.getVal();
			  intersectionFound = true;
			  //index = k;
			  closestT = tempT;
		  }
	  }
	  if(!intersectionFound)
		  return rgbTriple(0,0,0);

	  point p = inputRay.getPointFromT(closestT);

	  //We need these to determine which material to use.
	  //surface *surfacePointer = surfaceList.at(index);
//	  Vector surfaceNormal = surfacePointer ->getSurfaceNormal(p);
//	  material *materialPointer = materialList.at(surfacePointer->getMaterialIndex());
	  Vector surfaceNormal = intersect.getSurfaceNormal();
	  material *materialPointer = materialList.at(intersect.getMaterialIndex());
	  bool isFlipped = surfaceNormal.dotProduct(inputRay.getDir()) > 0; //Check if you're hitting the backside

	  Vector tempSurfaceNormal = (isFlipped)? surfaceNormal.scalarMultiply(-1) : surfaceNormal;
	  materialPointer = (isFlipped) ? BACKSIDE_MATERIAL : materialPointer;

	  //Do lighting and shading calcuation now?

	  rgbTriple R;
	  for(unsigned int k=0; k < pointLightList.size(); k++){
		  Vector pToLight = pointLightList.at(k)->getPosition().subtract(p);
		  double s_maxT = pToLight.getMagnitude();
		  ray s_ray = ray(p,pToLight);
		  rgbTriple L_rgb = L1(s_ray, 0.0001, s_maxT, 1, SHADOW_RAY, *pointLightList.at(k));
		  if(!L_rgb.isBlank()){
//			  std::cout << "Beginning shading" << std::endl;
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
		  rgbTriple newL_rgb = L1(reflectedRay, 0.0001, INFINITY, recursionLimit-1, REGULAR_RAY, pointLight());
		  //This shouldn't get a pointlight but i didn't know what to do.
				  //(ref_ray, .0001, +infinity, recurselimit - 1, REGULAR_RAY, ...)
		  R.addRGBFrom(materialPointer -> getIdealSpec().componentMultiplication(newL_rgb));
		  return R;
	  }
}

rgbTriple L (ray inputRay, double minT, double maxT, int recursionLimit, int rayType, pointLight light){
	if(RENDER_BOX_FLAG==0)
		return L1(inputRay, minT, maxT, recursionLimit, rayType, light);
	else
		return L2(inputRay, minT, maxT, recursionLimit, rayType, light);
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

					rgbTriple pixelLight = L(pixelRay, 0.0001, INFINITY, RECURSION_LIMIT, PRIMARY_RAY, pointLight());
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


int main (int argc, char *argv[])
{

	if(argc == 3){
		RENDER_BOX_FLAG = USE_BVH_TREE;
	}
	else if(argc==4){
		//Get the renderBoxFlag
		RENDER_BOX_FLAG = atoi( argv[3] ); //I tried stoi but it didn't work :(
		cout << RENDER_BOX_FLAG << endl;
		if(RENDER_BOX_FLAG != NO_BVH_TREE && RENDER_BOX_FLAG != BBOXED){
			cerr << "flag_render_bboxes must be of: {omitted,0,1}" << endl;
			return -1;
		}
	}
	else {
        cerr << "useage: raytra scenefilename writefilename flag_render_bboxes[Optional]" << endl;
        return -1;
    }



    //cout << "no error before parsing" << endl;
    readscene RS;
    RS.parseSceneFile (argv[1]);

    RS.getData(&surfaceList, &materialList, &pointLightList, &cam, &ambLight);
    cout << surfaceList.size() << endl;
    if(RENDER_BOX_FLAG){
    	root = BvhNode();
    	root.create(surfaceList.begin(), surfaceList.end(), 0);
    }
//    cout << root.leftSurface << endl;
//    cout << surfaceList.at(0) << endl;
    //cout << cam.nx << "\t" << cam.ny << endl;


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
