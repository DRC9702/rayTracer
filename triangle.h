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
public:
	triangle();
	virtual ~triangle();
	triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
	triangle(const point p1, const point p2, const point p3);
	void initBBox();
	void initTrianglePlane();
	Vector getNormal() const;
	plane getPlane() const;
	double intersectT(const ray r_ray) const;
	Intersection checkIntersect(const ray r_ray) const;
	bool barycentricInsideTriangle(const point p) const;
	bool crossProductInsideTriangle(const point p) const;
	bool checkIfRaySameDirectionAsNormal(const ray ray_r) const;
	Vector getSurfaceNormal(const point p) const;
};

#endif /* TRIANGLE_H_ */
