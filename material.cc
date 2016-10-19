#include "material.h"

material::material(){
	diffuse = rgbTriple();
	specular = rgbTriple();
	r=0;
	idealSpec = rgbTriple();
}

material::material(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib){
	setMaterial(dr, dg, db, sr, sg, sb, r, ir, ig, ib);
}

void material::setMaterial(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib)
{
	//Diffuse components
	diffuse.setRGB(dr,dg,db);
	//Specular components
	specular.setRGB(sr,sg,sb);
	//roughness phong exponent
	this->r = r;
	//ideal specular components
	idealSpec.setRGB(ir,ig,ib);
}
