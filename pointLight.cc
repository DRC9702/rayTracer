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
	lightValue = rgbTriple();
	intensity=1;
}

pointLight::pointLight(double x, double y, double z, double r, double g, double b, double intensity){
	//assert(r>0 && r<=1 && g>0 && g<=1 && b>0 && b<=1);
	lightValue.setRGB(r,g,b);
	this-> intensity = intensity;
	this->position = point(x,y,z);
}

void pointLight::lambertianShading(point p, surface *surface, material *m, rgbTriple &lambertianRGB){
	vector l = position.subtract(p); l.normalize();
	double distance = position.subtract(p).getMagnitude();
	vector surfaceNormal = surface->getSurfaceNormal(p);
	//std::cout << "l.x:" << l.x << std::endl;
	//std::cout << "sn.x:" << surfaceNormal.x << std::endl;

	//These are my diffuse coefficients
	double dr = m->diffuse.getR();
	double dg = m->diffuse.getG();
	double db = m->diffuse.getB();
	//double intensityCoefficient = 1 / (l.getMagnitude()*l.getMagnitude());
	double intensityCoefficient = intensity/(distance*distance); //WHAT IS I?!?!?!

	double dotMultiplier = l.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;

	//Diffusely reflect light in each of the three channels
	lambertianRGB.setR(dr * dotMultiplier * lightValue.getR() * intensityCoefficient);
	lambertianRGB.setG(dg * dotMultiplier * lightValue.getG() * intensityCoefficient);
	lambertianRGB.setB(db * dotMultiplier * lightValue.getB() * intensityCoefficient);
}

void pointLight::specularShading(point p, camera cam, surface *surface, material *m, rgbTriple &specularRGB){
	vector v = (cam.eye).subtract(p).getNormalizedVector();
	vector surfaceNormal = surface->getSurfaceNormal(p);
	//std::cout << "surface normal before stuff[" << surfaceNormal.getMagnitude() << "]" << std::endl;
	vector l = position.subtract(p); l.normalize();
	double distance = position.subtract(p).getMagnitude();
	vector h = v.add(l); h.normalize(); //Since both v and l are unit vectors, this should bisect them
	
	//These are my specular coefficients
	double sr = m->specular.getR();
	double sg = m->specular.getG();
	double sb = m->specular.getB();
	double phong = m->r; //my phong exponent
	double intensityCoefficient = intensity/(distance*distance); //WHAT IS I?!?!?!
	
	double dotMultiplier = h.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;
	
//	std::cout << "dotMultiplier[" << dotMultiplier << "]" << std::endl;
//	std::cout << "h[" << h.getMagnitude() << "]" << std::endl;
//	std::cout << "n[" << surfaceNormal.getMagnitude() << "]" << std::endl;

	specularRGB.setR(sr * pow(dotMultiplier,phong) * lightValue.getR() * intensityCoefficient);
	specularRGB.setG(sg * pow(dotMultiplier,phong) * lightValue.getG() * intensityCoefficient);
	specularRGB.setB(sb * pow(dotMultiplier,phong) * lightValue.getB() * intensityCoefficient);
	
	
}

pointLight::~pointLight() {
	// TODO Auto-generated destructor stub
}

