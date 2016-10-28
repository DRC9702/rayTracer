#include "point.h"
#include "rgbTriple.h"
#include "surface.h"
#include "pointLight.h"
#include "ambientLight.h"
#include "camera.h"
#include <vector>

#ifndef MATERIAL_H
#define MATERIAL_H


class material
{
private:
	//Diffuse components
	rgbTriple diffuse;
	//Specular components
	rgbTriple specular;
	//roughness phong exponent
	double r;
	//ideal specular components
	rgbTriple idealSpec;
public:
	material();
	material(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib);
	void setMaterial(double dr, double dg, double db, double sr, double sg, double sb, double r, double ir, double ig, double ib);
	rgbTriple shading(const point p, const camera cam, const unsigned int surfaceIndex, const std::vector<surface*> &surfaceList, const std::vector<pointLight*> &pointLightList, const ambientLight &ambLight, const Vector surfaceNormal, const Vector pToSource, const bool isFlipped) const;
	void lambertianShadingForPointLight(const point p, const pointLight* pL, rgbTriple &lambertianRGB, const Vector surfaceNormal) const;
	void specularShadingForPointLight(const point p, const pointLight* pL, rgbTriple &specularRGB, const Vector &surfaceNormal, const Vector &pToSource) const;
	void shadingFromAmbientLight(const ambientLight &ambLight, rgbTriple &ambient) const;

	const rgbTriple& getDiffuse() const {
		return diffuse;
	}

	const rgbTriple& getIdealSpec() const {
		return idealSpec;
	}

	double getR() const {
		return r;
	}

	const rgbTriple& getSpecular() const {
		return specular;
	}
};

#endif
