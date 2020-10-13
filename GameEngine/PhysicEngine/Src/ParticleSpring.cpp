#include <PhysicEngine/Header/ParticleSpring.hpp>

namespace PhysicEngine {

	ParticleSpring::ParticleSpring(CParticle* p_particle, float p_k, float p_l)
	{
		_oppositeParticle = p_particle;
		_k = p_k;
		_l0 = p_l;
	}

	void ParticleSpring::updateForce(CParticle* p_particle, double p_dt)
	{
		//Calculate the vector d
		Vector3 xA = p_particle->getPosition();
		Vector3 xB = _oppositeParticle->getPosition();
		Vector3 d = xA - xB;

		//Get magnitude and normalize d
		float dMagnitude = d.magnitude();
		d.normalize();

		// Calculate force
		Vector3 force = d * -_k * (dMagnitude - _l0);

		p_particle->addForce(force);
	}
}