#ifndef POINT_H
#define POINT_H

#include "Vector.h"

class point
{
private:
	double x;
	double y;
	double z;
public:
	point();
	point(double x, double y, double z);
	void setCoords(double x, double y, double z);
	point addVector(const Vector vec) const;
	bool isEqual(const point other) const;
	Vector subtract(const point other) const;
	Vector toVectorFromOrigin() const;

	double getX() const {
		return x;
	}

	double getY() const {
		return y;
	}

	double getZ() const {
		return z;
	}
};

#endif
