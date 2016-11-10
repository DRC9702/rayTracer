/*
 * BvhNode.h
 *
 *  Created on: Nov 9, 2016
 *      Author: david
 */

#ifndef BVHNODE_H_
#define BVHNODE_H_

#include "surface.h"
#include <vector>

class HitRecord{
public:
	int surfaceIndex = -1;
	double tVal = -1;
};


class BvhNode: public surface { //No real need to make it extend surface that I can see yet
private:
	surface *leftSurface;
	surface *rightSurface;
	BBox thisBox;
public:
	BvhNode();
//	virtual bool hit (ray r, double t0, double t1, Intersection intersectRecord, int BBoxFlag);
//	Intersection checkIntersectWithBBox(const ray r_ray, int BBoxFlag) const;
	virtual bool hit(ray r, double t0, double t1, HitRecord &HR,int BBoxFlag);
	//Tree Creation
	void create(std::vector<surface*> &surfaceList, int axis);
	virtual ~BvhNode();
};


#endif /* BVHNODE_H_ */


