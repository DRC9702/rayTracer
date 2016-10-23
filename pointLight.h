/*
 * pointLight.h
 *
 *  Created on: Oct 11, 2016
 *      Author: dr2884
 */
#include "point.h"
//#include "material.h"
//#include "surface.h"
//#include "ray.h"
//#include "camera.h"
#include "rgbTriple.h"

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

class pointLight {
private:
	point position;
	rgbTriple lightValue; //I prefer RGB over just indices. //It makes it easier for me to read the code //All of these should be between 0 and 1
	double intensity; //Multiplier on each color
public:
	pointLight();
	pointLight(double x, double y, double z, double r, double g, double b, double intensity);
	virtual ~pointLight();

	double getIntensity() const {
		return intensity;
	}

	const rgbTriple& getLightValue() const {
		return lightValue;
	}

	const point& getPosition() const {
		return position;
	}
};

#endif /* POINTLIGHT_H_ */
