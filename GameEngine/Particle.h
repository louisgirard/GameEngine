#pragma once
#include "Vector3.h"
#include <limits>
class Particle
{
private:
	/* Holds the position of the particle */
	Vector3 position;

	/* Holds the velocity of the particle */
	Vector3 velocity;

	/* Holds the acceleration of the particle */
	Vector3 acceleration;

	/* Holds the damping applied to linear motion */
	float damping;

	/* Holds the inverse of the mass of the particle */
	float inverseMass;

public:
	/* Returns the position of the particle */
	Vector3 getPosition() const;

	/* Sets the position of the particle */
	void setPosition(const Vector3& position);
	void setPosition(const float x, const float y, const float z);

	/* Returns the velocity of the particle */
	Vector3 getVelocity() const;

	/* Sets the velocity of the particle */
	void setVelocity(const Vector3& velocity);
	void setVelocity(const float x, const float y, const float z);

	/* Returns the acceleration of the particle */
	Vector3 getAcceleration() const;

	/* Sets the acceleration of the particle */
	void setAcceleration(const Vector3& acceleration);
	void setAcceleration(const float x, const float y, const float z);

	/* Returns the damping */
	float getDamping() const;

	/* Sets the damping */
	void setDamping(const float damping);

	/* Returns the inverse of the mass of the particle */
	float getInverseMass() const;

	/* Sets the inverse of the mass of the particle */
	void setInverseMass(const float inverseMass);

	/* Returns the mass of the particle */
	float getMass() const;

	/* Sets the mass of the particle */
	void setMass(const float mass);

	/* Integrate the particle */
	void integrate(float time);
};

