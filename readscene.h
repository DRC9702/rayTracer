/*
 * readscene.h
 *
 *  Created on: Oct 9, 2016
 *      Author: dr2884
 */
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
//My classes
#include "surface.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "ray.h"
#include "exr_test.h"
#include "pointLight.h"

#include "Light.h"
#include "ambientLight.h"
#include "areaLight.h"


#ifndef READSCENE_H_
#define READSCENE_H_

#define IM_DEBUGGING

class readscene
{
public:
	double getTokenAsDouble (string inString, int whichToken);
	std::vector<surface*> surfaceList = std::vector<surface*>();
	std::vector<material*> materialList = std::vector<material*>();
//	std::vector<pointLight*> pointLightList = std::vector<pointLight*>();
//	std::vector<areaLight*> areaLightList = std::vector<areaLight*>();
	std::vector<Light*> lightList = std::vector<Light*>();
	ambientLight ambLight = ambientLight(0,0,0);
	camera cam;
	void parseSceneFile (char *filnam);
	void writeRgba (const char fileName[], const Rgba *pixels, int width, int height);
	//void getData(std::vector<surface*> *surfaceList, std::vector<material*> *materialList, std::vector<pointLight*> *pointLightList, std::vector<areaLight*> *areaLightList, camera *cam, ambientLight* ambLight);
	void getData(std::vector<surface*> *surfaceList, std::vector<material*> *materialList, std::vector<Light*> *lightList, camera *cam, ambientLight* ambLight);
	void read_wavefront_file (const char *file, std::vector< int > &tris, std::vector< double > &verts);
};


#endif /* READSCENE_H_ */
