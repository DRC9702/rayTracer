/*
 * pointLight.h
 *
 *  Created on: Oct 11, 2016
 *      Author: dr2884
 */
#include "Light.h"
#include "point.h"
//#include "material.h"
//#include "surface.h"
//#include "ray.h"
//#include "camera.h"
#include "rgbTriple.h"

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

class pointLight : public Light {
private:
	double intensity; //Multiplier on each color
public:
	pointLight();
	pointLight(double x, double y, double z, double r, double g, double b, double intensity);
	virtual ~pointLight();

	double getIntensity() const {
		return intensity;
	}
};

#endif /* POINTLIGHT_H_ */
