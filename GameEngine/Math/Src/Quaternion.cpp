#include "Math/Header/Quaternion.hpp"

namespace Math {

	Quaternion::Quaternion() {
		_r = 1;
	}

	Quaternion::Quaternion(float p_real, const Vector3& p_complex) {
		_r = p_real;
		_complex = p_complex;
	}

	void Quaternion::normalize() {

		float squaredNorm = _r * _r + _complex.squaredMagnitude();

		if (squaredNorm == 0) {
			_r = 1;
			return;
		}

		float invNorm = 1.f / sqrt(squaredNorm);
		_r *= invNorm;
		_complex *= invNorm;
	}

	Quaternion& Quaternion::operator*= (const Quaternion& p_other) {

		//Formula from classes
		_r = _r * p_other._r - _complex.scalarProduct(p_other._complex);
		_complex = p_other._complex * _r + _complex * p_other._r + _complex.vectorProduct(p_other._complex);

		return (*this);
	}

	void Quaternion::rotateFromEulerVector(const Vector3& p_euler) {
		// Equivalent of the vector as quaternion
		Quaternion q(0, p_euler);
		(*this) *= q;
	}

	void Quaternion::updateAngularVelocity(const Vector3& p_euler, float p_time) {
		// We take a certain amount of rotation given time
		Quaternion q(0, p_euler * p_time);
		/*Multiply current rotation with angular velocity that as been weighted by time*/
		q *= *this;
		/*then we multiply by the 0.5 factor of the equation (because of the derivation)*/
		_r = q._r * 0.5f;
		_complex = q._complex * 0.5f;
	}

	Matrix3x3& Quaternion::getOrientationMatrix() const{
	
		//Formula from classes
		Vector3 cols[3];
		cols[0] = Vector3(
			1.f - (2.f * _complex[1] * _complex[1] + 2.f * _complex[2] * _complex[2]),
			2.f*_complex[0]*_complex[1] - 2.f*_complex[2]*_r,
			2.f*_complex[0]*_complex[2] + 2*_complex[1]*_r
		);
		cols[1] = Vector3(
			2.f*_complex[0]*_complex[1] + 2.f*_complex[2]*_r,
			1-(2.f*_complex[0]*_complex[0] + 2.f*_complex[2]*_complex[2]),
			2.f*_complex[1]*_complex[2] - 2.f*_complex[0]*_r
		
		);
		cols[2] = Vector3(
			2.f * _complex[0] * _complex[2] - 2.f * _complex[1] * _r,
			2.f * _complex[1] * _complex[2] + 2.f * _complex[0] * _r,
			1 - (2.f * _complex[0] * _complex[0] + 2 * _complex[1] * _complex[1])
		);

		Matrix3x3 result(cols);
		return result;
	}
}