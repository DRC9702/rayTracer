#include "ray.h"
#include "point.h"
#include "vector.h"

//Constructor

ray::ray(){
	origin = point();
	dir = vector().getNormalizedVector();
}

ray::ray(const point origin, const vector dir) //Will normalize the input vector
{
	setOrigin(origin);
	setDir(dir);
}

ray::ray(const double px, const double py, const double pz, const double vx, const double vy, const double vz)
{
	setOrigin(px,py,pz);
	setDir(vx,vy,vz);
}

ray::ray(const point p1, const point p2){
	setOrigin(p1);
	vector vec = p2.subtract(p1);
	setDir(vec);
}

void ray::setOrigin(const point p)
{
	origin=p;
}

void ray::setOrigin(const double px, const double py, const double pz)
{
	point p (px, py, pz);
	setOrigin(p);
}

void ray::setDir(const vector v)
{
	dir = v.getNormalizedVector();
}

void ray::setDir(const double vx, const double vy, const double vz)
{
	vector v (vx, vy, vz);
	setDir(v);
}

bool ray::isEqual(const ray other) const{
	if(	origin.isEqual(other.origin) && dir.isEqual(other.dir)	)
		return true;
	else
		return false;
}

point ray::getPointFromT(const double t) const{
	return origin.addVector(dir.scalarMultiply(t));
}

