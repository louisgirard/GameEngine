#pragma once
#include <cmath>
#include <string>

#include <glm/glm.hpp>

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

		static const Vector3 ZERO;
		static const Vector3 FRONT;
		static const Vector3 RIGHT;
		static const Vector3 LEFT;
		static const Vector3 UP;
		static const Vector3 DOWN;

		/* Default constructor */
		Vector3();

		/* Explicit constructor 
		* @param p_x x position of the vector
		* @param p_y y position of the vector
		* @param p_z z position of the vector
		*/
		Vector3(float p_x, float p_y, float p_z);

		/* Flips all the components */
		void invert();

		/* @return the magnitude */
		float magnitude() const;

		/* @return the squared magnitude */
		float squaredMagnitude() const;

		/* Turns a vector into a unit vector*/
		void normalize();

		/* Multiplies a vector by a scalar 
		* @param p_value value of the scalar
		*/
		void operator*= (const float p_value);

		/* @return a vector multiplied by a scalar
		* @param p_value value of the scalar
		*/
		Vector3 operator*(const float p_value) const;

		/* Adds a vector to this vector
		* @param p_vector value of the vector
		*/
		void operator+=(const Vector3& p_vector);

		/* @return a vector added with this vector
		* @param p_vector value of the vector
		*/
		Vector3 operator+(const Vector3& p_vector) const;

		/* Substracts a vector to this vector
		* @param p_vector value of the vector
		*/
		void operator-=(const Vector3& p_vector);

		/* @returns a vector subtracted with this vector
		* @param p_vector value of the vector
		*/
		Vector3 operator-(const Vector3& p_vector) const;

		/* @return a vector multiplied with this vector
		* @param p_vector value of the vector
		*/
		Vector3 componentProduct(const Vector3& p_vector) const;

		/* Multiplies a vector with this vector
		* @param p_vector value of the vector
		*/
		void componentProductUpdate(const Vector3& p_vector);

		/* Returns the scalar product with this vector
		* @param p_vector value of the vector
		*/
		float scalarProduct(const Vector3& p_vector) const;

		/* @return the vector product with this vector
		* @param p_vector value of the vector
		*/
		Vector3 vectorProduct(const Vector3& p_vector) const;

		static Vector3 convertGlm(const glm::vec3& p_vec);
	};
}


