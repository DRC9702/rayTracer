/*
 * BvhNode.h
 *
 *  Created on: Nov 9, 2016
 *      Author: david
 */

#ifndef BVHNODE_H_
#define BVHNODE_H_

#include "surface.h"

class BvhNode: public surface {
private:
	surface *leftSurface;
	surface *rightSurface;
	BBox thisBox;
public:
	BvhNode();
//	virtual bool hit (ray r, double t0, double t1, Intersection intersectRecord, int BBoxFlag);
//	Intersection checkIntersectWithBBox(const ray r_ray, int BBoxFlag) const;
	virtual ~BvhNode();
};


#endif /* BVHNODE_H_ */
