/*
 * triangle.cc
 *
 *  Created on: Oct 20, 2016
 *      Author: david
 */

#include "triangle.h"
#include <algorithm> //So I can use min and max

triangle::triangle() {
	p1 = point(1,0,0);
	p2 = point(0,1,0);
	p3 = point(0,0,1);
	surfaceIndex=0;
	initTrianglePlane();
	initBBox();
	normal = trianglePlane.getNormal();
}

triangle::triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, int surfaceIndex){
	p1 = point(x1,y1,z1);
	p2 = point(x2,y2,z2);
	p3 = point(x3,y3,z3);
	this->surfaceIndex = surfaceIndex;
	initTrianglePlane();
	initBBox();
	normal = trianglePlane.getNormal();
}
triangle::triangle(point p1, point p2, point p3, int surfaceIndex){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->surfaceIndex=surfaceIndex;
	initTrianglePlane();
	initBBox();
	normal = trianglePlane.getNormal();
}

void triangle::initBBox(){
	double xMin = std::min(p1.getX(),std::min(p2.getX(),p3.getX()));
	double xMax = std::max(p1.getX(),std::max(p2.getX(),p3.getX()));

	double yMin = std::min(p1.getY(),std::min(p2.getY(),p3.getY()));
	double yMax = std::max(p1.getY(),std::max(p2.getY(),p3.getY()));

	double zMin = std::min(p1.getZ(),std::min(p2.getZ(),p3.getZ()));
	double zMax = std::max(p1.getZ(),std::max(p2.getZ(),p3.getZ()));

	setBoundingBox(BBox(point(xMin,yMin,zMin), point(xMax,yMax,zMax),getSurfaceIndex()));
}

int triangle::getSurfaceIndex(){
	return surfaceIndex;
}

void triangle::initTrianglePlane(){
	trianglePlane = plane(p1,p2,p3);
}

Vector triangle::getNormal() const{
	return normal;
}
plane triangle::getPlane() const{
	return trianglePlane;
}



Intersection triangle::checkIntersect(const ray r_ray) const{
	double tVal = intersectT(r_ray);
	if(tVal < 0) //Miss
		return Intersection();
	else
		return Intersection(getMaterialIndex(), tVal, getSurfaceNormal(r_ray.getPointFromT(tVal)));
}


double triangle::intersectT(const ray r_ray) const{
//	if(checkIfRaySameDirectionAsNormal(r_ray)) //This works!
//		return -1;

	double T = trianglePlane.intersectT(r_ray); //This definitely works by now.
	if(T < 0){
		return -1;
	}

	point p = r_ray.getPointFromT(T);
	//Gonna use the barycentric method for now

	bool isInside = barycentricInsideTriangle(p);
//	bool isInside = crossProductInsideTriangle(p);
	if(isInside)
		return T;
	else
		return -1;

	return T;
}

bool triangle::crossProductInsideTriangle(const point p) const{
	Vector AB = p2.subtract(p1);
	Vector BC = p3.subtract(p2);
	Vector CA = p1.subtract(p3);

	Vector AP = p.subtract(p1);
	Vector BP = p.subtract(p2);
	Vector CP = p.subtract(p3);

	Vector n1 = AB.crossProduct(AP);
	Vector n2 = BC.crossProduct(BP);
	Vector n3 = CA.crossProduct(CP);

	if(normal.dotProduct(n1) < 0)
		return false;
	if(normal.dotProduct(n2) < 0)
		return false;
	if(normal.dotProduct(n3) < 0)
		return false;
	return true;
}

bool triangle::barycentricInsideTriangle(const point p) const{
	Vector A = p1.toVectorFromOrigin();
	Vector B = p2.toVectorFromOrigin();
	Vector C = p3.toVectorFromOrigin();

	Vector P = p.toVectorFromOrigin();

	Vector AB = B.subtract(A);
	Vector BC = C.subtract(B);
	Vector CA = A.subtract(C);

	//double areaABC = AB.crossProduct(C.subtract(A)).getMagnitude()/2;
	Vector AC = C.subtract(A);
	Vector N = AB.crossProduct(AC);

	Vector BP = P.subtract(B);
	Vector CP = P.subtract(C);
	Vector AP = P.subtract(A);


	Vector na = BC.crossProduct(BP);
	Vector nb = CA.crossProduct(CP);
	Vector nc = AB.crossProduct(AP);

	double alpha = (N.dotProduct(na))/ (N.dotProduct(N));
	double beta = (N.dotProduct(nb))/ (N.dotProduct(N));
	double gamma = (N.dotProduct(nc))/ (N.dotProduct(N));

	if(alpha < 0 || alpha > 1)
		return false;
	if(beta<0 || beta>1)
		return false;
	if(gamma<0 || gamma>1)
		return false;

	return true;
}

bool triangle::checkIfRaySameDirectionAsNormal(const ray r_ray) const{
	if(	r_ray.getDir().dotProduct(normal) > 0 )
		return true;
	else
		return false;
}

Vector triangle::getSurfaceNormal(const point p) const{
	return normal;
}

triangle::~triangle() {
	// TODO Auto-generated destructor stub
}

bool triangle::intersectHit(ray r, double bestT, Intersection &intersect) const{
	if(RENDER_BOX_FLAG==BBOXED){
		//return getBoundingBox().checkIntersect(r, getMaterialIndex());
		intersect = getBoundingBox().checkIntersect(r, getMaterialIndex());
		return intersect.isHit();

	}
	else if(RENDER_BOX_FLAG==USE_BVH_TREE){
		Intersection  intersect1 = getBoundingBox().checkIntersect(r, getMaterialIndex());
		if(intersect1.isHit()){
			intersect = checkIntersect(r);
			return intersect.isHit();
		}
		else{
			intersect = intersect1;
			return intersect.isHit();
		}
	}
	else{ //BBoxFlag==0
		intersect = checkIntersect(r);
		return intersect.isHit();
	}
}
