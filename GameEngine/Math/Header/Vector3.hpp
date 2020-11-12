#pragma once
#include <cmath>
#include <string>

#include <glm/glm.hpp>
#include <iostream>



namespace Math {

	class Matrix3x4;

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
		static const Vector3 ONE;
		static const Vector3 FRONT;
		static const Vector3 RIGHT;
		static const Vector3 LEFT;
		static const Vector3 UP;
		static const Vector3 DOWN;

		/* Default constructor */
		Vector3();

		/*
		* Constructor
		* @param p_components : components of the vector (size : 3) 
		*/
		Vector3(float* p_components);

		/* Explicit constructor 
		* @param p_x x position of the vector
		* @param p_y y position of the vector
		* @param p_z z position of the vector
		*/
		Vector3(float p_x, float p_y, float p_z);

		/*
		* Copy constructor
		* @param p_vec : the vector to copy
		*/
		Vector3(const Vector3& p_vec);


		/* Flips all the components */
		void invert();

		/* @return the magnitude */
		float magnitude() const;

		/* @return the squared magnitude */
		float squaredMagnitude() const;

		/* Turns a vector into a unit vector*/
		void normalize();

		/*
		* Accessor
		* Access the value at the specified index
		* @param p_index : the index of the scalar we want to get
		* @return the scalar at the index
		*/
		float& operator[] (int p_index);

		/*
		* Accessor
		* Access the value at the specified index
		* @param p_index : the index of the scalar we want to get
		* @return the scalar at the index
		*/
		const float& operator[] (int p_index) const;

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

		/*
		* Copy operator
		* @param p_value : the value to set to all coordinate of the vector
		* A copy of this vector
		*/
		Vector3& operator= (float const& p_value);

		/*
		* Copy operator
		* @param p_vec : the vector to copy
		* @return a copy of this vector
		*/
		Vector3& operator= (Vector3 const& p_vec);


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

		/*Transform a point from local position to world position
		* @param worldTransform : The world matrix
		* @return position in world
		*/
		Vector3 localToWorld(const Matrix3x4 & worldTransform);

		/*
		* Transform a point from world position to local position
		* @param worldTransform : The world matrix
		* @return position in model
		*/
		Vector3 worldToLocal(const Matrix3x4 & worldTransform);

		/*
		* Transform a direction from local direction to world direction
		* @param worldTransform : The world matrix
		* @return direction in world
		*/
		Vector3 localDirectionToWorld(const Matrix3x4 & worldTransform);

		/*
		* Transform a direction from world direction to local direction
		* @param worldTransform : The world matrix
		* @return direction in model
		*/
		Vector3 worldDirectionToLocal(const Matrix3x4 & worldTransform);

		/*
		* Convert a vector form glm library to a Vector3
		* @return p_vec : the vector to convert
		*/
		static Vector3 convertGlm(const glm::vec3& p_vec);

		/*
		* Convert a Vector3 to a vector from glm library
		* @return p_vec : the vector to convert
		*/
		static glm::vec3 toGlm(const Vector3& p_vec);
	};

	/*
	* Print a vector3 
	* @param p_vec : the vector to print
	*/
	inline std::ostream& operator << (std::ostream& p_out, const Vector3& p_vec)
	{
		std::cout << "(" << p_vec._x << ", "  << p_vec._y << ", " << p_vec._z << ")";
		return p_out;
	}

}


