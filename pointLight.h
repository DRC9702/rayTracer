/*
 * pointLight.h
 *
 *  Created on: Oct 11, 2016
 *      Author: dr2884
 */
#include "point.h"
#include "material.h"
#include "surface.h"
#include "ray.h"
#include "camera.h"

#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

class pointLight {
public:
	point position;
	double r, g, b; //I prefer RGB over just indices. //It makes it easier for me to read the code //All of these should be between 0 and 1
	double intensity; //Multiplier on each color
	pointLight();
	pointLight(double x, double y, double z, double r, double g, double b, double intensity);
	virtual ~pointLight();
	void lambertianShading(point p, surface *surface, material *m, double &ldr, double &ldg, double &ldb);
	void specularShading(point p, camera cam, surface *surface, material *m, double &lsr, double &lsg, double &lsb);
};

#endif /* POINTLIGHT_H_ */
