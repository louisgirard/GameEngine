#pragma once

#include <limits>
#include <PhysicEngine/Header/Vector3.h>

namespace PhysicEngine {
	class Particle
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

	public:
		Particle();

		Particle(float p_mass, Vector3 p_position, Vector3 p_velocity, Vector3 p_acceleration, float p_damping);

		/* Returns the position of the particle */
		Vector3 getPosition() const;

		/* Sets the position of the particle */
		void setPosition(const Vector3& p_position);
		void setPosition(const float p_x, const float p_y, const float p_z);

		/* Returns the velocity of the particle */
		Vector3 getVelocity() const;

		/* Sets the velocity of the particle */
		void setVelocity(const Vector3& p_velocity);
		void setVelocity(const float p_x, const float p_y, const float p_z);

		/* Returns the acceleration of the particle */
		Vector3 getAcceleration() const;

		/* Sets the acceleration of the particle */
		void setAcceleration(const Vector3& acceleration);
		void setAcceleration(const float p_x, const float p_y, const float p_z);

		/* Returns the damping */
		float getDamping() const;

		/* Sets the damping */
		void setDamping(const float p_damping);

		/* Returns the inverse of the mass of the particle */
		float getInverseMass() const;

		/* Sets the inverse of the mass of the particle */
		void setInverseMass(const float p_inverseMass);

		/* Returns the mass of the particle */
		float getMass() const;

		/* Sets the mass of the particle */
		void setMass(const float p_mass);

		/* Integrate the particle */
		void integrate(float p_time);
	};
}


