#include "surface.h"
#include "ray.h"
#include "Vector.h"
#include "point.h"

#ifndef SPHERE_H
#define SPHERE_H


class sphere : public surface
{
private:
	point center; //origin
	double radius; //radius
	int surfaceIndex;
public:
	sphere(const point center, const double radius, const int surfaceIndex);
	sphere(const double x, const double y, const double z, const double radius, const int surfaceIndex);
	//virtual double intersectT(ray r);
	void initBBox();
	double intersectT(const ray r_ray) const;
	Intersection checkIntersect(const ray r_ray) const;
	Vector getSurfaceNormal(const point p) const;

	const point& getCenter() const {
		return center;
	}

	double getRadius() const {
		return radius;
	}
	int getSurfaceIndex() const{
		return surfaceIndex;
	}
};

#endif
