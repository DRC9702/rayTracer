#include "surface.h"
#include "ray.h"
#include "vector.h"
#include "point.h"

surface::surface()
{
	mat = new material();
}

void surface::setMaterial(material* input_mat_p)
{
	mat = input_mat_p;
}
material* surface::getMaterial()
{
	return mat;
}

float surface::intersectT(ray r)
{
	return -1;
}
