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
	ray(double px, double py, double pz, double vx, double vy, double vz);
	ray(point p1, point p2);
	void setOrigin(point p);
	void setOrigin(double px, double py, double pz);
	void setDir(vector v);
	void setDir(double vx, double vy, double vz);
	bool isEqual(ray other);
	point getPointFromT(double t);
};

#endif
