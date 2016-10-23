#include "ray.h"
#include "vector.h"
#include "point.h"
//#include "material.h"

#ifndef SURFACE_H
#define SURFACE_H

//Originally each surface was storing it's own material but that's not very optimized.
//So instead it'll store an index pointing to the material list

class surface
{
private:
	//material* mat;
	int materialIndex;
public:
	surface();
	virtual ~surface();
	//void setMaterial(material* input_mat_p);
	//material* getMaterial();
	void setMaterialIndex(int n);
	int getMaterialIndex() const;
	virtual double intersectT(const ray r_ray) const;
	virtual vector getSurfaceNormal(const point p) const;
};

#endif
