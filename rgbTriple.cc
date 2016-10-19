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

double rgbTriple::getR(){
	return r;
}
void rgbTriple::setR(double r){
	this->r = r;
}
double rgbTriple::getG(){
	return g;
}
void rgbTriple::setG(double g){
	this->g = g;
}
double rgbTriple::getB(){
	return b;
}
void rgbTriple::setB(double b){
	this->b = b;
}

void rgbTriple::setRGB(double r, double g, double b){
	setR(r); setG(g); setB(b);
}

void rgbTriple::addRGBFrom(rgbTriple other){
	setR(getR()+other.getR());
	setG(getG()+other.getG());
	setB(getB()+other.getB());
}

rgbTriple::~rgbTriple() {
	// TODO Auto-generated destructor stub
}
