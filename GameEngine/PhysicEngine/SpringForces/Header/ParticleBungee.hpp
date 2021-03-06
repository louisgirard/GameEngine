#pragma once

#include <PhysicEngine/Forces/Header/ParticleForceGenerator.hpp>
#include <PhysicEngine/Header/CParticle.hpp>

namespace PhysicEngine {
	namespace SpringForces {
		class ParticleBungee : public Forces::ParticleForceGenerator
		{
		private:
			/*Particule at the opposite point of the spring*/
			CParticle* _oppositeParticle;
			/*Holds the compression distance coefficient */
			float _k;
			/*Length at rest*/
			float _l0;

		public:
			ParticleBungee(CParticle* p_particle, float p_k, float p_l);

			/*Applies bungee force to a particle
			* @param p_particle the particle to apply bungee on
			* @param p_dt the elapsed time since the last update
			*/
			virtual void updateForce(CParticle* p_particle, double p_dt);
		};
	}
}
