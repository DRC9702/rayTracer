#ifndef VECTOR_H
#define VECTOR_H

class vector
{
public:
	double x;
	double y;
	double z;
	vector();
	vector(double x, double y, double z);
	void setComponents(double x, double y, double z);
	bool isEqual(vector other);
	double getMagnitude();
	void applyScalar(double s);
	vector scalarMultiply(double s);
	vector add(vector other);
	vector negationVector();
	vector subtract(vector other);
	void normalize();
	vector getNormalizedVector();
	double dotProduct(vector other);
	vector crossProduct(vector other);
	
	
};

#endif
