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
		* Copy constructor
		* @param p_quaternion : quaternion to copy
		*/
		Quaternion(const Quaternion& p_quaternion);
		
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
		* Copy operator
		* @param p_other : quaternion to copy
		* @return a copy of this vector
		*/
		Quaternion& operator= (const Quaternion& p_other);

		/*
		* Rotate the quaternion from axis by an angle
		* @param p_euler : the vector that contains euler rotation by axis
		*/
		void rotateFromVector(const Vector3& p_vector);

		/*
		* Update the angular velocity by a time
		* @param p_aVelocity : Angular velocity
		* @param p_time : time to which it will be updated (in sec)
		*/
		void updateAngularVelocity(const Vector3& p_aVelocity, float p_time);

		/*
		* Gets equivalent orientation matrix
		* Don't use this too much as there are some approximation issues 
		* @return a 3x3 matrix equivalent to this quaternion
		*/
		Matrix3x3 getOrientationMatrix() const;


	};

	/*
	* Print a quaternion
	* @param p_vec : the vector to print
	*/
	inline std::ostream& operator << (std::ostream& p_out, const Quaternion& p_quaternion)
	{
		std::cout << "(" << p_quaternion._r << ", " << p_quaternion._complex<< ")";
		return p_out;
	}
}


