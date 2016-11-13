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


class BvhNode: public surface { //No real need to make it extend surface that I can see yet
//private:
//	surface *leftSurface;
//	surface *rightSurface;
public:
	surface *leftSurface;
	surface *rightSurface;
	BvhNode();
//	virtual bool hit (ray r, double t0, double t1, Intersection intersectRecord, int BBoxFlag);
//	Intersection checkIntersectWithBBox(const ray r_ray, int BBoxFlag) const;
//	virtual bool hit(ray r, double t0, double t1, HitRecord &HR,int BBoxFlag);
	bool intersectHit(ray r, double bestT, Intersection &intersect) const;
	//Tree Creation
	void create(std::vector<surface*>::iterator begin, std::vector<surface*>::iterator end, int axis);
	virtual ~BvhNode();
//	bool compareX(surface* a, surface* b);
//	bool compareY(const surface* a, const surface* b);
//	bool compareZ(const surface* a, const surface* b);
};


#endif /* BVHNODE_H_ */


