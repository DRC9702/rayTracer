#include "camera.h"
#include "ray.h"
#include "vector.h"
#include "point.h"
#include <iostream>

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
	this->u = u.normalize();
	this->v = v.normalize();
	this->w = w.normalize();
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
	v = u.crossProduct(dir).normalize();
	w = dir.negationVector().normalize(); //I know this should already be normalized, but i'm being safe
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
	u = dir.crossProduct(vector(0,1,0)).normalize();
	v = u.crossProduct(dir).normalize();
	w = dir.negationVector().normalize();
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
	float su = l + (r-l)*(i+0.5)/nx;
	float sv = b + (t-b)*(j+0.5)/ny;
	vector dir = (((w.scalarMultiply(-d)).add(u.scalarMultiply(su))).add(v.scalarMultiply(sv))).normalize();
	//std::cout << "camera generated a ray with magnitude[" << dir.getMagnitude() << "]" << std::endl;
	return ray(eye,dir);
	//Ask the TA.
}
