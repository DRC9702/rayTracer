/*
 * plane.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: dr2884
 */

#include "plane.h"
#include <iostream>

plane::plane() {
	normal = vector(0,1,0);
	originDistance = 0;
}

plane::plane(vector normal, double originDistance){
	this->normal = normal;
	this->originDistance = originDistance;
}

plane::plane(double nx, double ny, double nz, double originDistance){
	this->normal = vector(nx,ny,nz);
	this->originDistance = originDistance;
}

plane::plane(point p1, point p2, point p3){
	normal = (p2.subtract(p1)).crossProduct((p3.subtract(p1))).getNormalizedVector();
	originDistance = normal.dotProduct(p1.toVectorFromOrigin());
}

vector plane::getNormal(){
	return normal;
}
double plane::getOriginDistance(){
	return originDistance;
}

vector plane::getSurfaceNormal(point p){
	//ToDo: Should implement an assertion here to make sure p is on surface. //I can't figure out how
	//std::cout <<"PLANE IS THE GUY BEING CALLED" << std::endl;
	return getNormal();

}

double plane::intersectT(ray r_ray){
	double dirDotNormal = (r_ray.dir).dotProduct(normal);
	if(dirDotNormal==0){
		return -1; //No intersection. Plane and ray are parallel
	}
	else{ //Yes intersection
		double t = -(	(r_ray.origin).toVectorFromOrigin().dotProduct(normal) - originDistance	)/dirDotNormal;
		return t;
		//return 1000;
	}
}


plane::~plane() {
	// TODO Auto-generated destructor stub
}


