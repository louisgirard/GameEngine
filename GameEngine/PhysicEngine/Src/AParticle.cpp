#include <PhysicEngine/Header/AParticle.hpp>

namespace PhysicEngine {

	AParticle::AParticle(float p_mass, Vector3 p_position, Vector3 p_velocity, Vector3 p_acceleration, float p_damping) {
		setMass(p_mass);
		_position = p_position;
		_velocity = p_velocity;
		_acceleration = p_acceleration;
		_damping = p_damping;
		_forceAccum = Vector3::ZERO;
	}

	Vector3 AParticle::getPosition() const
	{
		return _position;
	}

	void AParticle::setPosition(const Vector3& p_position)
	{
		_position = p_position;
	}

	void AParticle::setPosition(const float p_x, const float p_y, const float p_z)
	{
		_position._x = p_x;
		_position._y = p_y;
		_position._z = p_z;
	}

	Vector3 AParticle::getVelocity() const
	{
		return _velocity;
	}

	void AParticle::setVelocity(const Vector3& p_velocity)
	{
		_velocity = p_velocity;
	}

	void AParticle::setVelocity(const float p_x, const float p_y, const float p_z)
	{
		_velocity._x = p_x;
		_velocity._y = p_y;
		_velocity._z = p_z;
	}

	Vector3 AParticle::getAcceleration() const
	{
		return _acceleration;
	}

	void AParticle::setAcceleration(const Vector3& p_acceleration)
	{
		_acceleration = p_acceleration;
	}

	void AParticle::setAcceleration(const float p_x, const float p_y, const float p_z)
	{
		_acceleration._x = p_x;
		_acceleration._y = p_y;
		_acceleration._z = p_z;
	}

	float AParticle::getDamping() const
	{
		return _damping;
	}

	void AParticle::setDamping(const float p_damping)
	{
		_damping = p_damping;
	}

	float AParticle::getInverseMass() const
	{
		return _inverseMass;
	}

	void AParticle::setInverseMass(const float p_inverseMass)
	{
		_inverseMass = p_inverseMass;
	}

	float AParticle::getMass() const
	{
		if (_inverseMass == 0) {
			return std::numeric_limits<float>::max();
		}
		else {
			return 1.0f / _inverseMass;
		}
	}

	void AParticle::setMass(const float p_mass)
	{
		if (p_mass == 0) {
			_inverseMass = INFINITY;
		}
		else {
			_inverseMass = 1.0f / p_mass;
		}
	}

	void AParticle::integrate(double p_time)
	{
		// Do not integrate if infinite mass
		if (_inverseMass <= 0.0) { return; }

		Vector3 resultingAcceleration = Vector3::ZERO;

		//no force applied on an object without mass because the inverse mass is infinite
		if (getMass() != 0) {
			//Compute the acceleration due to forces
			resultingAcceleration = _acceleration + _forceAccum * _inverseMass;
		}

		// Update the position
		_position += _velocity * (float)p_time;

		// Update velocity
		_velocity = _velocity * powf(_damping, (float)p_time) + resultingAcceleration * (float)p_time;

		//Clear the forces
		clearAccumulator();
	}

	void AParticle::clearAccumulator() {
		_forceAccum = Vector3::ZERO;
	}

	void AParticle::addForce(const Vector3& p_force) {
		_forceAccum += p_force;
	}
}