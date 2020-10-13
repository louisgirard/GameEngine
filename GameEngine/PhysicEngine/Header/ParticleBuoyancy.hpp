#pragma once
#include <PhysicEngine/Header/ParticleForceGenerator.hpp>

namespace PhysicEngine {
	class ParticleBuoyancy : public ParticleForceGenerator
	{
	private:
		/* Depth at which the object is completely submerged */
		float _maxDepth;
		/* Volume of the object */
		float _volume;
		/* The height of the water plane */
		float _waterheight;
		/* Density of the liquid */
		float _density;
		
	public:
		ParticleBuoyancy(float p_maxDepth, float p_volume, float p_waterheight, float p_density = 1000.0f);

		/*Applies buoyancy force to a particle
		* @param p_particle the particle to apply buoyancy on
		* @param p_dt the elapsed time since the last update
		*/
		virtual void updateForce(CParticle* p_particle, double p_dt);
	};
}
