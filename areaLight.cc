/*
 * areaLight.cc
 *
 *  Created on: Nov 17, 2016
 *      Author: david
 */

#include "areaLight.h"
#include <cstdlib>

areaLight::areaLight(double x, double y, double z, double nx, double ny, double nz,
		double ux, double uy, double uz, double len, double r, double g, double b){
	this->aLight = true;
	position = point(x,y,z);
	direction = Vector(nx,ny,nz); direction.normalize();
	uvector = Vector(ux,uy,uz); uvector.normalize();
	vvector = uvector.crossProduct(direction).getNormalizedVector();
	this->len = len;
	lightValue = rgbTriple(r,g,b);
	blCorner = position.addVector(uvector.scalarMultiply(-0.5*len)).addVector(uvector.scalarMultiply(-0.5*len));
}

const Vector& areaLight::getDirection() const {
	return direction;
}

double areaLight::getLen() const {
	return len;
}

const Vector& areaLight::getUvector() const {
	return uvector;
}

const Vector& areaLight::getVvector() const {
	return vvector;
}

const point& areaLight::getblCorner() const{
	return blCorner;
}

const point areaLight::generateSurfacePoint(int p, int q, int N) const{
	double su = (p+(rand()+0.0)/RAND_MAX)/N;
	double sv = (q+(rand()+0.0)/RAND_MAX)/N;
	point returnPoint = blCorner.addVector(uvector.scalarMultiply(su)).addVector(vvector.scalarMultiply(sv));
	return returnPoint;
}

areaLight::~areaLight() {
	// TODO Auto-generated destructor stub
}

