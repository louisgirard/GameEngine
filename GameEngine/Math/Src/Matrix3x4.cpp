#include <Math/Header/Matrix3x4.hpp>

namespace Math
{
	Matrix3x4::Matrix3x4()
	{
		for (int i = 0; i < 12; i++)
		{
			_values[i] = 0;
		}
	}

	Matrix3x4::Matrix3x4(Vector3* const p_cols) {
		/*Line 0*/
		_values[0] = p_cols[0]._x;
		_values[1] = p_cols[1]._x;
		_values[2] = p_cols[2]._x;
		_values[3] = p_cols[3]._x;

		/*Line 1*/
		_values[4] = p_cols[0]._y;
		_values[5] = p_cols[1]._y;
		_values[6] = p_cols[2]._y;
		_values[7] = p_cols[3]._y;

		/*Line 2*/
		_values[8] = p_cols[0]._z;
		_values[9] = p_cols[1]._z;
		_values[10] = p_cols[2]._z;
		_values[11] = p_cols[3]._z;
	}

	Matrix3x4::Matrix3x4(float p_v1, float p_v2, float p_v3, float p_v4, float p_v5, float p_v6, float p_v7, float p_v8, float p_v9, float p_v10, float p_v11, float p_v12)
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
		_values[9] = p_v10;
		_values[10] = p_v11;
		_values[11] = p_v12;
	}

	Matrix3x4::Matrix3x4(const Matrix3x4& p_matrix)
	{
		for (int i = 0; i < 12; i++)
		{
			_values[i] = p_matrix._values[i];
		}
	}

	float& Matrix3x4::operator[] (int p_index)
	{
		return _values[p_index];
	}

	const float& Matrix3x4::operator[] (int p_index) const
	{
		return _values[p_index];
	}

	Matrix3x4 Matrix3x4::operator*(const Matrix3x4& p_matrix) const
	{
		return Matrix3x4(
			_values[0] * p_matrix._values[0] + _values[1] * p_matrix._values[4] + _values[2] * p_matrix._values[8],
			_values[0] * p_matrix._values[1] + _values[1] * p_matrix._values[5] + _values[2] * p_matrix._values[9],
			_values[0] * p_matrix._values[2] + _values[1] * p_matrix._values[6] + _values[2] * p_matrix._values[10],
			_values[0] * p_matrix._values[3] + _values[1] * p_matrix._values[7] + _values[2] * p_matrix._values[11] + _values[3],

			_values[4] * p_matrix._values[0] + _values[5] * p_matrix._values[4] + _values[6] * p_matrix._values[8],
			_values[4] * p_matrix._values[1] + _values[5] * p_matrix._values[5] + _values[6] * p_matrix._values[9],
			_values[4] * p_matrix._values[2] + _values[5] * p_matrix._values[6] + _values[6] * p_matrix._values[10],
			_values[4] * p_matrix._values[3] + _values[5] * p_matrix._values[7] + _values[6] * p_matrix._values[11] + _values[7],

			_values[8] * p_matrix._values[0] + _values[9] * p_matrix._values[4] + _values[10] * p_matrix._values[8],
			_values[8] * p_matrix._values[1] + _values[9] * p_matrix._values[5] + _values[10] * p_matrix._values[9],
			_values[8] * p_matrix._values[2] + _values[9] * p_matrix._values[6] + _values[10] * p_matrix._values[10],
			_values[8] * p_matrix._values[3] + _values[9] * p_matrix._values[7] + _values[10] * p_matrix._values[11] + _values[11]
			);
	}

	Matrix3x4& Matrix3x4::operator*= (const Matrix3x4& p_matrix) {

		/*Line 0*/
		_values[0] = _values[0] * p_matrix._values[0] + _values[1] * p_matrix._values[4] + _values[2] * p_matrix._values[8];
		_values[1] = _values[0] * p_matrix._values[1] + _values[1] * p_matrix._values[5] + _values[2] * p_matrix._values[9];
		_values[2] = _values[0] * p_matrix._values[2] + _values[1] * p_matrix._values[6] + _values[2] * p_matrix._values[10];
		_values[3] = _values[0] * p_matrix._values[3] + _values[1] * p_matrix._values[7] + _values[2] * p_matrix._values[11] + _values[3];

		/*Line 1*/
		_values[4] = _values[4] * p_matrix._values[0] + _values[5] * p_matrix._values[4] + _values[6] * p_matrix._values[8];
		_values[5] = _values[4] * p_matrix._values[1] + _values[5] * p_matrix._values[5] + _values[6] * p_matrix._values[9];
		_values[6] = _values[4] * p_matrix._values[2] + _values[5] * p_matrix._values[6] + _values[6] * p_matrix._values[10];
		_values[7] = _values[4] * p_matrix._values[3] + _values[5] * p_matrix._values[7] + _values[6] * p_matrix._values[11] + _values[7];

		/*Line 2*/
		_values[8] = _values[8] * p_matrix._values[0] + _values[9] * p_matrix._values[4] + _values[10] * p_matrix._values[8];
		_values[9] = _values[8] * p_matrix._values[1] + _values[9] * p_matrix._values[5] + _values[10] * p_matrix._values[9];
		_values[10] = _values[8] * p_matrix._values[2] + _values[9] * p_matrix._values[6] + _values[10] * p_matrix._values[10];
		_values[11] = _values[8] * p_matrix._values[3] + _values[9] * p_matrix._values[7] + _values[10] * p_matrix._values[11] + _values[11];

		return (*this);
	}

	bool Matrix3x4::invert()
	{
		// afk−agj−bek+bgi+cej−cfi
		float det = _values[0] * _values[5] * _values[10] - _values[0] * _values[6] * _values[9] - _values[1] * _values[4] * _values[10] +
			_values[1] * _values[6] * _values[8] + _values[2] * _values[4] * _values[9] - _values[2] * _values[5] * _values[8];

		// Cannot divide by 0
		if (det == 0) return false;

		float inverseDet = 1.0f / det;

		// Create an old matrix to keep track of coefficient
		Matrix3x4 m(*this);

		_values[0] = -m._values[6] * m._values[9] + m._values[5] * m._values[10];
		_values[1] = m._values[2] * m._values[9] - m._values[1] * m._values[10];
		_values[2] = - m._values[2] * m._values[5] + m._values[1] * m._values[6];
		_values[3] = m._values[3] * m._values[6] * m._values[9] - m._values[2] * m._values[7] * m._values[9] -
			m._values[3] * m._values[5] * m._values[10] + m._values[1] * m._values[7] * m._values[10] +
			m._values[2] * m._values[5] * m._values[11] - m._values[1] * m._values[6] * m._values[11];

		_values[4] = m._values[6] * m._values[8] - m._values[4] * m._values[10];
		_values[5] = -m._values[2] * m._values[8] + m._values[0] * m._values[10];
		_values[6] = m._values[2] * m._values[4] - m._values[0] * m._values[6];
		_values[7] = -m._values[3] * m._values[6] * m._values[8] + m._values[2] * m._values[7] * m._values[8] +
			m._values[3] * m._values[4] * m._values[10] - m._values[0] * m._values[7] * m._values[10] -
			m._values[2] * m._values[4] * m._values[11] + m._values[0] * m._values[6] * m._values[11];

		_values[8] = -m._values[5] * m._values[8] + m._values[4] * m._values[9];
		_values[9] = m._values[1] * m._values[8] - m._values[0] * m._values[9];
		_values[10] = -m._values[1] * m._values[4] + m._values[0] * m._values[5];
		_values[11] = m._values[3] * m._values[5] * m._values[8] - m._values[1] * m._values[7] * m._values[8] -
			m._values[3] * m._values[4] * m._values[9] + m._values[0] * m._values[7] * m._values[9] +
			m._values[1] * m._values[4] * m._values[11] - m._values[0] * m._values[5] * m._values[11];

		for (int i = 0; i < 12; i++)
		{
			_values[i] *= inverseDet;
		}

		return true;
	}

	Matrix3x4& Matrix3x4::getInversion() const {
		Matrix3x4 result(*this);
		result.invert();
		return result;
	}

	void Matrix3x4::transpose() {
		std::swap(_values[1], _values[4]);
		std::swap(_values[2], _values[8]);
		std::swap(_values[6], _values[9]);

		_values[3] = 0;
		_values[7] = 0;
		_values[11] = 0;
	}

	Matrix3x4& Matrix3x4::getTranspose() const {
		Matrix3x4 result(*this);
		result.transpose();
		return result;
	}

	void Matrix3x4::setRotationMatrix(const Matrix3x3& p_rotationMatrix) {
		/*Line 0*/
		_values[0] = p_rotationMatrix[0];
		_values[1] = p_rotationMatrix[1];
		_values[2] = p_rotationMatrix[2];

		/*Line 1*/
		_values[4] = p_rotationMatrix[3];
		_values[5] = p_rotationMatrix[4];
		_values[6] = p_rotationMatrix[5];

		/*Line 2*/
		_values[8] = p_rotationMatrix[6];
		_values[9] = p_rotationMatrix[7];
		_values[10] = p_rotationMatrix[8];
	}

	void Matrix3x4::setTR(const Quaternion& p_quaternion, const Vector3& p_pos) {
		setRotationMatrix(p_quaternion.getOrientationMatrix());
		_values[3] = p_pos._x;
		_values[7] = p_pos._y;
		_values[11] = p_pos._z;
	}

	Vector3 Matrix3x4::transformPoint(const Vector3& p_point) const {
		return Vector3(
			_values[0] * p_point._x + _values[1] * p_point._y + _values[2] * p_point._z + _values[3],
			_values[4] * p_point._x + _values[5] * p_point._y + _values[6] * p_point._z + _values[7],
			_values[8] * p_point._x + _values[9] * p_point._y + _values[10] * p_point._z + _values[11]);
	}


	Vector3 Matrix3x4::transformDirection(const Vector3& p_direction) const {
		return Vector3(
			_values[0] * p_direction._x + _values[1] * p_direction._y + _values[2] * p_direction._z,
			_values[4] * p_direction._x + _values[5] * p_direction._y + _values[6] * p_direction._z,
			_values[8] * p_direction._x + _values[9] * p_direction._y + _values[10] * p_direction._z);
	}

	Matrix3x4& Matrix3x4::identity() {
		Matrix3x4 result;
		result._values[0] = 1;
		result._values[5] = 1;
		result._values[10] = 1;
		return result;
	}

	Matrix3x4 Matrix3x4::convertGlm(const glm::mat4& p_mat) {
		return Matrix3x4(
			p_mat[0][0], p_mat[1][0], p_mat[2][0], p_mat[3][0],
			p_mat[0][1], p_mat[1][1], p_mat[2][1], p_mat[3][1],
			p_mat[0][2], p_mat[1][2], p_mat[2][2], p_mat[3][2]
		);
	}

	glm::mat4 Matrix3x4::toGlm(const Matrix3x4& p_mat) {
		return glm::mat4(
			p_mat[0], p_mat[4], p_mat[8], 1,
			p_mat[1], p_mat[5], p_mat[9], 0,
			p_mat[2], p_mat[6], p_mat[10], 0,
			p_mat[3], p_mat[7], p_mat[11], 0
		);

	}
}