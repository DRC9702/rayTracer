/*
 * rgbTriple.h
 *
 *  Created on: Oct 18, 2016
 *      Author: david
 */

#ifndef RGBTRIPLE_H_
#define RGBTRIPLE_H_

class rgbTriple {
private:
	double r;
	double g;
	double b;
public:
	double getR() const;
	void setR(const double r);
	double getG() const;
	void setG(const double g);
	double getB() const;
	void setB(const double b);
	void setRGB(const double r, const double g, const double b);
	void addRGBFrom(const rgbTriple other);
	rgbTriple();
	rgbTriple(double r, double g, double b);
	virtual ~rgbTriple();
};

#endif /* RGBTRIPLE_H_ */
