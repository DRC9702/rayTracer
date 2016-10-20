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
	vector normal;
	plane trianglePlane;
public:
	triangle();
	virtual ~triangle();
	triangle(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);
	triangle(point p1, point p2, point p3);
	void initTrianglePlane();
	vector getNormal();
	plane getPlane();
	double intersectT(ray r_ray);
	bool barycentricInsideTriangle(point p);
	bool crossProductInsideTriangle(point p);
	bool checkIfRaySameDirectionAsNormal(ray ray_r);
	vector getSurfaceNormal(point p);
};

#endif /* TRIANGLE_H_ */
