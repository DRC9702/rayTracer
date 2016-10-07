#include "sphere.h"
#include "surface.h"
#include "ray.h"
#include "vector.h"
#include "point.h"
#include <cmath>

sphere::sphere(point center, float r)
{
	this->center=center;
	this->r=r;
}

sphere::sphere(float x, float y, float z, float r)
{
	this->center = point(x,y,z);
	this->r=r;
}

point sphere::getCenter()
{
	return center;
}

float sphere::getRadius()
{
	return r;
}


float sphere::intersectT(ray r_ray)
{
	vector p0minusO = r_ray.origin.subtract(center);
	float a1 = (r_ray.dir.scalarMultiply(-1)).dotProduct(p0minusO);
	
	float a2 = (r_ray.dir).dotProduct(p0minusO);
	a2 = a2*a2;
	
	float a3 = r_ray.dir.dotProduct(r_ray.dir);
	float a4 = p0minusO.dotProduct(p0minusO) - r*r;
	
	float discriminant = a2 - a3*a4;
	
	if(discriminant<0)
		return -1;
	else{
		float s = std::sqrt(discriminant);
		
		float t1 = (a1 + s)/a3;
		float t2 = (a1 - s)/a3;
		
		if(t1 < t2)
			return t1;
		else
			return t2;
	}

}
