#pragma once

#include <Math/Header/Vector3.hpp>

namespace Math {
	/* Holds a three dimensional matrix */
	class Matrix3x3
	{
	private:
		/* Holds the values inside the matrix*/
		float _values[9];

	public:
		/*
		* Default constructor
		*/
		Matrix3x3();

		/*
		* Constructor
		* @param p_cols : column of the matrix (size : 3)
		*/
		Matrix3x3(Vector3* const p_cols);

		/*
		* Constructor
		* @parma p_vij : new element at position i, j in matrix
		*/
		Matrix3x3(float p_v1, float p_v2, float p_v3, float p_v4, float p_v5, float p_v6, float p_v7, float p_v8, float p_v9);
		
		/*
		* Copy constructor
		* @param p_mat : the matrix to copy
		*/
		Matrix3x3(const Matrix3x3& p_matrix);


		/*
		* Access the value at specified index
		* @param index of the value we want to get
		* @return the value at the index
		*/
		float& operator[] (int p_index);

		/*
		* Access the value at specified index
		* @param index of the value we want to get
		* @return the value at the index
		*/
		const float& operator[] (int p_index) const;

		/* @return a vector multiplied by the matrix
		* @param p_vector vector to multiply
		*/
		Vector3 operator*(const Vector3& p_vector) const;

		/* @return a matrix multiplied by the matrix
		* @param p_matrix matrix to multiply
		*/
		Matrix3x3 operator*(const Matrix3x3& p_matrix) const;

		/*
		* Multiply operator
		* @param p_matrix matrix to multiply
		* @return a copy of this matrix
		*/
		Matrix3x3& operator*= (const Matrix3x3& p_matrix);

		/* Invert the matrix */
		void invert();

		/*
		* Gets matrix inversion
		* @return matrix inversion
		*/
		Matrix3x3& getInversion() const;

		/* Transpose the matrix */
		void transpose();

		/*
		* Gets matrix transpose
		* @return matrix transpose
		*/
		Matrix3x3& getTranspose() const;

		/*
		* Gets matrix identity
		* @return matrix identity
		*/
		static Matrix3x3& identity();

		/*
		* Convert a matrix form glm library to a Matrix3x3
		* @return p_mat : the vector to convert
		*/
		static Matrix3x3 convertGlm(const glm::mat3& p_mat);

		/*
		* Convert a Matrix3x4 to a matrix from glm library
		* @return p_mat : the matrix to convert
		*/
		static glm::mat3 toGlm(const Matrix3x3& p_mat);
	};

	/*
	* Print a matrix3x3
	* @param p_mat : the matrix to print
	*/
	inline std::ostream& operator << (std::ostream& p_out, const Matrix3x3& p_mat)
	{
		std::cout << "[" << p_mat[0] << " " << p_mat[1] << " " << p_mat[2] << std::endl;
		std::cout << p_mat[3] << " " << p_mat[4] << " " << p_mat[5] << std::endl;
		std::cout << p_mat[6] << " " << p_mat[7] << " " << p_mat[8] << "]" << std::endl;

		return p_out;
	}
}
