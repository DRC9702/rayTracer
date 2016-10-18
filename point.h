#ifndef POINT_H
#define POINT_H

#include "vector.h"

class point
{
public:
	double x;
	double y;
	double z;
	point();
	point(double x, double y, double z);
	void setCoords(double x, double y, double z);
	point addVector(vector vec);
	bool isEqual(point other);
	vector subtract(point other);
	vector toVectorFromOrigin();
};

#endif
