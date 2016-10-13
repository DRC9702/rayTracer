#ifndef MATERIAL_H
#define MATERIAL_H


class material
{
public:
	//Diffuse components
	double dr;
	double dg;
	double db;
	//Specular components
	double sr;
	double sg;
	double sb;
	//roughness phong exponent
	double r;
	//ideal specular components
	double ir;
	double ig;
	double ib;
	material();
	material(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib);
	void setMaterial(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib);
};

#endif
