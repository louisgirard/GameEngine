#pragma once
#include <PhysicEngine/Header/CParticle.hpp>

namespace PhysicEngine {
	namespace Forces {
		class ParticleForceGenerator {
		public:
			virtual void updateForce(CParticle* p_particle, double p_dt) = 0;
		};

	}
}