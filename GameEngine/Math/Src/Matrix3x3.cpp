#include <Math/Header/Matrix3x3.hpp>

namespace Math
{
	Matrix3x3::Matrix3x3()
	{
		for (int i = 0; i < 9; i++)
		{
			_values[i] = 0;
		}
	}

	Matrix3x3::Matrix3x3(Vector3* const p_cols){

		/*Line 0*/
		_values[0] = p_cols[0]._x;
		_values[1] = p_cols[1]._x;
		_values[2] = p_cols[2]._x;

		/*Line 1*/
		_values[3] = p_cols[0]._y;
		_values[4] = p_cols[1]._y;
		_values[5] = p_cols[2]._y;

		/*Line 2*/
		_values[6] = p_cols[0]._z;
		_values[7] = p_cols[1]._z;
		_values[8] = p_cols[2]._z;
	}

	Matrix3x3::Matrix3x3(float p_v1, float p_v2, float p_v3, float p_v4, float p_v5, float p_v6, float p_v7, float p_v8, float p_v9)
	{
		_values[0] = p_v1;
		_values[1] = p_v2;
		_values[2] = p_v3;
		_values[3] = p_v4;
		_values[4] = p_v5;
		_values[5] = p_v6;
		_values[6] = p_v7;
		_values[7] = p_v8;
		_values[8] = p_v9;
	}

	Matrix3x3::Matrix3x3(const Matrix3x3& p_matrix)
	{
		for (int i = 0; i < 9; i++)
		{
			_values[i] = p_matrix._values[i];
		}
	}

	float& Matrix3x3::operator[] (int p_index)
	{
		return _values[p_index];
	}

	const float& Matrix3x3::operator[] (int p_index) const
	{
		return _values[p_index];
	}

	Vector3 Matrix3x3::operator*(const Vector3& p_vector) const
	{
		return Vector3(
			_values[0] * p_vector._x + _values[1] * p_vector._y + _values[2] * p_vector._z,
			_values[3] * p_vector._x + _values[4] * p_vector._y + _values[5] * p_vector._z,
			_values[6] * p_vector._x + _values[7] * p_vector._y + _values[8] * p_vector._z);
	}

	Matrix3x3 Matrix3x3::operator*(const Matrix3x3& p_matrix) const
	{
		return Matrix3x3(
			_values[0] * p_matrix._values[0] + _values[1] * p_matrix._values[3] + _values[2] * p_matrix._values[6],
			_values[0] * p_matrix._values[1] + _values[1] * p_matrix._values[4] + _values[2] * p_matrix._values[7],
			_values[0] * p_matrix._values[2] + _values[1] * p_matrix._values[5] + _values[2] * p_matrix._values[8],

			_values[3] * p_matrix._values[0] + _values[4] * p_matrix._values[3] + _values[5] * p_matrix._values[6],
			_values[3] * p_matrix._values[1] + _values[4] * p_matrix._values[4] + _values[5] * p_matrix._values[7],
			_values[3] * p_matrix._values[2] + _values[4] * p_matrix._values[5] + _values[5] * p_matrix._values[8],

			_values[6] * p_matrix._values[0] + _values[7] * p_matrix._values[3] + _values[8] * p_matrix._values[6],
			_values[6] * p_matrix._values[1] + _values[7] * p_matrix._values[4] + _values[8] * p_matrix._values[7],
			_values[6] * p_matrix._values[2] + _values[7] * p_matrix._values[5] + _values[8] * p_matrix._values[8]
			);
	}

