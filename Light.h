/*
 * Light.h
 *
 *  Created on: Nov 17, 2016
 *      Author: david
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "point.h"
#include "rgbTriple.h"

class Light {
protected:
	point position;
	rgbTriple lightValue;
	bool aLight;
public:
	Light();
	virtual ~Light();
	bool isAreaLight() const;
	const rgbTriple& getLightValue() const;
	const point& getPosition() const;
};

#endif /* LIGHT_H_ */
