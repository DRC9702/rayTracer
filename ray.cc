#include "ray.h"
#include "point.h"
#include "vector.h"

//Constructor

ray::ray(){
	origin = point();
	dir = vector();
}

ray::ray(point origin, vector dir) //Will normalize the input vector
{
	setOrigin(origin);
	setDir(dir);
}

ray::ray(float px, float py, float pz, float vx, float vy, float vz)
{
	setOrigin(px,py,pz);
	setDir(vx,vy,vz);
}

ray::ray(point p1, point p2){
	setOrigin(p1);
	vector vec = p2.subtract(p1);
	setDir(vec);
}

void ray::setOrigin(point p)
{
	origin=p;
}

void ray::setOrigin(float px, float py, float pz)
{
	point p (px, py, pz);
	setOrigin(p);
}

void ray::setDir(vector v)
{
	dir = v;
	dir.applyNormalization();
}

void ray::setDir(float vx, float vy, float vz)
{
	vector v (vx, vy, vz);
	setDir(v);
}

bool ray::isEqual(ray other){
	if(	origin.isEqual(other.origin) && dir.isEqual(other.dir)	)
		return true;
	else
		return false;
}

point ray::getPointFromT(float t){
	return origin.addVector(dir.scalarMultiply(t));
}

