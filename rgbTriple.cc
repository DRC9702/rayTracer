/*
 * rgbTriple.cc
 *
 *  Created on: Oct 18, 2016
 *      Author: david
 */
#include "rgbTriple.h"

rgbTriple::rgbTriple() {
	setRGB(0,0,0);
}

rgbTriple::rgbTriple(double r, double g, double b){
	setRGB(r,g,b);
}

double rgbTriple::getR() const{
	return r;
}
void rgbTriple::setR(const double r){
	this->r = r;
}
double rgbTriple::getG() const{
	return g;
}
void rgbTriple::setG(const double g){
	this->g = g;
}
double rgbTriple::getB() const{
	return b;
}
void rgbTriple::setB(const double b){
	this->b = b;
}

void rgbTriple::setRGB(const double r, const double g, const double b){
	setR(r); setG(g); setB(b);
}

void rgbTriple::addRGBFrom(const rgbTriple other){
	setR(getR()+other.getR());
	setG(getG()+other.getG());
	setB(getB()+other.getB());
}

rgbTriple::~rgbTriple() {
	// TODO Auto-generated destructor stub
}

bool rgbTriple::isBlank() const{
	if(r!=0 || g!=0 || b!=0)
		return false;
	else
		return true;
}

rgbTriple rgbTriple::componentMultiplication(const rgbTriple other) const{
	return rgbTriple(r*other.r, g*other.g, b*other.b);
}

void rgbTriple::scale(const double s){
	r*=s;
	g*=s;
	b*=s;
}
