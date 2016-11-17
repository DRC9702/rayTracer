/*
 * areaLight.h
 *
 *  Created on: Nov 17, 2016
 *      Author: david
 */

#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "Light.h"
#include "point.h"
#include "Vector.h"
#include "rgbTriple.h"


class areaLight : public Light{
private:
	Vector direction;
	Vector uvector;
	Vector vvector;
	double len;
	point blCorner;
public:
	areaLight(double x, double y, double z, double nx, double ny, double nz,
			double ux, double uy, double uz, double len, double r, double g, double b);
	virtual ~areaLight();
	const rgbTriple& getColor() const;
	const Vector& getDirection() const;
	double getLen() const;
	const Vector& getUvector() const;
	const Vector& getVvector() const;
	const point& getblCorner() const;
	const point generateSurfacePoint(int p, int q, int N) const;
};

#endif /* AREALIGHT_H_ */
