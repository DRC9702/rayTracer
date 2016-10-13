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

double surface::intersectT(ray r)
{
	std::cout <<"The virtual surface method inersectT is being called." << std::endl;
	return -1;
}

vector surface::getSurfaceNormal(point p){
	std::cout <<"THE VIRTUAL SURFACE METHOD getSurfaceNormal IS BEING CALLED" << std::endl;
	return vector();
}

surface::~surface() {
	// TODO Auto-generated destructor stub
}
