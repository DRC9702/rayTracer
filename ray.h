#include "Vector.h"
#include "point.h"

#ifndef RAY_H
#define RAY_H


class ray
{
private:
	point origin;
	Vector dir; //Make sure this is always normalized
public:
	ray();
	ray(const point origin, const Vector dir);
	ray(const double px, const double py, const double pz, const double vx, double vy, double vz);
	ray(const point p1, const point p2);
	void setOrigin(const point p);
	void setOrigin(const double px, const double py, const double pz);
	void setDir(const Vector v);
	void setDir(const double vx, const double vy, const double vz);
	bool isEqual(const ray other) const;
	point getPointFromT(const double t) const;

	const Vector& getDir() const {
		return dir;
	}

	const point& getOrigin() const {
		return origin;
	}
};

#endif
