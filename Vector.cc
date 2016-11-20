#include "Vector.h"
#include <iostream>
#include <cmath>

//Constructor
Vector::Vector()
{
	x=0;
	y=0;
	z=0;
}

Vector::Vector(double x, double y, double z)
{
	setComponents(x,y,z);
}

void Vector::setComponents(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool Vector::isEqual(const Vector other) const
{
	if(x==other.getX() && y==other.getY() && z==other.getZ())
		return true;
	else
		return false;
}

double Vector::getMagnitude() const
{
	return std::sqrt( x*x + y*y + z*z );
}

void Vector::applyScalar(const double s)
{
	x *= s;
	y *= s;
	z *= s;
}

Vector Vector::scalarMultiply(const double s) const
{
	return Vector (x*s, y*s, z*s);
}

Vector Vector::add(const Vector other) const
{
	return Vector (x+other.getX(), y+other.getY(), z+other.getZ());
}

Vector Vector::negationVector() const
{
	return scalarMultiply(-1);
}

Vector Vector::subtract(const Vector other) const
{
	return add(other.negationVector());
}

void Vector::addInto(const Vector other){
	this->x += other.getX();
	this->y += other.getY();
	this->z += other.getZ();
}

void Vector::normalize(){
	double m = getMagnitude();
	applyScalar(1/m);
}
Vector Vector::getNormalizedVector() const{
	double m = getMagnitude();
	return scalarMultiply(1/m);
}

//Vector Vector::normalize(){
//	double m = getMagnitude();
//	return scalarMultiply(1/m);
//}

//void Vector::applyNormalization()
//{
//	double m = getMagnitude();
//	applyScalar(1/m);
//}

double Vector::dotProduct(const Vector other) const
{
	return x*other.getX() + y*other.getY() + z*other.getZ();
}

Vector Vector::crossProduct(const Vector other) const
{
	return Vector(y*other.getZ() - z*other.getY(), z*other.getX() - x*other.getZ(), x*other.getY() - y*other.getX());
}
