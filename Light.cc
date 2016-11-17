/*
 * Light.cc
 *
 *  Created on: Nov 17, 2016
 *      Author: david
 */

#include "Light.h"

Light::Light() {
	// TODO Auto-generated constructor stub

}

bool Light::isAreaLight() const {
	return aLight;
}

const rgbTriple& Light::getLightValue() const {
	return lightValue;
}

const point& Light::getPosition() const {
	return position;
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

