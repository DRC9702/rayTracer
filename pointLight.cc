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
#include <cmath>
#include <iostream>

pointLight::pointLight() {
	r=0.5;
	g=0.6;
	b=0.7;
	intensity=1;
}

pointLight::pointLight(double x, double y, double z, double r, double g, double b, double intensity){
	//assert(r>0 && r<=1 && g>0 && g<=1 && b>0 && b<=1);
	this->r = r;
	this->g = g;
	this->b = b;
	this-> intensity = intensity;
	this->position = point(x,y,z);
}

void pointLight::lambertianShading(point p, surface *surface, material *m, double  &ldr, double &ldg, double &ldb){
	vector l = position.subtract(p); l.normalize();
	double distance = position.subtract(p).getMagnitude();
	vector surfaceNormal = surface->getSurfaceNormal(p);
	//std::cout << "l.x:" << l.x << std::endl;
	//std::cout << "sn.x:" << surfaceNormal.x << std::endl;

	//These are my diffuse coefficients
	double dr = m->dr;
	double dg = m->dg;
	double db = m->db;
	//double intensityCoefficient = 1 / (l.getMagnitude()*l.getMagnitude());
	double intensityCoefficient = intensity/(distance*distance); //WHAT IS I?!?!?!

	double dotMultiplier = l.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;

	//Diffusely reflect light in each of the three channels
	ldr = dr * dotMultiplier * r * intensityCoefficient;
	//std::cout << "ldr:" << ldr << "\tintensity coefficient:" << intensityCoefficient << "\tdotmultiplier:" << dotMultiplier << std::endl;
	ldg = dg * dotMultiplier * g * intensityCoefficient;
	ldb = db * dotMultiplier * b * intensityCoefficient;
}

void pointLight::specularShading(point p, camera cam, surface *surface, material *m, double &lsr, double &lsg, double &lsb){
	vector v = (cam.eye).subtract(p).getNormalizedVector();
	vector surfaceNormal = surface->getSurfaceNormal(p);
	//std::cout << "surface normal before stuff[" << surfaceNormal.getMagnitude() << "]" << std::endl;
	vector l = position.subtract(p); l.normalize();
	double distance = position.subtract(p).getMagnitude();
	vector h = v.add(l); h.normalize(); //Since both v and l are unit vectors, this should bisect them
	
	//These are my specular coefficients
	double sr = m->sr;
	double sg = m->sg;
	double sb = m->sb;
	double phong = m->r; //my phong exponent
	double intensityCoefficient = intensity/(distance*distance); //WHAT IS I?!?!?!
	
	double dotMultiplier = h.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;
	
//	std::cout << "dotMultiplier[" << dotMultiplier << "]" << std::endl;
//	std::cout << "h[" << h.getMagnitude() << "]" << std::endl;
//	std::cout << "n[" << surfaceNormal.getMagnitude() << "]" << std::endl;

	lsr = (double)(sr * pow(dotMultiplier,phong) * r * intensityCoefficient);

	lsg = (double)(sg * pow(dotMultiplier,phong) * g * intensityCoefficient);
	lsb = (double)(sb * pow(dotMultiplier,phong) * b * intensityCoefficient);
	
	
}

pointLight::~pointLight() {
	// TODO Auto-generated destructor stub
}

