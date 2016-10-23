#include "vector.h"
#include "point.h"

#ifndef RAY_H
#define RAY_H


class ray
{
private:
	point origin;
	vector dir; //Make sure this is always normalized
public:
	ray();
	ray(const point origin, const vector dir);
	ray(const double px, const double py, const double pz, const double vx, double vy, double vz);
	ray(const point p1, const point p2);
	void setOrigin(const point p);
	void setOrigin(const double px, const double py, const double pz);
	void setDir(const vector v);
	void setDir(const double vx, const double vy, const double vz);
	bool isEqual(const ray other) const;
	point getPointFromT(const double t) const;

	const vector& getDir() const {
		return dir;
	}

	const point& getOrigin() const {
		return origin;
	}
};

#endif
