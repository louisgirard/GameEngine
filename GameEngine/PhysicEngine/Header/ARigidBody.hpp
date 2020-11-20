#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>

namespace PhysicEngine {
	class ARigidBody
	{
	public:

		float _inverseMass;

		float _linearDamping;

		float _angularDamping;

		//Center of mass position in world space
		Vector3 _position;

		//Orientation of the rigidbody in world space
		Quaternion _orientation;

		//Veclocity of the center of mass in world space
		Vector3 _velocity;

		//Angular velocity in world space
		Vector3 _angularVelocity;

		//Transformation matrix of the body
		Matrix3x4 _transformMatrix;

		//Inverse inertia tensor in local space
		Matrix3x3 _inverseInertiaTensor;

		//Inverse inertia tensor in world space
		Matrix3x3 _inverseInertiaTensorWorld;

		//force accumulator
		Vector3 _forceAccum;

		//torque accumulator
		Vector3 _torqueAccum;

	
		ARigidBody(float p_inverseMass, Matrix3x3 p_inverseInertiaTensor, Vector3 p_position, Quaternion p_orientation, 
			Vector3 p_velocity, Vector3 p_angularVelocity, float p_linearDamping, float p_angularDamping);

		/*@return the position of the body */
		Vector3 getPosition() const;

		/* Sets the position of the body
		@param p_position the position to which the body must be set
		*/
		void setPosition(const Vector3& p_position);

		/* Sets the position of the body
		@param p_x the new x of the body
		@param p_y the new y of the body
		@param p_z the new z of the body
		*/
		void setPosition(const float p_x, const float p_y, const float p_z);

		/*@return the velocity of the body */
		Vector3 getVelocity() const;

		/* Sets the velocity of the body
		@param p_velocity the velocity at which the body must be set
		*/
		void setVelocity(const Vector3& p_velocity);

		/* Sets the velocity of the body
		@param p_x the new x of the velocity
		@param p_y the new y of the velocity
		@param p_z the new z of the velocity
		*/
		void setVelocity(const float p_x, const float p_y, const float p_z);

		/*@return the linear damping */
		float getLinearDamping() const;

		/* Sets the damping
		@param p_damping the new damping
		*/
		void setLinearDamping(const float p_linearDamping);

		/*@return the damping */
		float getAngularDamping() const;

		/* Sets the damping
		@param p_damping the new damping
		*/
		void setAngularDamping(const float p_angularDamping);

		/*@return the inverse of the mass of the body */
		float getInverseMass() const;

		/* Sets the inverse of the mass of the body
		@param p_inverseMass the new inverse mass of the body
		*/
		void setInverseMass(const float p_inverseMass);

		/*@return the mass of the body */
		float getMass() const;

		/* Sets the mass of the body
		@param p_mass the new mass of the body
		*/
		void setMass(const float p_mass);

		//updates internal data (transformMatrix, world space inertia tensor)
		void calculateDerivedData();

		/*
		* Calculates the transformation matrix of a giiven position and orientation
		* @param p_transformMatrix: the matrix to put the result in
		* @param p_position: the position of the transform
		* @param p_orientation: the orientation of the transform
		*/
		static inline void s_calculateTransformMatrix(Matrix3x4 &p_transformMatrix, const Vector3 &p_position, const Quaternion &p_orientation);

		void SetInertiaTensor(Matrix3x3 p_inertiaTensor);

		/*Transforms the local space inertia tensor into a world space inertia tensor
		* @param p_iitWorld: the matrix to put the world space inertia tensor in
		* @param p_iitBody: the local space inertia tensor
		* @param p_rotMat: the transformation matrix of the body (treated as a rotation matrix)
		*/
		static inline void s_transformInertiaTensor(Matrix3x3& p_iitWorld, const Matrix3x3& p_iitBody, const Matrix3x4& p_rotMat);

		/*Adds a force at the center of mass of the rigidbody (no torque)
		* @param p_force: the force to apply
		*/
		void addForce(const Vector3& p_force);

		/*
		* Adds a force at a given point of the body in world space coordinates
		* @param p_force: the force to apply (world coordinates)
		* @param p_point: the point to apply the force at (world coordinates)
		*/
		void addForceAtPoint(const Vector3& p_force, const Vector3& p_point);

		/*
		* Adds a force at a given point of the body in local space coordinates
		* @param p_force: the force to apply (world coordinates)
		* @param p_point: the point to apply the force at (local coordinates)
		*/
		void addForceAtLocalPoint(const Vector3& p_force, const Vector3& p_point);

		//Clears the force and torque accumulators
		void clearAccumulators();

		void integrate(double p_dt);
	};
}
