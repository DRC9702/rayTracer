/*
 * ambientLight.cc
 *
 *  Created on: Oct 26, 2016
 *      Author: dr2884
 */

#include "ambientLight.h"
#include <cassert>
//#include <iostream>

ambientLight::ambientLight() {
	lightValue = rgbTriple();
}

ambientLight::ambientLight(double r, double g, double b){
	lightValue.setRGB(r,g,b);
}


ambientLight::~ambientLight() {
	// TODO Auto-generated destructor stub
}
