#include "ray.h"
#include "vector.h"
#include "point.h"

#ifndef CAMERA_H
#define CAMERA_H


class camera
{
private:
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
public:
	camera(); // I don't know if this is valid yet.
	camera(point p, vector u, vector v, vector w, double d, int nx, int ny, double width, double height);
	camera(point p, vector dir, double d, int nx, int ny, double width, double height);
	camera(double x, double y, double z, double vx, double vy, double vz, double d, int nx, int ny, double width, double height);
	ray generateRayForPixel(int i, int j);

	double getB() const {
		return b;
	}

	void setB(double b) {
		this->b = b;
	}

	double getD() const {
		return d;
	}

	const point& getEye() const {
		return eye;
	}

	double getL() const {
		return l;
	}

	int getNx() const {
		return nx;
	}

	int getNy() const {
		return ny;
	}

	double getR() const {
		return r;
	}

	double getT() const {
		return t;
	}

	const vector& getU() const {
		return u;
	}

	const vector& getV() const {
		return v;
	}

	const vector& getW() const {
		return w;
	}
};

#endif
