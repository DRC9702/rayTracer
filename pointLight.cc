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
#include <cassert>
#include <cmath>
#include <iostream>

pointLight::pointLight() {
	r=0.5;
	g=0.6;
	b=0.7;
	intensity=1;
}

pointLight::pointLight(float x, float y, float z, float r, float g, float b, float intensity){
	//assert(r>0 && r<=1 && g>0 && g<=1 && b>0 && b<=1);
	this->r = r;
	this->g = g;
	this->b = b;
	this-> intensity = intensity;
	this->position = point(x,y,z);
}

void pointLight::lambertianShading(point p, surface *surface, material *m, float  &ldr, float &ldg, float &ldb){
	vector l = position.subtract(p); l.normalize();
	vector surfaceNormal = surface->getSurfaceNormal(p);
	//std::cout << "l.x:" << l.x << std::endl;
	//std::cout << "sn.x:" << surfaceNormal.x << std::endl;

	//These are my diffuse coefficients
	float dr = m->dr;
	float dg = m->dg;
	float db = m->db;
	//float intensityCoefficient = 1 / (l.getMagnitude()*l.getMagnitude());
	float intensityCoefficient = intensity/(position.subtract(p).getMagnitude()*position.subtract(p).getMagnitude()) ; //WHAT IS I?!?!?!

	float dotMultiplier = l.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;

	//Diffusely reflect light in each of the three channels
	ldr = dr * dotMultiplier * r * intensityCoefficient;
	//std::cout << "ldr:" << ldr << "\tintensity coefficient:" << intensityCoefficient << "\tdotmultiplier:" << dotMultiplier << std::endl;
	ldg = dg * dotMultiplier * g * intensityCoefficient;
	ldb = db * dotMultiplier * b * intensityCoefficient;
}

void pointLight::specularShading(point p, ray rToP, surface *surface, material *m, float &lsr, float &lsg, float &lsb){
	vector v = (rToP.dir).negationVector().normalize();
	vector surfaceNormal = surface->getSurfaceNormal(p);
	vector l = position.subtract(p); l.normalize();
	float distance = position.subtract(p).getMagnitude();
	vector h = v.add(l).normalize(); //Since both v and l are unit vectors, this should bisect them
	
	//These are my specular coefficients
	float sr = m->sr;
	float sg = m->sg;
	float sb = m->sb;
	float phong = m->r; //my phong exponent
	float intensityCoefficient = intensity/(distance*distance); //WHAT IS I?!?!?!
	
	float dotMultiplier = h.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;
	
	lsr = (float)(sr * pow(dotMultiplier,phong) * r * intensityCoefficient);
	lsg = (float)(sg * pow(dotMultiplier,phong) * g * intensityCoefficient);
	lsb = (float)(sb * pow(dotMultiplier,phong) * b * intensityCoefficient);		
	
	
}

pointLight::~pointLight() {
	// TODO Auto-generated destructor stub
}

