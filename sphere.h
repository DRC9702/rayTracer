#include "surface.h"
#include "ray.h"
#include "vector.h"
#include "point.h"
#include <cmath>

#ifndef SPHERE_H
#define SPHERE_H


class sphere : public surface
{
public:
	point center; //origin
	double r; //radius
	sphere(point center, double r);
	sphere(double x, double y, double z, double r);
	point getCenter();
	double getRadius();
	//virtual double intersectT(ray r);
	double intersectT(ray r_ray);
	vector getSurfaceNormal(point p);
};

#endif
