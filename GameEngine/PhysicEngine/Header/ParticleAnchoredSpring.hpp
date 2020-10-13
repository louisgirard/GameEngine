#pragma once
#include <PhysicEngine/Header/ParticleForceGenerator.hpp>
#include <PhysicEngine/Header/CParticle.hpp>

namespace PhysicEngine {
	class ParticleAnchoredSpring : public ParticleForceGenerator
	{
	private:
		/*Anchor*/
		Vector3 _anchor;
		/*Holds the compression distance coefficient */
		float _k;
		/*Length at rest*/
		float _l0;


	public:
		ParticleAnchoredSpring(Vector3 p_anchor, float p_k, float p_l);

		/*Applies spring force to a particle
		* @param p_particle the particle to apply spring on
		* @param p_dt the elapsed time since the last update
		*/
		virtual void updateForce(CParticle* p_particle, double p_dt);
	};
}
