#include "ray.h"
#include "vector.h"
#include "point.h"
#include "material.h"

#ifndef SURFACE_H
#define SURFACE_H


class surface
{
public:
	material* mat;
	surface();
	void setMaterial(material* input_mat_p);
	material* getMaterial();
	virtual float intersectT(ray r);
};

#endif
