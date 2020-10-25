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
			/*coefficient of restitution*/
			float _restitution;
			
		public:
			virtual unsigned AddContact(ParticleContact* p_contact,unsigned p_limit) const;
		};
	}
}