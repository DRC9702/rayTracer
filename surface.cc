#include "surface.h"

#include <iostream>

#include <stdexcept> //This should let me throw standard exceptions

surface::surface()
{
	//mat = new material();
	materialIndex=0; //Default material
	boundingBox = BBox();
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

int surface::getMaterialIndex() const
{
	return materialIndex;
}

double surface::intersectWithBBox(const ray r_ray, bool useBBox) const{
	if(useBBox){
		return boundingBox.intersectRay(r_ray);
	}
	else{
		return intersectT(r_ray);
	}
}

double surface::intersectT(const ray r) const
{
	std::cout <<"The virtual surface method inersectT is being called." << std::endl;
	return -1;
}

Vector surface::getSurfaceNormal(const point p) const{
	std::cout <<"THE VIRTUAL SURFACE METHOD getSurfaceNormal IS BEING CALLED" << std::endl;
	return Vector();
}

bool surface::checkIfRaySameDirectionAsNormal(const ray r_ray, const point p) const{
	if(	r_ray.getDir().dotProduct(getSurfaceNormal(p)) > 0 )
		return true;
	else
		return false;
}


surface::~surface() {
	// TODO Auto-generated destructor stub
}
