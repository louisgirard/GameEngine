#pragma once
#include <PhysicEngine/Header/ParticleForceGenerator.hpp>

namespace PhysicEngine {
	class ParticleDrag : public ParticleForceGenerator
	{
	private:
		/* Holds the velocity drag coefficient */
		float _k1;

		/* Holds the velocity squared drag coefficient */
		float _k2;

	public:
		ParticleDrag(float p_k1, float p_k2);
		
		/*Applies drag force to a particle
		* @param p_particle the particle to apply drag on
		* @param p_dt the elapsed time since the last update
		*/
		virtual void updateForce(CParticle* p_particle, double p_dt);
	};
}
