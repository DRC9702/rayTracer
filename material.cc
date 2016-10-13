#include "material.h"

material::material(){
	dr=0; dg=0; db=0;
	sr=0; sg=0; sb=0;
	r=0;
	ir=0; ig=0; ib=0;
}

material::material(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib){
	setMaterial(dr, dg, db, sr, sg, sb, r, ir, ig, ib);
}

void material::setMaterial(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib)
{
	//Diffuse components
	this->dr = dr;
	this->dg = dg;
	this->db = db;
	//Specular components
	this->sr = sr;
	this->sg = sg;
	this->sb = sb;
	//roughness phong exponent
	this->r = r;
	//ideal specular components
	this->ir = ir;
	this->ig = ig;
	this->ib = ib;
}
