#include<iostream>
#include "point.h"
#include "vector.h"

//Constructor
point::point ()
{
	x=0;
	y=0;
	z=0;
}

point::point(double x, double y, double z)
{
	setCoords(x,y,z);
}

void point::setCoords(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

point point::addVector(const vector vec) const
{
	return point(x+vec.getX(), y+vec.getY(), z+vec.getZ());
}

bool point::isEqual(const point other) const{
	if(x==other.getX() && y==other.getY() && z==other.getZ())
		return true;
	else
		return false;
}

vector point::subtract(const point other) const{
	return vector(x-other.getX(), y-other.getY(), z-other.getZ());
}

vector point::toVectorFromOrigin() const{
	return subtract(point(0,0,0));
}

