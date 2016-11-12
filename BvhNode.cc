/*
 * BvhNode.cc
 *
 *  Created on: Nov 9, 2016
 *      Author: david
 */

#include "BvhNode.h"
#include <algorithm>

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

bool compareX(surface* a, surface* b){
	return a->getBoundingBox().compare(b->getBoundingBox(),0);
}

bool compareY(const surface* a, const surface* b){
	return a->getBoundingBox().compare(b->getBoundingBox(),1);
}

bool compareZ(const surface* a, const surface* b){
	return a->getBoundingBox().compare(b->getBoundingBox(),2);
}

void BvhNode::create(std::vector<surface*>::iterator begin, std::vector<surface*>::iterator end, int axis){
	unsigned int N = end-begin;

	if(N == 1){
		leftSurface = *begin;
		rightSurface = nullptr;
		thisBox = leftSurface->getBoundingBox();
	}
	else if (N==2){
		leftSurface = *begin;
		rightSurface = *(begin+1);
		thisBox = BBox(leftSurface->getBoundingBox(),rightSurface->getBoundingBox());
	}
	else{
		switch(axis){
			case 0: std::sort(begin,end,compareX); break;
			case 1: std::sort(begin,end,compareY); break;
			case 2: std::sort(begin,end,compareZ); break;
		}
		BvhNode *leftNode = new BvhNode();
		leftNode->create(begin, begin + (end-begin)/2, (axis+1)%3);
		leftSurface = leftNode;
		BvhNode *rightNode = new BvhNode();
		rightNode->create(begin + (end-begin)/2, end, (axis+1)%3);
		rightSurface = rightNode;
		thisBox = BBox(leftSurface->getBoundingBox(),rightSurface->getBoundingBox());
	}
}


//bool checkIsLeaf

BvhNode::BvhNode() {
	// TODO Auto-generated constructor stub

}

BvhNode::~BvhNode() {
	// TODO Auto-generated destructor stub
}
