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
	int surfaceIndex=-1;
public:
	BBox(); //Don't know what to do with this guy
	BBox(point minVals, point maxVals, int surfaceIndex);
	int getSurfaceIndex() const;
	//double intersectRay(const ray& r) const;
	Intersection checkIntersect(const ray& r,int materialIndex) const;
	//double BBox::intersectRay(const ray& r) const;
	const point& getMaxVals() const;
	const point& getMinVals() const;
	double getMinX() const;
	double getMinY() const;
	double getMinZ() const;
	double getMaxX() const;
	double getMaxY() const;
	double getMaxZ() const;
	BBox(const BBox box1, const BBox box2);
	bool compare(const BBox other,int axis) const;
	virtual ~BBox();
};

#endif /* BBOX_H_ */
