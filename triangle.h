/*
 * triangle.h
 *
 *  Created on: Oct 20, 2016
 *      Author: david
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "surface.h"
#include "plane.h"

class triangle: public surface {
private:
	point p1, p2, p3;
	Vector normal;
	plane trianglePlane;
	int surfaceIndex;
	Vector N1, N2, N3;
public:
	triangle();
	virtual ~triangle();
	triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, int surfaceIndex);
	triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, int surfaceIndex, bool objTriangle);
	triangle(const point p1, const point p2, const point p3, int surfaceIndex);
	int getSurfaceIndex();
	void initBBox();
	void initTrianglePlane();
	Vector getNormal() const;
	plane getPlane() const;
	double intersectT(const ray r_ray, Vector &smoothNormal) const;
	Intersection checkIntersect(const ray r_ray) const;
	bool barycentricInsideTriangle(const point p, Vector &smoothNormal) const;
	bool crossProductInsideTriangle(const point p) const;
	bool checkIfRaySameDirectionAsNormal(const ray ray_r) const;
	Vector getSurfaceNormal(const point p) const;
	bool intersectHit(ray r, double &bestT, Intersection &intersect) const;
	const Vector& getN1() const;
	void setN1(const Vector& n1);
	const Vector& getN2() const;
	void setN2(const Vector& n2);
	const Vector& getN3() const;
	void setN3(const Vector& n3);
	void setSurfaceIndex(int surfaceIndex);
};

#endif /* TRIANGLE_H_ */
