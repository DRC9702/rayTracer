#include "sphere.h"
#include "surface.h"
#include "ray.h"
#include "vector.h"
#include "point.h"
#include <cmath>
#include <cassert>

#include <iostream>

sphere::sphere(point center, double r)
{
	this->center=center;
	this->r=r;
}

sphere::sphere(double x, double y, double z, double r)
{
	this->center = point(x,y,z);
	this->r=r;
}

point sphere::getCenter()
{
	return center;
}

double sphere::getRadius()
{
	return r;
}


double sphere::intersectT(ray r_ray)
{
	vector p0minusO = r_ray.origin.subtract(center);
	double a1 = (r_ray.dir.scalarMultiply(-1)).dotProduct(p0minusO);
	
	double a2 = (r_ray.dir).dotProduct(p0minusO);
	a2 = a2*a2;
	
	double a3 = r_ray.dir.dotProduct(r_ray.dir);
	double a4 = p0minusO.dotProduct(p0minusO) - r*r;
	
	double discriminant = a2 - a3*a4;
	
	if(discriminant<0)
		return -1;
	else{
		double s = std::sqrt(discriminant);
		
		double t1 = (a1 + s)/a3;
		double t2 = (a1 - s)/a3;
		
		if(t1 < t2)
			return t1;
		else
			return t2;
	}

}

vector sphere::getSurfaceNormal(point p){
	vector sn = p.subtract(getCenter());
	//std::cout <<"Magnitude: " << sn.getMagnitude() << "\tRadius: " << getRadius() << std::endl;
	assert(std::abs(sn.getMagnitude()-getRadius())<.1); //I don't know how much precision is needed.
	//std::cout <<"SPHERE IS THE GUY BEING CALLED" << std::endl;
	sn.normalize();
	return sn;
}
