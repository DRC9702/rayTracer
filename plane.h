/*
 * plane.h
 *
 *  Created on: Oct 11, 2016
 *      Author: dr2884
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "surface.h"

class plane: public surface {
public:
	vector normal;
	double originDistance; //distance between origin and closest point on plane in direction of normal
	plane();
	plane(vector normal, double originDistance);
	plane(double nx, double ny, double nz, double originDistance);
	plane(point p1, point p2, point p3);
	virtual ~plane(); //I think this is called a deconstructor. Not quite sure what it does.
	vector getNormal();
	double getOriginDistance();
	double intersectT(ray r_ray);
	vector getSurfaceNormal(point p);
};

#endif /* PLANE_H_ */
