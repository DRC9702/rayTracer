#include "camera.h"
#include <iostream>
#include <cstdlib>

//Constructor // Don't know how valid this is yet.

camera::camera()
{
 	eye = point();
	
	d = 10; // focal length
	
	u = Vector(0,1,0);
	v = Vector(1,0,0);
	w = Vector(0,0,-1);
	
	nx = 20;
	ny = 20;
	
	l = -10; r = 10; t = 10; b = -10;
}

//We're going to make everything centered by default
camera::camera(point p, Vector u, Vector v, Vector w, double d, int nx, int ny, double width, double height)
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
camera::camera(point p, Vector inputDir, double d, int nx, int ny, double width, double height)
{
	eye = p;
	Vector dir = inputDir.getNormalizedVector();
	u = dir.crossProduct(Vector(0,1,0));
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
	Vector dir = Vector(vx,vy,vz).getNormalizedVector();
	u = dir.crossProduct(Vector(0,1,0)).getNormalizedVector();
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
	Vector dir = (((w.scalarMultiply(-d)).add(u.scalarMultiply(su))).add(v.scalarMultiply(sv))).getNormalizedVector();
	//std::cout << "camera generated a ray with magnitude[" << dir.getMagnitude() << "]" << std::endl;
	return ray(eye,dir);
	//Ask the TA.
}

ray camera::generateRayForPixel(int i, int j, int p, int q, int n){
	double su = l + (r-l)*(i+ (p+(rand()+0.0)/((double) RAND_MAX))/n)/nx;
	double sv = b + (t-b)*(j+ (q+(rand()+0.0)/((double) RAND_MAX))/n)/ny;
//	std::cout << "Su:" << su << ", sv:" << sv << std::endl;
	Vector dir = (((w.scalarMultiply(-d)).add(u.scalarMultiply(su))).add(v.scalarMultiply(sv))).getNormalizedVector();
	//std::cout << "camera generated a ray with magnitude[" << dir.getMagnitude() << "]" << std::endl;
	return ray(eye,dir);
	//TA is busy, can't ask him right now, lol
}
