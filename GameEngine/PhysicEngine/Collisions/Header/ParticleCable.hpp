#pragma once
#include <PhysicEngine/Collisions/Header/ParticleLink.hpp>

namespace PhysicEngine
{
	namespace Collisions {
		class ParticleCable : ParticleLink
		{
		private:
			/*Maximum length of the cable*/
			float _maxLength;
			
		public:
			ParticleCable(CParticle* p_particle1, CParticle* p_particle2, float p_maxLength);
			virtual unsigned AddContact(ParticleContact* p_contact,unsigned p_limit) override;
		};
	}
}