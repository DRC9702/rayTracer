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
	float originDistance; //distance between origin and closest point on plane in direction of normal
	plane();
	plane(vector normal, float originDistance);
	plane(float nx, float ny, float nz, float originDistance);
	plane(point p1, point p2, point p3);
	virtual ~plane(); //I think this is called a deconstructor. Not quite sure what it does.
	vector getNormal();
	float getOriginDistance();
	float intersectT(ray r_ray);
	vector getSurfaceNormal(point p);
};

#endif /* PLANE_H_ */
