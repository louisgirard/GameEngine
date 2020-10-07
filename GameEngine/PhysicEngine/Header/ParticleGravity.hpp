#pragma once
#include <PhysicEngine/Header/ParticleForceGenerator.hpp>

namespace PhysicEngine {
	class ParticleGravity : public ParticleForceGenerator
	{
	private:
		/*Holds the acceleration due to gravity*/
		Vector3 _gravity;

	public:
		ParticleGravity(const Vector3& p_gravity);
		
		/*Applies gravity to a particle
		* @param p_particle the particle to apply gravity on
		* @param p_dt the elapsed time since the last update
		*/
		virtual void updateForce(CParticle* p_particle, double p_dt);
	};
}
