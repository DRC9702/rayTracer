/*
 * plane.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: dr2884
 */

#include "plane.h"
#include <iostream>

plane::plane() {
	normal = Vector(0,1,0);
	originDistance = 0;
}

plane::plane(Vector normal, double originDistance){
	this->normal = normal.getNormalizedVector();
	this->originDistance = originDistance;
}

plane::plane(double nx, double ny, double nz, double originDistance){
	this->normal = Vector(nx,ny,nz).getNormalizedVector();
	this->originDistance = originDistance;
}

plane::plane(point p1, point p2, point p3){
	normal = (p2.subtract(p1)).crossProduct((p3.subtract(p1))).getNormalizedVector();
	originDistance = normal.dotProduct(p1.toVectorFromOrigin());
}

Vector plane::getNormal() const{
	return normal;
}
double plane::getOriginDistance() const{
	return originDistance;
}

Vector plane::getSurfaceNormal(const point p) const{
	//ToDo: Should implement an assertion here to make sure p is on surface. //I can't figure out how
	//std::cout <<"PLANE IS THE GUY BEING CALLED" << std::endl;
	return getNormal();

}

double plane::intersectT(const ray r_ray) const{
	double dirDotNormal = (r_ray.getDir()).dotProduct(normal);

	if(dirDotNormal==0){
		return -1; //No intersection. Plane and ray are parallel
	}
	else{ //Yes intersection
		double t = -(	(r_ray.getOrigin()).toVectorFromOrigin().dotProduct(normal) - originDistance	)/dirDotNormal;
		if(t<0){ //Plane should be hit from the back
			return -1;
			//return -t;
		}
		else{
			return t;
		}
		//return 1000;

	}
}


plane::~plane() {
	// TODO Auto-generated destructor stub
}


