﻿#include <PhysicEngine/Header/Matrix4.hpp>

namespace PhysicEngine
{
	Matrix4::Matrix4()
	{
		for (int i = 0; i < 12; i++)
		{
			_values[i] = 0;
		}
	}

	Matrix4::Matrix4(float p_v1, float p_v2, float p_v3, float p_v4, float p_v5, float p_v6, float p_v7, float p_v8, float p_v9, float p_v10, float p_v11, float p_v12)
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

	Matrix4::Matrix4(const Matrix4& p_matrix)
	{
		for (int i = 0; i < 12; i++)
		{
			_values[i] = p_matrix._values[i];
		}
	}

	Vector3 Matrix4::operator*(const Vector3& p_vector) const
	{
		return Vector3(
			_values[0] * p_vector._x + _values[1] * p_vector._y + _values[2] * p_vector._z + _values[3],
			_values[4] * p_vector._x + _values[5] * p_vector._y + _values[6] * p_vector._z + _values[7],
			_values[8] * p_vector._x + _values[9] * p_vector._y + _values[10] * p_vector._z + _values[11]);
	}

	Matrix4 Matrix4::operator*(const Matrix4& p_matrix) const
	{
		return Matrix4(
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

	void Matrix4::invert()
	{
		// afk−agj−bek+bgi+cej−cfi
		float det = _values[0] * _values[5] * _values[10] - _values[0] * _values[6] * _values[9] - _values[1] * _values[4] * _values[10] +
			_values[1] * _values[6] * _values[8] + _values[2] * _values[4] * _values[9] - _values[2] * _values[5] * _values[8];

		// Cannot divide by 0
		if (det == 0) return;

		float inverseDet = 1.0f / det;

		// Create an old matrix to keep track of coefficient
		Matrix4 m(*this);

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
	}

	
}