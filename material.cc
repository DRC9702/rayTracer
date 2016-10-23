#include "material.h"
#include <cmath>
#include <iostream>

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

rgbTriple material::shading(const point p, const camera cam, const unsigned int surfaceIndex, const std::vector<surface*> &surfaceList, const std::vector<pointLight*> &pointLightList) const{
	rgbTriple shadeLight;

	rgbTriple lambertianShading;
	rgbTriple specularShading;
	for(unsigned int k=0; k < pointLightList.size(); k++){

		ray ray_pToL = ray(p,pointLightList.at(k)->getPosition());
		double distanceFromPointToLight = pointLightList.at(k)->getPosition().subtract(p).getMagnitude();
		bool lightHit = false;
		for(unsigned int j=0; j < surfaceList.size() && !lightHit; j++){

			if(j==surfaceIndex){
				continue; //Skip your own surface
			}
			double tempT = surfaceList.at(j) -> intersectT(ray_pToL);
//			std::cout << "tempT[" << tempT << " distanceToLight[" << distanceFromPointToLight << "]" << std::endl;
			if(tempT > 0){
				//std::cout << "Hello!" << std::endl;
				if(tempT < distanceFromPointToLight){
					//continue;
					lightHit = true;
//					std::cout << "DistanceFromPointToLight[" << distanceFromPointToLight << "\t tempT[" << tempT  << "]" << std::endl;
				}
//				lightHit = true;
			}
		}
		if(!lightHit) {


		//lambertian shading
		lambertianShadingForPointLight(p, surfaceIndex, surfaceList, pointLightList.at(k), lambertianShading);
		//specular shading
		specularShadingForPointLight(p, cam, surfaceIndex, surfaceList, pointLightList.at(k), specularShading);
		//Adding all shading from pointlight
		shadeLight.addRGBFrom(lambertianShading);
		shadeLight.addRGBFrom(specularShading);
		}
	}
	return shadeLight;
}

void material::lambertianShadingForPointLight(const point p, const unsigned int surfaceIndex, const std::vector<surface*> &surfaceList, const pointLight* pL, rgbTriple &lambertianRGB) const{
	surface *pointSurface = surfaceList.at(surfaceIndex);
	vector l = pL->getPosition().subtract(p); l.normalize();
	double distance = pL->getPosition().subtract(p).getMagnitude();
	vector surfaceNormal = pointSurface->getSurfaceNormal(p);
	//std::cout << "l.x:" << l.x << std::endl;
	//std::cout << "sn.x:" << surfaceNormal.x << std::endl;

	//These are my diffuse coefficients
	double dr = diffuse.getR();
	double dg = diffuse.getG();
	double db = diffuse.getB();
	//double intensityCoefficient = 1 / (l.getMagnitude()*l.getMagnitude());
	double intensityCoefficient = pL->getIntensity()/(distance*distance); //WHAT IS I?!?!?!

	double dotMultiplier = l.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;

	//Diffusely reflect light in each of the three channels
	lambertianRGB.setR(dr * dotMultiplier * pL->getLightValue().getR() * intensityCoefficient);
	lambertianRGB.setG(dg * dotMultiplier * pL->getLightValue().getG() * intensityCoefficient);
	lambertianRGB.setB(db * dotMultiplier * pL->getLightValue().getB() * intensityCoefficient);
}

void material::specularShadingForPointLight(const point p, const camera cam, const unsigned int surfaceIndex, const std::vector<surface*> &surfaceList, const pointLight* pL, rgbTriple &specularRGB) const{
	surface* pointSurface = surfaceList.at(surfaceIndex);
	vector v = (cam.getEye()).subtract(p).getNormalizedVector();
	vector surfaceNormal = pointSurface->getSurfaceNormal(p);
	//std::cout << "surface normal before stuff[" << surfaceNormal.getMagnitude() << "]" << std::endl;
	vector l = pL->getPosition().subtract(p); l.normalize();
	double distance = pL->getPosition().subtract(p).getMagnitude();
	vector h = v.add(l); h.normalize(); //Since both v and l are unit vectors, this should bisect them

	//These are my specular coefficients
	double sr = specular.getR();
	double sg = specular.getG();
	double sb = specular.getB();
	double phong = r; //my phong exponent
	double intensityCoefficient = pL->getIntensity()/(distance*distance); //WHAT IS I?!?!?!

	double dotMultiplier = h.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;

//	std::cout << "dotMultiplier[" << dotMultiplier << "]" << std::endl;
//	std::cout << "h[" << h.getMagnitude() << "]" << std::endl;
//	std::cout << "n[" << surfaceNormal.getMagnitude() << "]" << std::endl;

	specularRGB.setR(sr * pow(dotMultiplier,phong) * pL->getLightValue().getR() * intensityCoefficient);
	specularRGB.setG(sg * pow(dotMultiplier,phong) * pL->getLightValue().getG() * intensityCoefficient);
	specularRGB.setB(sb * pow(dotMultiplier,phong) * pL->getLightValue().getB() * intensityCoefficient);

}
