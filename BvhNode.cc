/*
 * BvhNode.cc
 *
 *  Created on: Nov 9, 2016
 *      Author: david
 */

#include "BvhNode.h"

//bool BvhNode::hit (ray r, double t0, double t1, Intersection intersectRecord, int BBoxFlag){

bool BvhNode::hit(ray r, double t0, double t1, HitRecord &HR,int BBoxFlag){
	Intersection outsideIntersection = thisBox.checkIntersect(r,BBoxFlag);
	if(outsideIntersection.getVal()<t0 || outsideIntersection.getVal()>t1)
		outsideIntersection = Intersection();

	if(outsideIntersection.isHit()){
		HitRecord leftRec, rightRec;
		bool leftHit, rightHit;

		//leftHit
		if(leftSurface==nullptr)
			leftHit = false;
		else
			leftHit = hit(r,t0,t1,leftRec,BBoxFlag);
		//rightHit
		if(rightSurface==nullptr)
			rightHit = false;
		else
			rightHit = hit(r,t0,t1,rightRec,BBoxFlag);

		if(leftHit && rightHit){
			if(leftRec.tVal < rightRec.tVal)
				HR = leftRec;
			else
				HR = rightRec;
			return true;
		}
		else if(leftHit){
			HR = leftRec;
			return true;
		}
		else if(rightHit){
			HR = rightRec;
			return true;
		}
		//Not sure if this goes here but why not?
		HR.surfaceIndex = thisBox.getSurfaceIndex();
	}
	return false;
}

void BvhNode::create(std::vector<surface*> &surfaceList, int axis){
	unsigned int N = surfaceList.size();

	if(N == 1){
		leftSurface = surfaceList.at(0);
		rightSurface = nullptr;
		thisBox = leftSurface->getBoundingBox();
	}
	else if (N==2){
		leftSurface = surfaceList.at(0);
		rightSurface = surfaceList.at(1);
		thisBox = BBox(leftSurface->getBoundingBox(),rightSurface->getBoundingBox());
	}

}


//bool checkIsLeaf

//BvhNode::BvhNode() {
//	// TODO Auto-generated constructor stub
//
//}

BvhNode::~BvhNode() {
	// TODO Auto-generated destructor stub
}
