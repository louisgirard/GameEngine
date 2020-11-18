#pragma once

#include <Math/Header/Quaternion.hpp>

namespace Math {
	/* Holds a 3x4 dimensional matrix */
	class Matrix3x4
	{
	public:
		/* Holds the values inside the matrix*/
		float _values[12];

		/* Constructors */
		Matrix3x4();

		/*
		* Constructor
		* @param p_cols : column of the matrix (size : 4)
		*/
		Matrix3x4(Vector3* const p_cols);

		/*
		* Constructor
		* @parma p_vij : new element at position i, j in matrix
		*/
		Matrix3x4(float p_v1, float p_v2, float p_v3, float p_v4, float p_v5, float p_v6, float p_v7, float p_v8, float p_v9, float p_v10, float p_v11, float p_v12);
		
		/*
		* Copy constructor
		* @param p_mat : the matrix to copy
		*/
		Matrix3x4(const Matrix3x4& p_matrix);

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

		/* @return a matrix multiplied by the matrix
		* @param p_matrix matrix to multiply
		*/
		Matrix3x4 operator*(const Matrix3x4& p_matrix) const;

		/*
		* Multiply operator
		* @param p_matrix matrix to multiply
		* @return a copy of this matrix
		*/
		Matrix3x4& operator*= (const Matrix3x4& p_matrix);

		/* Invert the matrix 
		* @return true if the matrix has been inverted, false if it is non invertible
		*/
		bool invert();

		/*
		* Gets matrix inversion
		* @return matrix inversion
		*/
		Matrix3x4& getInversion() const;

		/*
		* Transpose the matrix
		*/
		void transpose();

		/*
		* Gets matrix transpose
		* @return matrix transpose
		*/
		Matrix3x4& getTranspose() const;

		/*
		* Sets rotation matrix
		* @param p_rotationMatrix : rotation matrix
		*/
		void setRotationMatrix(const Matrix3x3& p_rotationMatrix);

		/*
		* Set a Rotation, Translation matrix
		* @param p_quaternion : The rotation element
		* @param p_pos : the translation element
		*/
		void setTR(const Quaternion& p_quaternion, const Vector3& p_pos);

		/*
		* Obtain the transform of a point by this matrix
		* @param p_point The point to multiply
		* @return the new position of the point
		*/
		Vector3 transformPoint(const Vector3& p_point) const;

		/*
		* Obtain the transform of a direction by this matrix
		* @param p_direction The orientation to multiply
		* @return the new orientation of the point
		*/
		Vector3 transformDirection(const Vector3& p_direction) const;

		/*
		* Gets matrix identity
		* @return matrix identity
		*/
		static Matrix3x4& identity();

		/*
		* Convert a matrix form glm library to a Matrix3x4
		* @return p_mat : the vector to convert
		*/
		static Matrix3x4 convertGlm(const glm::mat4& p_mat);

		/*
		* Convert a Matrix3x4 to a matrix from glm library
		* @return p_mat : the matrix to convert
		*/
		static glm::mat4 toGlm(const Matrix3x4& p_mat);
	};
	
	/*
	* Print a matrix3x4
	* @param p_mat : the matrix to print
	*/
	inline std::ostream& operator << (std::ostream& p_out, const Matrix3x4& p_mat)
	{
		std::cout << std::endl << "[" << p_mat[0] << " " << p_mat[1]<< " " << p_mat[2] << " " << p_mat[3] << std::endl;
		std::cout << p_mat[4] << " " << p_mat[5] << " " << p_mat[6] << " " << p_mat[7] << std::endl;
		std::cout << p_mat[8] << " " << p_mat[9] << " " << p_mat[10] << " " << p_mat[11] << std::endl;
		std::cout << 0 << " " << 0 << " " << 0 << " " << 1 << "]" << std::endl;

		return p_out;
	}
}