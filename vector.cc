#include "vector.h"
#include <iostream>
#include <cmath>

//Constructor
vector::vector()
{
	x=0;
	y=0;
	z=0;
}

vector::vector(float x, float y, float z)
{
	setComponents(x,y,z);
}

void vector::setComponents(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool vector::isEqual(vector other)
{
	if(x==other.x && y==other.y && z==other.z)
		return true;
	else
		return false;
}

float vector::getMagnitude()
{
	return std::sqrt( x*x + y*y + z*z );
}

void vector::applyScalar(float s)
{
	x *= s;
	y *= s;
	z *= s;
}

vector vector::scalarMultiply(float s)
{
	return vector (x*s, y*s, z*s);
}

vector vector::add(vector other)
{
	return vector (x+other.x, y+other.y, z+other.z);
}

vector vector::negationVector()
{
	return scalarMultiply(-1);
}

vector vector::subtract(vector other)
{
	return add(other.negationVector());
}

vector vector::normalize(){
	float m = getMagnitude();
	return scalarMultiply(1/m);
}

void vector::applyNormalization()
{
	float m = getMagnitude();
	applyScalar(1/m);
}

float vector::dotProduct(vector other)
{
	return x*other.x + y*other.y + z*other.z;
}

vector vector::crossProduct(vector other)
{
	return vector(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}
