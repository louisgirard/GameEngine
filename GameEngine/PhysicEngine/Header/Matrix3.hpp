#pragma once

#include <PhysicEngine/Header/Vector3.hpp>

namespace PhysicEngine {
	/* Holds a three dimensional matrix */
	class Matrix3
	{
	private:
		/* Holds the values inside the matrix*/
		float _values[9];

	public:
		/* Constructors */
		Matrix3();
		Matrix3(float p_v1, float p_v2, float p_v3, float p_v4, float p_v5, float p_v6, float p_v7, float p_v8, float p_v9);
		Matrix3(const Matrix3& p_matrix);

		/* @return a vector multiplied by the matrix
		* @param p_vector vector to multiply
		*/
		Vector3 operator*(const Vector3& p_vector) const;

		/* @return a matrix multiplied by the matrix
		* @param p_matrix matrix to multiply
		*/
		Matrix3 operator*(const Matrix3& p_matrix) const;

		/* Invert the matrix */
		void invert();

		/* Transpose the matrix */
		void transpose();
	};
}
