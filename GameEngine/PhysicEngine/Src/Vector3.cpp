#include <PhysicEngine/Header/Vector3.hpp>

namespace PhysicEngine {
	const Vector3 Vector3::ZERO(0, 0, 0);
	const Vector3 Vector3::FRONT(0,0,-1);
	const Vector3 Vector3::RIGHT(1,0,0);
	const Vector3 Vector3::UP(1,0,0);

	Vector3::Vector3() : _x(0), _y(0), _z(0)
	{
	}

	Vector3::Vector3(float p_x, float p_y, float p_z) : _x(p_x), _y(p_y), _z(p_z)
	{
	}

	void Vector3::invert()
	{
		_x = -_x;
		_y = -_y;
		_z = -_z;
	}

	float Vector3::magnitude() const
	{
		return sqrt(_x * _x + _y * _y + _z * _z);
	}

	float Vector3::squaredMagnitude() const
	{
		return (_x * _x + _y * _y + _z * _z);
	}

	void Vector3::normalize()
	{
		float magnitude = this->magnitude();
		if (magnitude > 0) {
			*this *= (1.0f / magnitude);
		}
	}

	void Vector3::operator*=(const float p_value)
	{
		_x *= p_value;
		_y *= p_value;
		_z *= p_value;
	}

	Vector3 Vector3::operator*(const float p_value) const
	{
		return Vector3(_x * p_value, _y * p_value, _z * p_value);
	}

	void Vector3::operator+=(const Vector3& p_vector)
	{
		_x += p_vector._x;
		_y += p_vector._y;
		_z += p_vector._z;
	}

	Vector3 Vector3::operator+(const Vector3& p_vector) const
	{
		return Vector3(_x + p_vector._x, _y + p_vector._y, _z + p_vector._z);
	}

	void Vector3::operator-=(const Vector3& p_vector)
	{
		_x -= p_vector._x;
		_y -= p_vector._y;
		_z -= p_vector._z;
	}

	Vector3 Vector3::operator-(const Vector3& p_vector) const
	{
		return Vector3(_x - p_vector._x, _y - p_vector._y, _z - p_vector._z);
	}

	Vector3 Vector3::componentProduct(const Vector3& vector) const
	{
		return Vector3(_x * vector._x, _y * vector._y, _z * vector._z);
	}

	void Vector3::componentProductUpdate(const Vector3& p_vector)
	{
		_x *= p_vector._x;
		_y *= p_vector._y;
		_z *= p_vector._z;
	}

	float Vector3::scalarProduct(const Vector3& p_vector) const
	{
		return _x * p_vector._x + _y * p_vector._y + _z * p_vector._z;
	}

	Vector3 Vector3::vectorProduct(const Vector3& p_vector) const
	{
		return Vector3(_y * p_vector._z - _z * p_vector._y,
			_z * p_vector._x - _x * p_vector._z,
			_x * p_vector._y - _y * p_vector._x);
	}

	Vector3 Vector3::convertGlm(const glm::vec3& p_vec) {
		return Vector3(p_vec.x, p_vec.y, p_vec.z);
	}

}

