/*
 * BBox.h
 *
 *  Created on: Nov 6, 2016
 *      Author: dr2884
 */

#ifndef BBOX_H_
#define BBOX_H_

#include "point.h"
#include "ray.h"
#include "Intersection.h"

class BBox {
private:
	point minVals;
	point maxVals;
public:
	BBox(); //Don't know what to do with this guy
	BBox(point minVals, point maxVals);
	//double intersectRay(const ray& r) const;
	Intersection checkIntersect(const ray& r) const;
	virtual ~BBox();
};

#endif /* BBOX_H_ */
