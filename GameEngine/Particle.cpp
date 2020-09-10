#include "Particle.h"

Vector3 Particle::getPosition() const
{
	return position;
}

void Particle::setPosition(const Vector3& position)
{
	this->position = position;
}

void Particle::setPosition(const float x, const float y, const float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

Vector3 Particle::getVelocity() const
{
	return velocity;
}

void Particle::setVelocity(const Vector3& velocity)
{
	this->velocity = velocity;
}

void Particle::setVelocity(const float x, const float y, const float z)
{
	velocity.x = x;
	velocity.y = y;
	velocity.z = z;
}

Vector3 Particle::getAcceleration() const
{
	return acceleration;
}

void Particle::setAcceleration(const Vector3& acceleration)
{
	this->acceleration = acceleration;
}

void Particle::setAcceleration(const float x, const float y, const float z)
{
	acceleration.x = x;
	acceleration.y = y;
	acceleration.z = z;
}

float Particle::getDamping() const
{
	return damping;
}

void Particle::setDamping(const float damping)
{
	this->damping = damping;
}

float Particle::getInverseMass() const
{
	return inverseMass;
}

void Particle::setInverseMass(const float inverseMass)
{
	this->inverseMass = inverseMass;
}

float Particle::getMass() const
{
	if (inverseMass == 0) {
		return std::numeric_limits<float>::max();
	}
	else {
		return 1.0f / inverseMass;
	}
}

void Particle::setMass(const float mass)
{
	if (mass == 0) {
		return;
	}
	else {
		inverseMass = 1.0f / mass;
	}
}

void Particle::integrate(float time)
{
	// Do not integrate if infinite mass
	if (inverseMass <= 0.0) { return; }

	// Update the position
	position += velocity * time;

	// Update velocity
	velocity = velocity * powf(damping, time) + acceleration * time;
}
