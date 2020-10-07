#include <PhysicEngine/Header/CParticle.hpp>

namespace PhysicEngine {
	CParticle::CParticle(float p_mass, Vector3 p_position, Vector3 p_velocity, Vector3 p_acceleration, float p_damping, Vector3 p_color, float p_size)
	{
		_abstraction = std::make_shared<AParticle>(p_mass, p_position, p_velocity, p_acceleration, p_damping);
		_presentation = std::make_shared<PParticle>(p_color, p_size);
	}

	CParticle::CParticle(Types p_type, Vector3 p_position= Vector3::ZERO,Vector3 p_launchDirection = Vector3::FRONT) {
		switch (p_type) {
		case Types::Bullet:
			_abstraction = std::make_shared<AParticle>(1, p_position, p_launchDirection * 80, *new Vector3(0., 0., 0.), 0.999);
			_presentation = std::make_shared<PParticle>(*new Vector3(0., 1., 1.), 10.);
			break;
		case Types::Canonball:
			//Former Velocity *new Vector3(0., 60., -140.)
			_abstraction = std::make_shared<AParticle>(10, p_position, p_launchDirection * 140, *new Vector3(0., 0., 0.), 0.999);
			_presentation = std::make_shared<PParticle>(*new Vector3(0.5, 0.5, 0.5), 40.);
			break;
		case Types::Laser:
			_abstraction = std::make_shared<AParticle>(0., p_position, p_launchDirection * 170, *new Vector3(0., 0., 0.), 0.999);
			_presentation = std::make_shared<PParticle>(*new Vector3(0., 0., 1.), 10.);
			break;
		case Types::Fireball:
			_abstraction = std::make_shared<AParticle>(2, p_position, p_launchDirection * 80, *new Vector3(0., 15., 0.), 0.999);
			_presentation = std::make_shared<PParticle>(*new Vector3(1., 0., 0.), 10.);
			break;
		}
	}

	Vector3 CParticle::getPosition() const
	{
		return _abstraction->getPosition();
	}
	void CParticle::setPosition(const Vector3& p_position)
	{
		_abstraction->setPosition(p_position);
	}
	void CParticle::setPosition(const float p_x, const float p_y, const float p_z)
	{
		_abstraction->setPosition(p_x,p_y,p_z);
	}
	Vector3 CParticle::getVelocity() const
	{
		return _abstraction->getVelocity();
	}
	void CParticle::setVelocity(const Vector3& p_velocity)
	{
		_abstraction->setVelocity(p_velocity);
	}
	void CParticle::setVelocity(const float p_x, const float p_y, const float p_z)
	{
		_abstraction->setVelocity(p_x, p_y, p_z);
	}
	Vector3 CParticle::getAcceleration() const
	{
		return _abstraction->getAcceleration();
	}
	void CParticle::setAcceleration(const Vector3& p_acceleration)
	{
		_abstraction->setAcceleration(p_acceleration);
	}
	void CParticle::setAcceleration(const float p_x, const float p_y, const float p_z)
	{
		_abstraction->setAcceleration(p_x, p_y, p_z);
	}
	float CParticle::getDamping() const
	{
		return _abstraction->getDamping();
	}
	void CParticle::setDamping(const float p_damping)
	{
		_abstraction->setDamping(p_damping);
	}
	float CParticle::getInverseMass() const
	{
		return _abstraction->getInverseMass();
	}
	void CParticle::setInverseMass(const float p_inverseMass)
	{
		_abstraction->setInverseMass(p_inverseMass);
	}
	float CParticle::getMass() const
	{
		return _abstraction->getMass();
	}
	void CParticle::setMass(const float p_mass)
	{
		_abstraction->setMass(p_mass);
	}
	void CParticle::integrate(double p_time)
	{
		_abstraction->integrate(p_time);
	}
	void CParticle::updateFrame()
	{
		_presentation->draw(_abstraction->getPosition());
	}
	void CParticle::updatePhysic(double p_dt)
	{
		_abstraction->integrate(p_dt);
	}

	void CParticle::addForce(const Vector3& p_force)
	{
		_abstraction->addForce(p_force);
	}
}