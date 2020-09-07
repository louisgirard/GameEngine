#include "Vector3.h"

Vector3::Vector3() : x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

void Vector3::invert()
{
	x = -x;
	y = -y;
	z = -z;
}

float Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

float Vector3::squaredMagnitude() const
{
	return (x * x + y * y + z * z);
}

void Vector3::normalize()
{
	float magnitude = this->magnitude();
	if (magnitude > 0) {
		*this *= (1.0 / magnitude);
	}
}

void Vector3::operator*=(const float value)
{
	x *= value;
	y *= value;
	z *= value;
}

Vector3 Vector3::operator*(const float value) const
{
	return Vector3(x * value, y * value, z * value);
}

void Vector3::operator+=(const Vector3& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
}

Vector3 Vector3::operator+(const Vector3& vector) const
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

void Vector3::operator-=(const Vector3& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
}

Vector3 Vector3::operator-(const Vector3& vector) const
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::componentProduct(const Vector3& vector) const
{
	return Vector3(x * vector.x, y * vector.y, z * vector.z);
}

void Vector3::componentProductUpdate(const Vector3& vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
}

float Vector3::scalarProduct(const Vector3& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z;
}

Vector3 Vector3::vectorProduct(const Vector3& vector) const
{
	return Vector3(y * vector.z - z * vector.y,
		z * vector.x - x * vector.z,
		x * vector.y - y * vector.x);
}
