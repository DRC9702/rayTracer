#include "ray.h"
#include "vector.h"
#include "point.h"

#ifndef CAMERA_H
#define CAMERA_H


class camera
{
public:
	point eye;
	
	double d; // focal length
	
	//Basis
	vector u;
	vector v;
	vector w;
	
	int nx; //Number of pixels in the x dimension
	int ny; //Number of pixels in the y dimension
	
	//Let's try make the camera centered for now
	double l, r, t, b;
	
	camera(); // I don't know if this is valid yet.
	camera(point p, vector u, vector v, vector w, double d, int nx, int ny, double width, double height);
	camera(point p, vector dir, double d, int nx, int ny, double width, double height);
	camera(double x, double y, double z, double vx, double vy, double vz, double d, int nx, int ny, double width, double height);
	ray generateRayForPixel(int i, int j);
	
};

#endif
