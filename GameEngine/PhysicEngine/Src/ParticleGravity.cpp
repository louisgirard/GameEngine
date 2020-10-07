#include <PhysicEngine/Header/ParticleGravity.hpp>

namespace PhysicEngine {

	ParticleGravity::ParticleGravity(const Vector3& p_gravity)
	{
		_gravity = p_gravity;
	}

	void ParticleGravity::updateForce(CParticle* p_particle, double p_dt)
	{
		//No update if the mass is infinite
		if (p_particle->getInverseMass() <= 0) {
			return;
		}
		p_particle->addForce(_gravity * p_particle->getMass());
	}
}