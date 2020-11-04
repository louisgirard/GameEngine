#pragma once

#include <PhysicEngine/Header/Vector3.hpp>

namespace PhysicEngine {
	/* Holds a 3x4 dimensional matrix */
	class Matrix4
	{
	private:
		/* Holds the values inside the matrix*/
		float _values[12];

	public:
		/* Constructors */
		Matrix4();
		Matrix4(float p_v1, float p_v2, float p_v3, float p_v4, float p_v5, float p_v6, float p_v7, float p_v8, float p_v9, float p_v10, float p_v11, float p_v12);
		Matrix4(const Matrix4& p_matrix);

		/* @return a vector multiplied by the matrix
		* @param p_vector vector to multiply
		*/
		Vector3 operator*(const Vector3& p_vector) const;

		/* @return a matrix multiplied by the matrix
		* @param p_matrix matrix to multiply
		*/
		Matrix4 operator*(const Matrix4& p_matrix) const;

		/* Invert the matrix */
		void invert();
	};
}