#include "ray.h"
#include "vector.h"
#include "point.h"

#ifndef CAMERA_H
#define CAMERA_H


class camera
{
public:
	point eye;
	
	float d; // focal length
	
	//Basis
	vector u;
	vector v;
	vector w;
	
	int nx; //Number of pixels in the x dimension
	int ny; //Number of pixels in the y dimension
	
	//Let's try make the camera centered for now
	float l, r, t, b;
	
	camera(); // I don't know if this is valid yet.
	camera(point p, vector u, vector v, vector w, float d, int nx, int ny, float width, float height);
	camera(point p, vector dir, float d, int nx, int ny, float width, float height);
	camera(float x, float y, float z, float vx, float vy, float vz, float d, int nx, int ny, float width, float height);
	ray generateRayForPixel(int i, int j);
	
};

#endif
