/*
 * BvhNode.cc
 *
 *  Created on: Nov 9, 2016
 *      Author: david
 */

#include "BvhNode.h"
#include <algorithm>
#include <iostream>

//bool BvhNode::hit (ray r, double t0, double t1, Intersection intersectRecord, int BBoxFlag){

bool BvhNode::intersectHit(ray r, double bestT, Intersection &intersect){
	Intersection outsideIntersection = getBoundingBox().checkIntersect(r,0);
	if(!(outsideIntersection.getVal()<bestT || outsideIntersection.getVal()>0.001))
		outsideIntersection = Intersection();

	if(outsideIntersection.isHit()){
//		std::cout << "hit outside bounding box checking" << std::endl;
		Intersection leftRec, rightRec;
		bool leftHit = false;
		bool rightHit = false;

		//leftHit
		if(leftSurface==nullptr)
			leftHit = false;
		else{
			std::cout << "leftHit checking" << std::endl;
			leftHit = leftSurface->intersectHit(r,bestT,leftRec);
			std::cout << "Hello!" << std::endl;
			std::cout << &leftRec << std::endl;
		}
		//rightHit
		if(rightSurface==nullptr)
			rightHit = false;
		else
			rightHit = rightSurface->intersectHit(r,bestT,rightRec);

		if(leftHit && rightHit){
			if(leftRec.getVal() < rightRec.getVal())
				intersect = leftRec;
			else
				intersect = rightRec;
			return true;
		}
		else if(leftHit){
			intersect = leftRec;
//			std::cout << "Intersection with left child." << std::endl;
			return true;
		}
		else if(rightHit){
			intersect = rightRec;
			return true;
		}
		//Not sure if this goes here but why not?
//		intersect.surfaceIndex = thisBox.getSurfaceIndex();
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
	std::cout << N << std::endl;
	if(N == 1){
		leftSurface = *begin;
		rightSurface = nullptr;
		setBoundingBox(leftSurface->getBoundingBox());
	}
	else if (N==2){
		leftSurface = *begin;
		rightSurface = *(begin+1);
		setBoundingBox(BBox(leftSurface->getBoundingBox(),rightSurface->getBoundingBox()));
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
		setBoundingBox(BBox(leftSurface->getBoundingBox(),rightSurface->getBoundingBox()));
	}
}


//bool checkIsLeaf

BvhNode::BvhNode() {
	// TODO Auto-generated constructor stub

}

BvhNode::~BvhNode() {
	// TODO Auto-generated destructor stub
}