	Matrix3x3& Matrix3x3::operator*= (const Matrix3x3& p_matrix) {
		/*Line 0*/
		_values[0] = _values[0] * p_matrix._values[0] + _values[1] * p_matrix._values[3] + _values[2] * p_matrix._values[6],
		_values[1] = _values[0] * p_matrix._values[1] + _values[1] * p_matrix._values[4] + _values[2] * p_matrix._values[7],
		_values[2] = _values[0] * p_matrix._values[2] + _values[1] * p_matrix._values[5] + _values[2] * p_matrix._values[8],

		/*Line 1*/
		_values[3] = _values[3] * p_matrix._values[0] + _values[4] * p_matrix._values[3] + _values[5] * p_matrix._values[6],
		_values[4] = _values[3] * p_matrix._values[1] + _values[4] * p_matrix._values[4] + _values[5] * p_matrix._values[7],
		_values[5] = _values[3] * p_matrix._values[2] + _values[4] * p_matrix._values[5] + _values[5] * p_matrix._values[8],

		/*Line 2*/
		_values[6] = _values[6] * p_matrix._values[0] + _values[7] * p_matrix._values[3] + _values[8] * p_matrix._values[6],
		_values[7] = _values[6] * p_matrix._values[1] + _values[7] * p_matrix._values[4] + _values[8] * p_matrix._values[7],
		_values[8] = _values[6] * p_matrix._values[2] + _values[7] * p_matrix._values[5] + _values[8] * p_matrix._values[8];
		
		return (*this);
	
	}

	void Matrix3x3::invert()
	{
		float det = _values[0] * _values[4] * _values[8] + _values[3] * _values[7] * _values[2] + _values[6] * _values[1] * _values[5] -
			_values[0] * _values[7] * _values[5] - _values[6] * _values[4] * _values[2] - _values[3] * _values[1] * _values[8];

		//std::cout << "Determinant " << det<<std::endl;
		// Cannot divide by 0
		if (det <0.000001 && det>-0.000001) return;

		float inverseDet = 1.0f / det;

		// Create an old matrix to keep track of coefficient
		Matrix3x3 m(*this);

		_values[0] = m._values[4] * m._values[8] - m._values[5] * m._values[7];
		_values[1] = m._values[2] * m._values[7] - m._values[1] * m._values[8];
		_values[2] = m._values[1] * m._values[5] - m._values[2] * m._values[4];
		_values[3] = m._values[5] * m._values[6] - m._values[3] * m._values[8];
		_values[4] = m._values[0] * m._values[8] - m._values[2] * m._values[6];
		_values[5] = m._values[2] * m._values[3] - m._values[0] * m._values[5];
		_values[6] = m._values[3] * m._values[7] - m._values[4] * m._values[6];
		_values[7] = m._values[1] * m._values[6] - m._values[0] * m._values[7];
		_values[8] = m._values[0] * m._values[4] - m._values[1] * m._values[3];

		for (int i = 0; i < 9; i++)
		{
			_values[i] *= inverseDet;
		}
	}

	Matrix3x3& Matrix3x3::getInversion() const {
		Matrix3x3 result(*this);
		result.invert();
		return result;
	}

	void Matrix3x3::transpose()
	{
		std::swap(_values[1], _values[3]);
		std::swap(_values[2], _values[6]);
		std::swap(_values[5], _values[7]);
	}

	Matrix3x3& Matrix3x3::getTranspose() const {
		Matrix3x3 result(*this);
		result.transpose();
		return result;
	}

	Matrix3x3& Matrix3x3::identity() {
		Matrix3x3 result;
		result._values[0] = 1;
		result._values[4] = 1;
		result._values[8] = 1;
		return result;
	}

	Matrix3x3 Matrix3x3::convertGlm(const glm::mat3& p_mat) {
		return Matrix3x3(
			p_mat[0][0], p_mat[1][0], p_mat[2][0],
			p_mat[0][1], p_mat[1][1], p_mat[2][1], 
			p_mat[0][2], p_mat[1][2], p_mat[2][2] 
		);
	}

	glm::mat3 Matrix3x3::toGlm(const Matrix3x3& p_mat) {
		return glm::mat3(
			p_mat[0], p_mat[3], p_mat[6],
			p_mat[1], p_mat[4], p_mat[7],
			p_mat[2], p_mat[5], p_mat[8]
		);

	}
}