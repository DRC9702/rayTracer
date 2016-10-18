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
camera::camera(point p, vector u, vector v, vector w, double d, int nx, int ny, double width, double height)
{
	eye = p;
	this->u = u.getNormalizedVector();
	this->v = v.getNormalizedVector();
	this->w = w.getNormalizedVector();
	this->d = d;
	this->nx = nx;
	this->ny = ny;
	r = width/2;
	l = r - width;
	t =  height/2;
	b = t - height;
}
//We're going to make everything centered by default
camera::camera(point p, vector inputDir, double d, int nx, int ny, double width, double height)
{
	eye = p;
	vector dir = inputDir.getNormalizedVector();
	u = dir.crossProduct(vector(0,1,0));
	v = u.crossProduct(dir).getNormalizedVector();
	w = dir.negationVector().getNormalizedVector(); //I know this should already be normalized, but i'm being safe
	this->d = d;
	this->nx = nx;
	this->ny = ny;
	r = width/2;
	l = r - width;
	t =  height/2;
	b = t - height;
}

camera::camera(double x, double y, double z, double vx, double vy, double vz, double d, int nx, int ny, double width, double height)
{
	eye = point(x,y,z);
	vector dir = vector(vx,vy,vz).getNormalizedVector();
	u = dir.crossProduct(vector(0,1,0)).getNormalizedVector();
	v = u.crossProduct(dir).getNormalizedVector();
	w = dir.negationVector().getNormalizedVector();
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
	double su = l + (r-l)*(i+0.5)/nx;
	double sv = b + (t-b)*(j+0.5)/ny;
	vector dir = (((w.scalarMultiply(-d)).add(u.scalarMultiply(su))).add(v.scalarMultiply(sv))).getNormalizedVector();
	//std::cout << "camera generated a ray with magnitude[" << dir.getMagnitude() << "]" << std::endl;
	return ray(eye,dir);
	//Ask the TA.
}
