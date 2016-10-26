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
#include "ambientLight.h"


#ifndef READSCENE_H_
#define READSCENE_H_

#define IM_DEBUGGING

class readscene
{
public:
	double getTokenAsDouble (string inString, int whichToken);
	std::vector<surface*> surfaceList = std::vector<surface*>();
	std::vector<material*> materialList = std::vector<material*>();
	std::vector<pointLight*> pointLightList = std::vector<pointLight*>();
	ambientLight ambLight = ambientLight(0,0,0);
	camera cam;
	void parseSceneFile (char *filnam);
	void writeRgba (const char fileName[], const Rgba *pixels, int width, int height);
	void getData(std::vector<surface*> *surfaceList, std::vector<material*> *materialList, std::vector<pointLight*> *pointLightList, camera *cam, ambientLight* ambLight);
};


#endif /* READSCENE_H_ */
