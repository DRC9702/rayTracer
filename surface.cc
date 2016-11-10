#include "surface.h"

#include <iostream>

#include <stdexcept> //This should let me throw standard exceptions

static int USE_BVH_TREE = 2;
static int NO_BVH_TREE = 0;
static int BBOXED = 1;

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

void surface::setBoundingBox(BBox inBox){
	boundingBox = inBox;
}

int surface::getMaterialIndex() const
{
	return materialIndex;
}

Intersection surface::checkIntersectWithBBox(const ray r_ray, int BBoxFlag) const{
	if(BBoxFlag==BBOXED){
		//std::cout << "BBox is one: " << getBoundingBox().checkIntersect(r_ray).isHit() << std::endl;
		return getBoundingBox().checkIntersect(r_ray, getMaterialIndex());
	}
	else if(BBoxFlag==USE_BVH_TREE){
		Intersection  intersect1 = getBoundingBox().checkIntersect(r_ray, getMaterialIndex());
		if(intersect1.isHit()){
			return checkIntersect(r_ray);
		}
		else{
			return intersect1;
		}
	}
	else{ //BBoxFlag==0
		return checkIntersect(r_ray);
	}
}

Intersection surface::checkIntersect(const ray r_ray) const{
	std::cout <<"The virtual surface method checkIntersect is being called." << std::endl;
	return Intersection();
}

/*
double surface::intersectWithBBox(const ray r_ray, bool useBBox) const{
	if(useBBox){
		//std::cout<<"Checking if intersection with bounding box: " << boundingBox.intersectRay(r_ray) << std::endl;
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
*/
Vector surface::getSurfaceNormal(const point p) const{
	std::cout <<"THE VIRTUAL SURFACE METHOD getSurfaceNormal IS BEING CALLED" << std::endl;
	return Vector();
}

const BBox& surface::getBoundingBox() const {
	return boundingBox;
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
