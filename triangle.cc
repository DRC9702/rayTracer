/*
 * triangle.cc
 *
 *  Created on: Oct 20, 2016
 *      Author: david
 */

#include "triangle.h"

triangle::triangle() {
	p1 = point(1,0,0);
	p2 = point(0,1,0);
	p3 = point(0,0,1);
	initTrianglePlane();
	normal = trianglePlane.getNormal();
}

triangle::triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3){
	p1 = point(x1,y1,z1);
	p2 = point(x2,y2,z2);
	p3 = point(x3,y3,z3);
	initTrianglePlane();
	normal = trianglePlane.getNormal();
}
triangle::triangle(point p1, point p2, point p3){
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	initTrianglePlane();
	normal = trianglePlane.getNormal();
}

void triangle::initTrianglePlane(){
	trianglePlane = plane(p1,p2,p3);
}

vector triangle::getNormal(){
	return normal;
}
plane triangle::getPlane(){
	return trianglePlane;
}

double triangle::intersectT(ray r_ray){
	if(checkIfRaySameDirectionAsNormal(r_ray)) //This works!
		return -1;

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

bool triangle::crossProductInsideTriangle(point p){
	vector AB = p2.subtract(p1);
	vector BC = p3.subtract(p2);
	vector CA = p1.subtract(p3);

	vector AP = p.subtract(p1);
	vector BP = p.subtract(p2);
	vector CP = p.subtract(p3);

	vector n1 = AB.crossProduct(AP);
	vector n2 = BC.crossProduct(BP);
	vector n3 = CA.crossProduct(CP);

	if(normal.dotProduct(n1) < 0)
		return false;
	if(normal.dotProduct(n2) < 0)
		return false;
	if(normal.dotProduct(n3) < 0)
		return false;
	return true;
}

bool triangle::barycentricInsideTriangle(point p){
	vector A = p1.toVectorFromOrigin();
	vector B = p2.toVectorFromOrigin();
	vector C = p3.toVectorFromOrigin();

	vector P = p.toVectorFromOrigin();

	vector AB = B.subtract(A);
	vector BC = C.subtract(B);
	vector CA = A.subtract(C);

	//double areaABC = AB.crossProduct(C.subtract(A)).getMagnitude()/2;
	vector AC = C.subtract(A);
	vector N = AB.crossProduct(AC);

	vector BP = P.subtract(B);
	vector CP = P.subtract(C);
	vector AP = P.subtract(A);


	vector na = BC.crossProduct(BP);
	vector nb = CA.crossProduct(CP);
	vector nc = AB.crossProduct(AP);

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

bool triangle::checkIfRaySameDirectionAsNormal(ray r_ray){
	if(	r_ray.dir.dotProduct(normal) > 0 )
		return true;
	else
		return false;
}

vector triangle::getSurfaceNormal(point p){
	return normal;
}

triangle::~triangle() {
	// TODO Auto-generated destructor stub
}

