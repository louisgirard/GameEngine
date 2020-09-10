#pragma once
#include <cmath>
#include <string>

/* Holds a vector in three dimensions */
class Vector3
{
public:
	/* Holds the value along the x axis */
	float x;

	/* Holds the value along the y axis */
	float y;

	/* Holds the value along the z axis */
	float z;

	/* Default constructor */
	Vector3();

	/* Explicit constructor */
	Vector3(float x, float y, float z);

	/* Flips all the components */
	void invert();

	/* Returns the magnitude */
	float magnitude() const;

	/* Returns the squared magnitude */
	float squaredMagnitude() const;

	/* Turns a vector into a unit vector*/
	void normalize();

	/* Multiplies a vector by a scalar */
	void operator*= (const float value);

	/* Returns a vector multiplied by a scalar */
	Vector3 operator*(const float value) const;

	/* Adds a vector to this vector */
	void operator+=(const Vector3& vector);

	/* Returns a vector added with this vector */
	Vector3 operator+(const Vector3& vector) const;

	/* Substracts a vector to this vector */
	void operator-=(const Vector3& vector);

	/* Returns a vector subtracted with this vector */
	Vector3 operator-(const Vector3& vector) const;

	/* Returns a vector multiplied with this vector */
	Vector3 componentProduct(const Vector3& vector) const;

	/* Multiplies a vector with this vector */
	void componentProductUpdate(const Vector3& vector);

	/* Returns the scalar product with this vector */
	float scalarProduct(const Vector3& vector) const;

	/* Returns the vector product with this vector */
	Vector3 vectorProduct(const Vector3& vector) const;
};
