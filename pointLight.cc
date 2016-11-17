/*
 * pointLight.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: dr2884
 */

#include "pointLight.h"
#include "point.h"
#include "material.h"
#include "surface.h"
#include "camera.h"
#include <cassert>
//#include <iostream>

pointLight::pointLight() {
	lightValue = rgbTriple();
	intensity=1;
	this->aLight = false;
}

pointLight::pointLight(double x, double y, double z, double r, double g, double b, double intensity){
	//assert(r>0 && r<=1 && g>0 && g<=1 && b>0 && b<=1);
	lightValue.setRGB(r,g,b);
	this-> intensity = intensity;
	this->position = point(x,y,z);
	this->aLight = false;
}


pointLight::~pointLight() {
	// TODO Auto-generated destructor stub
}

