#ifndef VECTOR_H
#define VECTOR_H

class vector
{
private:
	double x;
	double y;
	double z;
public:
	vector();
	vector(double x, double y, double z);
	void setComponents(double x, double y, double z);
	bool isEqual(const vector other) const;
	double getMagnitude() const;
	void applyScalar(const double s);
	vector scalarMultiply(const double s) const;
	vector add(const vector other) const;
	vector negationVector() const;
	vector subtract(const vector other) const;
	void normalize();
	vector getNormalizedVector() const;
	double dotProduct(const vector other) const;
	vector crossProduct(const vector other) const;

	double getX() const {
		return x;
	}

	double getY() const {
		return y;
	}

	double getZ() const {
		return z;
	}
};

#endif
