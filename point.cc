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

point::point(int x, int y, int z)
{
	setCoords(x,y,z);
}

void point::setCoords(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

point point::addVector(vector vec)
{
	return point(x+vec.x, y+vec.y, z+vec.z);
}

bool point::isEqual(point other){
	if(x==other.x && y==other.y && z==other.z)
		return true;
	else
		return false;
}

vector point::subtract(point other){
	return vector(x-other.x, y-other.y, z-other.z);
}
