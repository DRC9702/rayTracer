#ifndef VECTOR_H
#define VECTOR_H

class vector
{
public:
	float x;
	float y;
	float z;
	vector();
	vector(float x, float y, float z);
	void setComponents(float x, float y, float z);
	bool isEqual(vector other);
	float getMagnitude();
	void applyScalar(float s);
	vector scalarMultiply(float s);
	vector add(vector other);
	vector negationVector();
	vector subtract(vector other);
	vector normalize();
	void applyNormalization();
	float dotProduct(vector other);
	vector crossProduct(vector other);
	
	
};

#endif
