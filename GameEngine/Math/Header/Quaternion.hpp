#pragma once

#include <Math/Header/Matrix3x3.hpp>

namespace Math {
	/*Contains a 3 DOF rotation */
	class Quaternion
	{
	public :
		/* real component of the quaternion */
		float _r;
		/* Holds the complex component of the quaternion */
		Vector3 _complex;

		/*
		* Default constructor 
		* Set as quaternion identity
		*/
		Quaternion();

		/*
		* Constructor
		* @param p_real : real component
		* @param p_complex : complex components
		*/
		Quaternion(float p_real, const Vector3& p_complex);
		
		/*
		* Normalize the quaternion 
		*/
		void normalize();

		/*
		* Multiply operator
		* @param p_other : quaternion to multiply
		* @return a copy of this vector
		*/
		Quaternion& operator*= (const Quaternion& p_other);

		/*
		* Rotate the quaternion from axis by an angle
		* @param p_euler : the vector that contains euler rotation by axis
		*/
		void rotateFromEulerVector(const Vector3& p_euler);

		/*
		* Update the angular velocity by a time
		*/
		void updateAngularVelocity(const Vector3& p_euler, float p_time);

		/*
		* Gets equivalent orientation matrix
		* @return a 3x3 matrix equivalent to this quaternion
		*/
		Matrix3x3& getOrientationMatrix() const;


	};
}


