#include <PhysicEngine/Forces/Header/ParticleDrag.hpp>

namespace PhysicEngine {
	namespace Forces {
		ParticleDrag::ParticleDrag(float p_k1, float p_k2)
		{
			_k1 = p_k1;
			_k2 = p_k2;
		}

		void ParticleDrag::updateForce(CParticle* p_particle, double p_dt)
		{
			// Get normalized velocity of the particle
			Vector3 normalizedVelocity = p_particle->getVelocity();
			float magnitude = normalizedVelocity.magnitude();
			normalizedVelocity.normalize();

			// Calculate force
			Vector3 force = normalizedVelocity * -1 * (_k1 * magnitude + _k2 * magnitude * magnitude);

			p_particle->addForce(force);
		}
	}
}