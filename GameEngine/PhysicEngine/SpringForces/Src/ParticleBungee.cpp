#include <PhysicEngine/SpringForces/Header/ParticleBungee.hpp>

namespace PhysicEngine {
	namespace SpringForces {
		ParticleBungee::ParticleBungee(CParticle* p_particle, float p_k, float p_l)
		{
			_oppositeParticle = p_particle;
			_k = p_k;
			_l0 = p_l;
		}

		void ParticleBungee::updateForce(CParticle* p_particle, double p_dt)
		{
			//Calculate the vector d
			Vector3 xA = p_particle->getPosition();
			Vector3 xB = _oppositeParticle->getPosition();
			Vector3 d = xA - xB;

			//Get magnitude and normalize d
			float dMagnitude = d.magnitude();
			if (dMagnitude <= _l0)
			{
				return;
			}
			d.normalize();

			// Calculate force
			Vector3 force = d * -_k * (dMagnitude - _l0);

			p_particle->addForce(force);
		}
	}
}