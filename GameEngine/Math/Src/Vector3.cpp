#include <Math/Header/Vector3.hpp>
#include <Math/Header/Matrix3x4.hpp>

namespace Math {
	const Vector3 Vector3::ZERO(0, 0, 0);
	const Vector3 Vector3::ONE(1, 1, 1);
	const Vector3 Vector3::FRONT(0,0,-1);
	const Vector3 Vector3::RIGHT(1,0,0);
	const Vector3 Vector3::LEFT(-1, 0, 0);
	const Vector3 Vector3::UP(0,1,0);
	const Vector3 Vector3::DOWN(0, -1, 0);

	Vector3::Vector3() : _x(0), _y(0), _z(0)
	{
	}

	Vector3::Vector3(float* p_components) : _x(p_components[0]), _y(p_components[1]), _z(p_components[2]) {}

	Vector3::Vector3(float p_x, float p_y, float p_z) : _x(p_x), _y(p_y), _z(p_z){}

	Vector3::Vector3(const Vector3& p_vec) : _x(p_vec._x), _y(p_vec._y), _z(p_vec._z) {}

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

	float& Vector3::operator[] (int p_index) {
		assert((p_index >= 0 && p_index < 3) && "Index must be in [0,2]");
		switch (p_index) {
		case 0:
			return _x;
		case 1:
			return _y;
		case 2:
			return _z;
		default :
			break;
		}
	}

	const float& Vector3::operator[] (int p_index) const {
		assert((p_index >= 0 && p_index < 3) && "Index must be in [0,2]");
		switch (p_index) {
		case 0:
			return _x;
		case 1:
			return _y;
		case 2:
			return _z;
		default:
			break;
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

	Vector3& Vector3::operator= (float const& p_value)
	{
		_x = p_value;
		_y = p_value;
		_z = p_value;
		return *this;
	}

	Vector3& Vector3::operator= (Vector3 const& p_vec)
	{
		_x = p_vec._x;
		_y = p_vec._y;
		_z = p_vec._z;
		return (*this);
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

	Vector3 Vector3::localToWorld(const Matrix3x4& worldTransform) {
		return worldTransform.transformPoint((*this));
	}

	Vector3 Vector3::worldToLocal(const Matrix3x4& worldTransform) {
		Matrix3x4 inverseTransform = worldTransform;
		inverseTransform.invert();
		return inverseTransform.transformPoint((*this));
	}

	Vector3 Vector3::localDirectionToWorld(const Matrix3x4& worldTransform) {
		return worldTransform.transformDirection((*this));
	}
	Vector3 Vector3::worldDirectionToLocal(const Matrix3x4& worldTransform) {
		Matrix3x4 inverseTransform = worldTransform;
		inverseTransform.invert();
		return inverseTransform.transformDirection((*this));
	}

	Vector3 Vector3::convertGlm(const glm::vec3& p_vec) {
		return Vector3(p_vec.x, p_vec.y, p_vec.z);
	}

	glm::vec3  Vector3::toGlm(const Vector3& p_vec) {
		return glm::vec3(p_vec._x, p_vec._y, p_vec._z);
	}

	std::string Vector3::ToString()
	{
		return "(" + std::to_string(_x) + ", " + std::to_string(_y) + ", " + std::to_string(_z) + ")";
	}

}

