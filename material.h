#include "point.h"
#include "rgbTriple.h"
#include "surface.h"
#include "pointLight.h"
#include "camera.h"
#include <vector>

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
	rgbTriple shading(point p, camera cam, unsigned int surfaceIndex, std::vector<surface*> &surfaceList, std::vector<pointLight*> &pointLightList);
	void lambertianShadingForPointLight(point p, unsigned int surfaceIndex, std::vector<surface*> &surfaceList, pointLight* pL, rgbTriple &lambertianRGB);
	void specularShadingForPointLight(point p, camera cam, unsigned int surfaceIndex, std::vector<surface*> &surfaceList, pointLight* pL, rgbTriple &specularRGB);
};

#endif
