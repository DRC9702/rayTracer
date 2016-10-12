#include "vector.h"
#include "point.h"

#ifndef RAY_H
#define RAY_H


class ray
{
public:
	point origin;
	vector dir; //Make sure this is always normalized
	ray();
	ray(point origin, vector dir);
	ray(float px, float py, float pz, float vx, float vy, float vz);
	ray(point p1, point p2);
	void setOrigin(point p);
	void setOrigin(float px, float py, float pz);
	void setDir(vector v);
	void setDir(float vx, float vy, float vz);
	bool isEqual(ray other);
	point getPointFromT(float t);
};

#endif
