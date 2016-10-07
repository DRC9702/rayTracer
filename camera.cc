#include "camera.h"
#include "ray.h"
#include "vector.h"
#include "point.h"

//Constructor // Don't know how valid this is yet.


camera::camera()
{
 	eye = point();
	
	d = 10; // focal length
	
	u = vector(0,1,0);
	v = vector(1,0,0);
	w = vector(0,0,-1);
	
	nx = 20;
	ny = 20;
	
	l = -10; r = 10; t = 10; b = -10;
}

//We're going to make everything centered by default
camera::camera(point p, vector u, vector v, vector w, float d, int nx, int ny, float width, float height)
{
	eye = p;
	this->u = u;
	this->v = v;
	this->w = w;
	this->d = d;
	this->nx = nx;
	this->ny = ny;
	r = width/2;
	l = r - width;
	t =  height/2;
	b = t - height;
}
//We're going to make everything centered by default
camera::camera(point p, vector inputDir, float d, int nx, int ny, float width, float height)
{
	eye = p;
	vector dir = inputDir.normalize();
	u = dir.crossProduct(vector(0,1,0));
	v = u.crossProduct(dir);
	w = dir.negationVector();
	this->d = d;
	this->nx = nx;
	this->ny = ny;
	r = width/2;
	l = r - width;
	t =  height/2;
	b = t - height;
}

camera::camera(float x, float y, float z, float vx, float vy, float vz, float d, int nx, int ny, float width, float height)
{
	eye = point(x,y,z);
	vector dir = vector(vx,vy,vz).normalize();
	u = dir.crossProduct(vector(0,1,0));
	v = u.crossProduct(dir);
	w = dir.negationVector();
	this->d = d;
	this->nx = nx;
	this->ny = ny;
	r = width/2;
	l = r - width;
	t =  height/2;
	b = t - height;
	
}

ray camera::generateRayForPixel(int i, int j)
{
	int su = l + (r-l)*(i+0.5)/nx;
	int sv = b + (t-b)*(j+0.5)/ny;
	vector dir = ((w.scalarMultiply(-d)).add(u.scalarMultiply(su))).add(v.scalarMultiply(sv));
	return ray(eye,dir);
	//Ask the TA.
}
