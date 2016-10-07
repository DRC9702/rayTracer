#ifndef POINT_H
#define POINT_H

#include "vector.h"

class point
{
public:
	int x;
	int y;
	int z;
	point();
	point(int x, int y, int z);
	void setCoords(int x, int y, int z);
	point addVector(vector vec);
	bool isEqual(point other);
	vector subtract(point other);
};

#endif
