#include <PhysicEngine/SpringForces/Header/ParticleAnchoredSpring.hpp>

namespace PhysicEngine {
	namespace SpringForces {
		ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 p_anchor, float p_k, float p_l)
		{
			_anchor = p_anchor;
			_k = p_k;
			_l0 = p_l;
		}

		void ParticleAnchoredSpring::updateForce(CParticle* p_particle, double p_dt)
		{
			//Calculate the vector d
			Vector3 xA = p_particle->getPosition();
			Vector3 xB = _anchor;
			Vector3 d = xA - xB;

			//Get magnitude and normalize d
			float dMagnitude = d.magnitude();
			d.normalize();

			// Calculate force
			Vector3 force = d * -_k * (dMagnitude - _l0);

			p_particle->addForce(force);
		}
	}
}