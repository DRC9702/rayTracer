#include "rgbTriple.h"

#ifndef MATERIAL_H
#define MATERIAL_H


class material
{
public:
	//Diffuse components
	rgbTriple diffuse;
	//Specular components
	rgbTriple specular;
	//roughness phong exponent
	double r;
	//ideal specular components
	rgbTriple idealSpec;
	material();
	material(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib);
	void setMaterial(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib);
};

#endif
