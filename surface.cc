#include "surface.h"
#include "ray.h"
#include "vector.h"
#include "point.h"

#include <iostream>

surface::surface()
{
	//mat = new material();
	materialIndex=0; //Default material
}

//void surface::setMaterial(material* input_mat_p)
//{
//	mat = input_mat_p;
//}
//material* surface::getMaterial()
//{
//	return mat;
//}

void surface::setMaterialIndex(int n)
{
	materialIndex = n;
}

int surface::getMaterialIndex()
{
	return materialIndex;
}

float surface::intersectT(ray r)
{
	return -1;
}

vector surface::getSurfaceNormal(point p){
	//std::cout <<"THE VIRTUAL SURFACE METHOD IS BEING CALLED" << std::endl;
	return vector();
}
