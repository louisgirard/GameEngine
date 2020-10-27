#pragma once

#include <PhysicEngine/Forces/Header/ParticleForceGenerator.hpp>

namespace PhysicEngine {
	namespace SpringForces {
		class ParticleBuoyancy : public Forces::ParticleForceGenerator
		{
		private:
			/* Depth at which the object is completely submerged */
			float _maxDepth;
			/* Volume of the object */
			float _volume;
			/* The height of the water plane */
			float _waterHeight;
			/*Gravity acceleration*/
			float _gravity;
			/* Density of the liquid */
			float _density;

		public:
			ParticleBuoyancy(float p_maxDepth, float p_volume, float p_waterHeight, float p_gravity, float p_density = 1000.0f);

			/*Applies buoyancy force to a particle
			* @param p_particle the particle to apply buoyancy on
			* @param p_dt the elapsed time since the last update
			*/
			virtual void updateForce(CParticle* p_particle, double p_dt);
		};
	}
}
