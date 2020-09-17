#pragma once
#include <cmath>
#include <string>

namespace PhysicEngine {
	/* Holds a vector in three dimensions */
	class Vector3
	{
	public:
		/* Holds the value along the x axis */
		float _x;

		/* Holds the value along the y axis */
		float _y;

		/* Holds the value along the z axis */
		float _z;

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
		void operator*= (const float p_value);

		/* Returns a vector multiplied by a scalar */
		Vector3 operator*(const float p_value) const;

		/* Adds a vector to this vector */
		void operator+=(const Vector3& p_vector);

		/* Returns a vector added with this vector */
		Vector3 operator+(const Vector3& p_vector) const;

		/* Substracts a vector to this vector */
		void operator-=(const Vector3& p_vector);

		/* Returns a vector subtracted with this vector */
		Vector3 operator-(const Vector3& p_vector) const;

		/* Returns a vector multiplied with this vector */
		Vector3 componentProduct(const Vector3& p_vector) const;

		/* Multiplies a vector with this vector */
		void componentProductUpdate(const Vector3& p_vector);

		/* Returns the scalar product with this vector */
		float scalarProduct(const Vector3& p_vector) const;

		/* Returns the vector product with this vector */
		Vector3 vectorProduct(const Vector3& p_vector) const;
	};
}


