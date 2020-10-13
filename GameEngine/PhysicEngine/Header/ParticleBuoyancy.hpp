#pragma once
#include <PhysicEngine/Header/ParticleForceGenerator.hpp>

namespace PhysicEngine {
	class ParticleBuoyancy : public ParticleForceGenerator
	{
	private:
		/*  */
		float _maxDepth;
		/*  */
		float _volume;
		/*  */
		float _waterheight;
		/*  */
		float _density;
		
	public:
		ParticleBuoyancy(float p_maxDepth, float p_volume, float p_waterheight, float p_density);

		/*Applies buoyancy force to a particle
		* @param p_particle the particle to apply buoyancy on
		* @param p_dt the elapsed time since the last update
		*/
		virtual void updateForce(CParticle* p_particle, double p_dt);
	};
}
