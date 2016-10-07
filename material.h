#ifndef MATERIAL_H
#define MATERIAL_H


class material
{
public:
	//Diffuse components
	float dr;
	float dg;
	float db;
	//Specular components
	float sr;
	float sg;
	float sb;
	//roughness phong exponent
	float r;
	//ideal specular components
	float ir;
	float ig;
	float ib;
	material();
	material(float dr, float dg, float db, float sr, float sg, float sb, float r, float ir, float ig, float ib);
	void setMaterial(float dr, float dg, float db, float sr, float sg, float sb, float r, float ir, float ig, float ib);
};

#endif
