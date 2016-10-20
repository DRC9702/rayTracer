#include "material.h"
#include <cmath>

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

rgbTriple material::shading(point p, camera cam, unsigned int surfaceIndex, std::vector<surface*> &surfaceList, std::vector<pointLight*> &pointLightList){
	rgbTriple shadeLight;

	rgbTriple lambertianShading;
	rgbTriple specularShading;
	for(unsigned int k=0; k < pointLightList.size(); k++){

		bool lightHit = false;
		ray ray_pToL = ray(p,pointLightList.at(k)->position);
		for(unsigned int k=0; k < surfaceList.size(); k++){
			if(k==surfaceIndex){
				continue; //Skip your own surface
			}
			double tempT = surfaceList.at(k) -> intersectT(ray_pToL);
			if(tempT > 0){
				lightHit = true;
			}
		}
		if(lightHit){
			continue;
		}

		//lambertian shading
		lambertianShadingForPointLight(p, surfaceIndex, surfaceList, pointLightList.at(k), lambertianShading);
		//specular shading
		specularShadingForPointLight(p, cam, surfaceIndex, surfaceList, pointLightList.at(k), specularShading);
		//Adding all shading from pointlight
		shadeLight.addRGBFrom(lambertianShading);
		shadeLight.addRGBFrom(specularShading);
	}
	return shadeLight;
}

void material::lambertianShadingForPointLight(point p, unsigned int surfaceIndex, std::vector<surface*> &surfaceList, pointLight* pL, rgbTriple &lambertianRGB){
	surface *pointSurface = surfaceList.at(surfaceIndex);
	vector l = pL->position.subtract(p); l.normalize();
	double distance = pL->position.subtract(p).getMagnitude();
	vector surfaceNormal = pointSurface->getSurfaceNormal(p);
	//std::cout << "l.x:" << l.x << std::endl;
	//std::cout << "sn.x:" << surfaceNormal.x << std::endl;

	//These are my diffuse coefficients
	double dr = diffuse.getR();
	double dg = diffuse.getG();
	double db = diffuse.getB();
	//double intensityCoefficient = 1 / (l.getMagnitude()*l.getMagnitude());
	double intensityCoefficient = pL->intensity/(distance*distance); //WHAT IS I?!?!?!

	double dotMultiplier = l.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;

	//Diffusely reflect light in each of the three channels
	lambertianRGB.setR(dr * dotMultiplier * pL->lightValue.getR() * intensityCoefficient);
	lambertianRGB.setG(dg * dotMultiplier * pL->lightValue.getG() * intensityCoefficient);
	lambertianRGB.setB(db * dotMultiplier * pL->lightValue.getB() * intensityCoefficient);
}

void material::specularShadingForPointLight(point p, camera cam, unsigned int surfaceIndex, std::vector<surface*> &surfaceList, pointLight* pL, rgbTriple &specularRGB){
	surface* pointSurface = surfaceList.at(surfaceIndex);
	vector v = (cam.eye).subtract(p).getNormalizedVector();
	vector surfaceNormal = pointSurface->getSurfaceNormal(p);
	//std::cout << "surface normal before stuff[" << surfaceNormal.getMagnitude() << "]" << std::endl;
	vector l = pL->position.subtract(p); l.normalize();
	double distance = pL->position.subtract(p).getMagnitude();
	vector h = v.add(l); h.normalize(); //Since both v and l are unit vectors, this should bisect them

	//These are my specular coefficients
	double sr = specular.getR();
	double sg = specular.getG();
	double sb = specular.getB();
	double phong = r; //my phong exponent
	double intensityCoefficient = pL->intensity/(distance*distance); //WHAT IS I?!?!?!

	double dotMultiplier = h.dotProduct(surfaceNormal);
	dotMultiplier = (dotMultiplier < 0) ? 0 : dotMultiplier;

//	std::cout << "dotMultiplier[" << dotMultiplier << "]" << std::endl;
//	std::cout << "h[" << h.getMagnitude() << "]" << std::endl;
//	std::cout << "n[" << surfaceNormal.getMagnitude() << "]" << std::endl;

	specularRGB.setR(sr * pow(dotMultiplier,phong) * pL->lightValue.getR() * intensityCoefficient);
	specularRGB.setG(sg * pow(dotMultiplier,phong) * pL->lightValue.getG() * intensityCoefficient);
	specularRGB.setB(sb * pow(dotMultiplier,phong) * pL->lightValue.getB() * intensityCoefficient);

}
