/*
 * Intersection.h
 *
 *  Created on: Nov 8, 2016
 *      Author: david
 */

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Vector.h"

class Intersection {
private:
	int materialIndex;
	double tVal;
	Vector surfaceNormal;
	bool hit;

public:
	Intersection();
	Intersection(int materialIndex, double tVal, Vector surfaceNormal);
	virtual ~Intersection();
	bool isHit() const;
	int getMaterialIndex() const;
	const Vector& getSurfaceNormal() const;
	double getVal() const;
};

#endif /* INTERSECTION_H_ */
