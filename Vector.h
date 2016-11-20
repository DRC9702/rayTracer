#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
private:
	double x;
	double y;
	double z;
public:
	Vector();
	Vector(double x, double y, double z);
	void setComponents(double x, double y, double z);
	bool isEqual(const Vector other) const;
	double getMagnitude() const;
	void applyScalar(const double s);
	Vector scalarMultiply(const double s) const;
	Vector add(const Vector other) const;
	Vector negationVector() const;
	Vector subtract(const Vector other) const;
	void addInto(const Vector other);
	void normalize();
	Vector getNormalizedVector() const;
	double dotProduct(const Vector other) const;
	Vector crossProduct(const Vector other) const;

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
