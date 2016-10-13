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
	float r, g, b; //I prefer RGB over just indices. //It makes it easier for me to read the code //All of these should be between 0 and 1
	float intensity; //Multiplier on each color
	pointLight();
	pointLight(float x, float y, float z, float r, float g, float b, float intensity);
	virtual ~pointLight();
	void lambertianShading(point p, surface *surface, material *m, float &ldr, float &ldg, float &ldb);
	void specularShading(point p, camera cam, surface *surface, material *m, float &lsr, float &lsg, float &lsb);
};

#endif /* POINTLIGHT_H_ */
