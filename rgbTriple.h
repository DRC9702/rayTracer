/*
 * rgbTriple.h
 *
 *  Created on: Oct 18, 2016
 *      Author: david
 */

#ifndef RGBTRIPLE_H_
#define RGBTRIPLE_H_

class rgbTriple {
public:
	double r;
	double g;
	double b;
	double getR();
	void setR(double r);
	double getG();
	void setG(double g);
	double getB();
	void setB(double b);
	void setRGB(double r, double g, double b);
	void addRGBFrom(rgbTriple other);
	rgbTriple();
	rgbTriple(double r, double g, double b);
	virtual ~rgbTriple();
};

#endif /* RGBTRIPLE_H_ */
