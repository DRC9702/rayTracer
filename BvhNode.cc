/*
 * BvhNode.cc
 *
 *  Created on: Nov 9, 2016
 *      Author: david
 */

#include "BvhNode.h"

//bool BvhNode::hit (ray r, double t0, double t1, Intersection intersectRecord, int BBoxFlag){

bool BvhNode::hit(ray r, double t0, double t1, &hitRecord,int BBoxFlag){
	Intersection outsideIntersection = thisBox.checkIntersect(r,intBBoxFlag)
	if(thisBox.)
}

bool checkIsLeaf

//BvhNode::BvhNode() {
//	// TODO Auto-generated constructor stub
//
//}

BvhNode::~BvhNode() {
	// TODO Auto-generated destructor stub
}

class hitRecord{
public:
	int surfaceIndex = -1;
	double tVal = -1;
};
