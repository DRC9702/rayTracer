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

vector::vector(double x, double y, double z)
{
	setComponents(x,y,z);
}

void vector::setComponents(double x, double y, double z)
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

double vector::getMagnitude()
{
	return std::sqrt( x*x + y*y + z*z );
}

void vector::applyScalar(double s)
{
	x *= s;
	y *= s;
	z *= s;
}

vector vector::scalarMultiply(double s)
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

void vector::normalize(){
	double m = getMagnitude();
	applyScalar(1/m);
}
vector vector::getNormalizedVector(){
	double m = getMagnitude();
	return scalarMultiply(1/m);
}

//vector vector::normalize(){
//	double m = getMagnitude();
//	return scalarMultiply(1/m);
//}

//void vector::applyNormalization()
//{
//	double m = getMagnitude();
//	applyScalar(1/m);
//}

double vector::dotProduct(const vector other)
{
	return x*other.x + y*other.y + z*other.z;
}

vector vector::crossProduct(vector other)
{
	return vector(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}
