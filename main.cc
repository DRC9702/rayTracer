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

int PRAYS_N = -1;
int SRAYS_N = -1;




//int renderBoxFlag = -1;
int USE_BVH_TREE = 2;
int NO_BVH_TREE = 0;
int BBOXED = 1;
int RENDER_BOX_FLAG = USE_BVH_TREE; //Had to put this in for 1.4, too lazy to take out for 1.5

BvhNode *root;

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
//	cout << "L2 says hi." << endl;
	if(recursionLimit==0)
		return rgbTriple(0,0,0);

	  if (rayType == SHADOW_RAY) {
		  //bool intersectionFound = false; //I don't think I need it here at all
		  Intersection intersect;
		  if(root->intersectHit(inputRay, maxT, intersect))
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
	  intersectionFound = (root->intersectHit(inputRay, maxT, intersect));
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
		  rgbTriple L_rgb = L(s_ray, 0.0001, s_maxT, 1, SHADOW_RAY, *pointLightList.at(k));
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
					//ray pixelRay = cam.generateRayForPixel(j,h-1-i);
					rgbTriple pixelLight = rgbTriple(0,0,0);
					for(int p=0; p<PRAYS_N; p++){
						for(int q=0; q<PRAYS_N; q++){
							ray pixelRay = cam.generateRayForPixel(j,h-1-i,p,q,PRAYS_N);
//							ray pixelRay = cam.generateRayForPixel(j,h-1-i);
							rgbTriple tempPixelLight = L(pixelRay, 0.0001, INFINITY, RECURSION_LIMIT, PRIMARY_RAY, pointLight());
//							cout << tempPixelLight.getR() << "\t" << tempPixelLight.getG() << "\t" << tempPixelLight.getB() << endl;
							pixelLight.addRGBFrom(tempPixelLight);
						}
					}
					//rgbTriple pixelLight = L(pixelRay, 0.0001, INFINITY, RECURSION_LIMIT, PRIMARY_RAY, pointLight());
					pixelLight.scale(1/(PRAYS_N*PRAYS_N));
//					cout << pixelLight.getR() << "\t" << pixelLight.getG() << "\t" << pixelLight.getB() << endl;
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
		PRAYS_N = 1;
		SRAYS_N = 1;
		cout << "SquareRoot Of Primary Ray Sampling Number: " << "[1]" << endl;
		cout << "SquareRoot Of Shadow Ray Sampling Number: " << "[1]" << endl;
	}
	else if(argc==5){
		//Get the renderBoxFlag
		PRAYS_N = atoi( argv[3] ); //I tried stoi but it didn't work :(
		SRAYS_N = atoi( argv[4] );
		cout << "SquareRoot Of Primary Ray Sampling Number: " << "[" << PRAYS_N << "]" << endl;
		cout << "SquareRoot Of Shadow Ray Sampling Number: " << "[" << SRAYS_N << "]" << endl;
		if(PRAYS_N < 1 && SRAYS_N < 1){
			cerr << "Sampling Input Numbers must be >=1" << endl;
			return -1;
		}
	}
	else {
        cerr << "useage: raytra scenefilename writefilename flag_PRAYS_N flag_SRAYS_N" << endl;
        return -1;
    }



    //cout << "no error before parsing" << endl;
    readscene RS;
    RS.parseSceneFile (argv[1]);

    RS.getData(&surfaceList, &materialList, &pointLightList, &cam, &ambLight);
    cout << "Number Of Surfaces: " << surfaceList.size() << endl;

    root = new BvhNode();
	root->create(surfaceList.begin(), surfaceList.end(), 0);


    try{

    	writePixels(argv[2]);
    }
    catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }



    delete(root);


    //Free materials pointed to in material list
    for(material* m : materialList){
    	delete(m);
    }
    delete(BACKSIDE_MATERIAL);

    //Free pointLights pointed to in pointLight list
    for(pointLight* p : pointLightList){
    	delete(p);
    }

    return 0;
}
