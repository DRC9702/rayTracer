/*
 * Intersection.cc
 *
 *  Created on: Nov 8, 2016
 *      Author: david
 */

#include "Intersection.h"

Intersection::Intersection(){
	materialIndex=0; //Default material index
	tVal = -1; //Miss
	hit = false;
	surfaceNormal = Vector();
}

Intersection::Intersection(int materialIndex, double tVal, Vector surfaceNormal){
	this->materialIndex = materialIndex;
	this->tVal = tVal;
	this->surfaceNormal = surfaceNormal;
	hit = true;
}

bool Intersection::isHit() const {
	return hit;
}

int Intersection::getMaterialIndex() const {
	return materialIndex;
}

const Vector& Intersection::getSurfaceNormal() const {
	return surfaceNormal;
}

double Intersection::getVal() const {
	return tVal;
}

Intersection::~Intersection() {
	// TODO Auto-generated destructor stub
}

