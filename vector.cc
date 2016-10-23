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

bool vector::isEqual(const vector other) const
{
	if(x==other.getX() && y==other.getY() && z==other.getZ())
		return true;
	else
		return false;
}

double vector::getMagnitude() const
{
	return std::sqrt( x*x + y*y + z*z );
}

void vector::applyScalar(const double s)
{
	x *= s;
	y *= s;
	z *= s;
}

vector vector::scalarMultiply(const double s) const
{
	return vector (x*s, y*s, z*s);
}

vector vector::add(const vector other) const
{
	return vector (x+other.getX(), y+other.getY(), z+other.getZ());
}

vector vector::negationVector() const
{
	return scalarMultiply(-1);
}

vector vector::subtract(const vector other) const
{
	return add(other.negationVector());
}

void vector::normalize(){
	double m = getMagnitude();
	applyScalar(1/m);
}
vector vector::getNormalizedVector() const{
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

double vector::dotProduct(const vector other) const
{
	return x*other.getX() + y*other.getY() + z*other.getZ();
}

vector vector::crossProduct(const vector other) const
{
	return vector(y*other.getZ() - z*other.getY(), z*other.getX() - x*other.getZ(), x*other.getY() - y*other.getX());
}
