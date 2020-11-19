#include "Math/Header/Quaternion.hpp"

namespace Math {

	Quaternion::Quaternion() {
		_r = 1;
	}

	Quaternion::Quaternion(float p_real, const Vector3& p_complex) {
		_r = p_real;
		_complex = p_complex;
	}

	Quaternion::Quaternion(const Quaternion& p_quaternion) {
		_r = p_quaternion._r;
		_complex = p_quaternion._complex;
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

	Quaternion& Quaternion::operator= (const Quaternion& p_other) {
		_r = p_other._r;
		_complex = p_other._complex;
		return (*this);
	}

	Quaternion& Quaternion::operator*= (const Quaternion& p_other) {

		//Formula from classes
		float saveR = _r;
		Vector3 saveComplex = _complex;

		_r = saveR * p_other._r - saveComplex.scalarProduct(p_other._complex);
		_complex = saveComplex * p_other._r + p_other._complex * saveR + saveComplex.vectorProduct(p_other._complex);

		return (*this);
	}

	void Quaternion::rotateFromVector(const Vector3& p_vector) {
		// Equivalent of the vector as quaternion
		Quaternion q(0, p_vector);
		(*this) *= q;
	}



	void Quaternion::updateAngularVelocity(const Vector3& p_aVelocity, float p_time) {

		// We take a certain amount of rotation given time
		Quaternion q(0, p_aVelocity);
		/*Multiply angular velocity that as been weighted by time with current orientation */
		q *= *this;
		/*then we multiply by the 0.5*time factor of the equation (because of the derivation)*/
		_r += q._r * 0.5f* p_time;
		_complex += q._complex * 0.5f* p_time;
	}

	Matrix3x3 Quaternion::getOrientationMatrix() const{
	
		Quaternion q(*this);
		q.normalize();

		Vector3 saveComplex = q._complex;
		float saveR = q._r;

		//Formula from classes
		Vector3 cols[3];
		cols[0] = Vector3(
			1.f - 2.f*(saveComplex[1] * saveComplex[1] + saveComplex[2] * saveComplex[2]),
			2.f* (saveComplex[0]* saveComplex[1] - saveComplex[2]* saveR),
			2.f* (saveComplex[0]* saveComplex[2] + saveComplex[1]* saveR)
		);
		cols[1] = Vector3(
			2.f* (saveComplex[0]* saveComplex[1] + saveComplex[2]* saveR),
			1- 2.f * ( saveComplex[0]* saveComplex[0] + saveComplex[2]* saveComplex[2]),
			2.f* (saveComplex[1]* saveComplex[2] - saveComplex[0]* saveR)
		);
		cols[2] = Vector3(
			2.f * (saveComplex[0] * saveComplex[2] - saveComplex[1] * saveR),
			2.f * (saveComplex[1] * saveComplex[2] + saveComplex[0] * saveR),
			1 - 2.f * (saveComplex[0] * saveComplex[0] + saveComplex[1] * saveComplex[1])
		);

		Matrix3x3 result(cols);
		return result;
	}
}