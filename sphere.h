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
	float r; //radius
	sphere(point center, float r);
	sphere(float x, float y, float z, float r);
	point getCenter();
	float getRadius();
	//virtual float intersectT(ray r);
	float intersectT(ray r_ray);
};

#endif
