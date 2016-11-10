/*
 * BBox.cc
 *
 *  Created on: Nov 6, 2016
 *      Author: dr2884
 */

#include "BBox.h"

BBox::BBox(point minVals, point maxVals, int surfaceIndex){
	this->minVals = minVals;
	this->maxVals = maxVals;
	this->surfaceIndex = surfaceIndex;
}

int BBox::getSurfaceIndex(){
	return surfaceIndex;
}

BBox::BBox(){
	this->minVals = point();
	this->maxVals = point();
}

BBox::~BBox() {
	// TODO Auto-generated destructor stub
}

Intersection BBox::checkIntersect(const ray& r, int materialIndex) const{
	point rayO = r.getOrigin();
	Vector rayDir = r.getDir();

	//Get your dx,dy,dz
	double dx = rayDir.getX();
	double dy = rayDir.getY();
	double dz = rayDir.getZ();

	//Get your ax,ay,az //Because the code breaks for negative -0 values of dx,dy,and dz
	double ax = 1/dx;
	double ay = 1/dy;
	double az = 1/dz;

	//Calculate txMin, txMax;
	float txMin, txMax;
	if(dx>=0){
		txMin = (minVals.getX() - rayO.getX())*ax;
		txMax = (maxVals.getX() - rayO.getX())*ax;
	}
	else{
		txMin = (maxVals.getX() - rayO.getX())*ax;
		txMax = (minVals.getX() - rayO.getX())*ax;
	}

	//Calculate tyMin, tyMax;
	float tyMin, tyMax;
	if(dy>=0){
		tyMin = (minVals.getY() - rayO.getY())*ay;
		tyMax = (maxVals.getY() - rayO.getY())*ay;
	}
	else{
		tyMin = (maxVals.getY() - rayO.getY())*ay;
		tyMax = (minVals.getY() - rayO.getY())*ay;
	}

	//Calculate tzMin, tzMax;
	float tzMin, tzMax;
	if(dz>=0){
		tzMin = (minVals.getZ() - rayO.getZ())*az;
		tzMax = (maxVals.getZ() - rayO.getZ())*az;
	}
	else{
		tzMin = (maxVals.getZ() - rayO.getZ())*az;
		tzMax = (minVals.getZ() - rayO.getZ())*az;
	}

	//Check if the t-intervals overlap
	//First check if the tx interval isn't outside the others
	if(	(txMin>tyMax) || (txMin>tzMax)	){
		return Intersection();
	}
	//Then check if the ty interval isn't outside the others
	if(	(tyMin>txMax) || (tyMin>tzMax)	){
		return Intersection();
	}
	//Finally check if the tz interval isn't outside the others
	if(	(tzMin>txMax) || (tzMin>tyMax)	){
		return Intersection();
	}
	//Now find the largest minimum t to return (in terms of x,y,and z)
	//Must make sure they're non-negative
	double tMin;
	if(	(txMin>tyMin) && (txMin>tzMin) && (txMin>0)	){
		tMin = txMin;
		//ToDo: Fix vector direction
		return Intersection(materialIndex, tMin, Vector((dx<0)?1:-1,0,0));
	}
	else if(	(tyMin>txMin) && (tyMin>tzMin) && (tyMin>0)	){
		tMin = tyMin;
		//ToDo: Fix vector direction
		return Intersection(materialIndex, tMin, Vector(0,(dy<0)?1:-1,0));
	}
	else if(	(tzMin>txMin) && (tzMin>tyMin) && (tzMin>0)	){
		tMin = tzMin;
		//ToDo: Fix vector direction
		return Intersection(materialIndex, tMin, Vector(0,0,(dz<0)?1:-1));
	}
	else{
		tMin = -1; //No intersection;
		return Intersection();
	}
}
