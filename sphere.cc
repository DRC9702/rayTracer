#include "sphere.h"
#include "surface.h"
#include <cmath>
#include <cassert>

sphere::sphere(const point center,const double radius)
{
	this->center=center;
	this->radius=radius;
	initBBox();
}

sphere::sphere(const double x, const double y, const double z, const double radius)
{
	this->center = point(x,y,z);
	this->radius=radius;
	initBBox();
}

void sphere::initBBox(){
	double xMin = center.getX() - radius;
	double xMax = center.getX() + radius;

	double yMin = center.getY() - radius;
	double yMax = center.getY() + radius;

	double zMin = center.getZ() - radius;
	double zMax = center.getZ() + radius;

	setBoundingBox(BBox(point(xMin,yMin,zMin), point(xMax,yMax,zMax)));
}

Intersection sphere::checkIntersect(const ray r_ray) const{
	double tVal = intersectT(r_ray);
	if(tVal < 0) //Miss
		return Intersection();
	else
		return Intersection(getMaterialIndex(), tVal, getSurfaceNormal(r_ray.getPointFromT(tVal)));
}

double sphere::intersectT(const ray r_ray) const
{
	Vector p0minusO = r_ray.getOrigin().subtract(center);
	double a1 = (r_ray.getDir().scalarMultiply(-1)).dotProduct(p0minusO);
	
	double a2 = (r_ray.getDir()).dotProduct(p0minusO);
	a2 = a2*a2;
	
	double a3 = r_ray.getDir().dotProduct(r_ray.getDir());
	double a4 = p0minusO.dotProduct(p0minusO) - radius*radius;
	
	double discriminant = a2 - a3*a4;
	
	if(discriminant<0){ //No intersection
		return -1;
	}
	else if(discriminant==0){
		double s = std::sqrt(discriminant);
		double t1 = (a1 + s)/a3;  //t1 and t2 will be equal.
		return t1; //1 Intersection
	}
	else{
		double s = std::sqrt(discriminant);
		
		double t1 = (a1 + s)/a3;
		double t2 = (a1 - s)/a3;
		
		if(t1<0 && t2<0)
			return -1;
		else if(t1<0 && t2>=0)
			return t2;
		else if(t2<0 && t1>=0)
			return t1;
		else if(t1 < t2)
			return t1;
		else
			return t2;


//		if(t1 < t2)
//			return t1;
//		else
//			return t2;
	}

}

Vector sphere::getSurfaceNormal(const point p) const{
	Vector sn = p.subtract(getCenter());
	//std::cout <<"Magnitude: " << sn.getMagnitude() << "\tRadius: " << getRadius() << std::endl;

	//ToDo: Remember to put this back in when you refactor intersection stuff
	//assert(std::abs(sn.getMagnitude()-getRadius())<.1); //I don't know how much precision is needed.

	//std::cout <<"SPHERE IS THE GUY BEING CALLED" << std::endl;
	sn.normalize();
	return sn;
}
