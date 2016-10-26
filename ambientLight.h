/*
 * ambientLight.h
 *
 *  Created on: Oct 26, 2016
 *      Author: dr2884
 */

#include "rgbTriple.h"

#ifndef AMBIENTLIGHT_H_
#define AMBIENTLIGHT_H_

class ambientLight {
private:
	rgbTriple lightValue; //I prefer RGB over just indices. //It makes it easier for me to read the code //All of these should be between 0 and 1
public:
	ambientLight();
	ambientLight(double r, double g, double b);
	virtual ~ambientLight();
	const rgbTriple& getLightValue() const {
		return lightValue;
	}

};
#endif /* AMBIENTLIGHT_H_ */
