#include "ray.h"
#include "Vector.h"
#include "point.h"
#include "BBox.h"
//#include "material.h"
#include "Intersection.h"
#include "Constants.h"

#ifndef SURFACE_H
#define SURFACE_H

//Originally each surface was storing it's own material but that's not very optimized.
//So instead it'll store an index pointing to the material list

class surface
{
private:
	//material* mat;
	int materialIndex;
	BBox boundingBox;
public:
	surface();
	virtual ~surface();
	//void setMaterial(material* input_mat_p);
	//material* getMaterial();
	void setMaterialIndex(int n);
	int getMaterialIndex() const;
	//double intersectWithBBox(const ray r_ray, bool useBBox) const;
	virtual void setBoundingBox(BBox bbox);

	virtual bool intersectHit(ray r, double bestT, Intersection &intersect) const;

//	Intersection checkIntersectWithBBox(const ray r_ray, int BBoxFlag) const;
//	virtual Intersection checkIntersect(const ray r_ray) const;
	//virtual double intersectT(const ray r_ray) const;
	virtual Vector getSurfaceNormal(const point p) const;
	bool checkIfRaySameDirectionAsNormal(const ray r_ray, const point p) const;
	const BBox& getBoundingBox() const;
};

#endif
