#pragma once
#include <PhysicEngine/Header/Vector3.hpp>
#include <limits>
#include <iostream>

namespace PhysicEngine {
	class AParticle
	{
	private:
		/* Holds the position of the particle */
		Vector3 _position;

		/* Holds the velocity of the particle */
		Vector3 _velocity;

		/* Holds the acceleration of the particle */
		Vector3 _acceleration;

		/* Holds the damping applied to linear motion */
		float _damping;

		/* Holds the inverse of the mass of the particle */
		float _inverseMass;

		/*Holds the accumulated force to be applied next step*/
		Vector3 _forceAccum;

	public:
		/*Constructor*/
		AParticle(float p_mass, Vector3 p_position, Vector3 p_velocity, Vector3 p_acceleration, float p_damping);

		/*@return the position of the particle */
		Vector3 getPosition() const;

		/* Sets the position of the particle
		@param p_position the position to which the particle must be set
		*/
		void setPosition(const Vector3& p_position);

		/* Sets the position of the particle
		@param p_x the new x of the particle
		@param p_y the new y of the particle
		@param p_z the new z of the particle
		*/
		void setPosition(const float p_x, const float p_y, const float p_z);

		/*@return the velocity of the particle */
		Vector3 getVelocity() const;

		/* Sets the velocity of the particle
		@param p_velocity the velocity at which the particle must be set
		*/
		void setVelocity(const Vector3& p_velocity);

		/* Sets the velocity of the particle
		@param p_x the new x of the velocity
		@param p_y the new y of the velocity
		@param p_z the new z of the velocity
		*/
		void setVelocity(const float p_x, const float p_y, const float p_z);

		/*@return the acceleration of the particle */
		Vector3 getAcceleration() const;

		/* Sets the acceleration of the particle
		@param p_acceleration the velocity at which the particle must be set
		*/
		void setAcceleration(const Vector3& p_acceleration);

		/* Sets the acceleration of the particle
		@param p_x the new x of the acceleration
		@param p_y the new y of the acceleration
		@param p_z the new z of the acceleration
		*/
		void setAcceleration(const float p_x, const float p_y, const float p_z);

		/*@return the damping */
		float getDamping() const;

		/* Sets the damping
		@param p_damping the new damping
		*/
		void setDamping(const float p_damping);

		/*@return the inverse of the mass of the particle */
		float getInverseMass() const;

		/* Sets the inverse of the mass of the particle
		@param p_inverseMass the new inverse mass of the particle
		*/
		void setInverseMass(const float p_inverseMass);

		/*@return the mass of the particle */
		float getMass() const;

		/* Sets the mass of the particle
		@param p_mass the new mass of the particle
		*/
		void setMass(const float p_mass);

		/* Computes the new velocity and position of the particle
		@param p_time the ellapsed time since the last update
		*/
		void integrate(double p_time);

		/*Resets the force accumulator to zero*/
		void clearAccumulator();

		/*Adds a force to the particle for the next iteration only*/
		void addForce(const Vector3 &p_force);
	};
}
