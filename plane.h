/*
 * plane.h
 *
 *  Created on: Oct 11, 2016
 *      Author: dr2884
 */

#ifndef PLANE_H_
#define PLANE_H_

#include "surface.h"

//class plane: public surface {
class plane{
private:
	Vector normal;
	double originDistance; //distance between origin and closest point on plane in direction of normal
public:
	plane();
	plane(const Vector normal, const double originDistance);
	plane(double nx, double ny, double nz, double originDistance);
	plane(const point p1, const point p2, const point p3);
	virtual ~plane(); //I think this is called a deconstructor. Not quite sure what it does.
	Vector getNormal() const;
	double getOriginDistance() const;
	double intersectT(const ray r_ray) const;
	Vector getSurfaceNormal(const point p) const;
};

#endif /* PLANE_H_ */
