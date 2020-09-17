#include <PhysicEngine/Header/Particle.h>


namespace PhysicEngine {
	Particle::Particle()
	{
		setMass(1);
		_position = *new Vector3(0,0,0);
		_velocity = *new Vector3(0, 0, 0);
		_acceleration = *new Vector3(0, -10, 0);
		_damping = 0.999;
	}

	Particle::Particle(float p_mass, Vector3 p_position, Vector3 p_velocity, Vector3 p_acceleration, float p_damping)
	{
		setMass(p_mass);
		_position = p_position;
		_velocity = p_velocity;
		_acceleration = p_acceleration;
		_damping = p_damping;
	}

	Vector3 Particle::getPosition() const
	{
		return _position;
	}

	void Particle::setPosition(const Vector3& p_position)
	{
		_position = p_position;
	}

	void Particle::setPosition(const float p_x, const float p_y, const float p_z)
	{
		_position._x = p_x;
		_position._y = p_y;
		_position._z = p_z;
	}

	Vector3 Particle::getVelocity() const
	{
		return _velocity;
	}

	void Particle::setVelocity(const Vector3& p_velocity)
	{
		_velocity = p_velocity;
	}

	void Particle::setVelocity(const float p_x, const float p_y, const float p_z)
	{
		_velocity._x = p_x;
		_velocity._y = p_y;
		_velocity._z = p_z;
	}

	Vector3 Particle::getAcceleration() const
	{
		return _acceleration;
	}

	void Particle::setAcceleration(const Vector3& p_acceleration)
	{
		_acceleration = p_acceleration;
	}

	void Particle::setAcceleration(const float p_x, const float p_y, const float p_z)
	{
		_acceleration._x = p_x;
		_acceleration._y = p_y;
		_acceleration._z = p_z;
	}

	float Particle::getDamping() const
	{
		return _damping;
	}

	void Particle::setDamping(const float p_damping)
	{
		_damping = p_damping;
	}

	float Particle::getInverseMass() const
	{
		return _inverseMass;
	}

	void Particle::setInverseMass(const float p_inverseMass)
	{
		_inverseMass = p_inverseMass;
	}

	float Particle::getMass() const
	{
		if (_inverseMass == 0) {
			return std::numeric_limits<float>::max();
		}
		else {
			return 1.0f / _inverseMass;
		}
	}

	void Particle::setMass(const float p_mass)
	{
		if (p_mass == 0) {
			return;
		}
		else {
			_inverseMass = 1.0f / p_mass;
		}
	}

	void Particle::integrate(float p_time)
	{
		// Do not integrate if infinite mass
		if (_inverseMass <= 0.0) { return; }

		// Update the position
		_position += _velocity * p_time;

		// Update velocity
		_velocity = _velocity * powf(_damping, p_time) + _acceleration * p_time;
	}

}

