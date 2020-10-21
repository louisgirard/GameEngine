#pragma once
#include <PhysicEngine/Collisions/Header/ParticleContactGenerator.hpp>

namespace PhysicEngine {
	namespace Collisions {
		class ParticleLink : ParticleContactGenerator
		{
		protected :
			/*Particules linked by the link (cable or rod) */
			CParticle* _particule[2];

			/*Calculate the length of the link
			* @return return the length of the link
			*/
			float CurrentLenth() const;

		public:
			/*Generate the contact, if necesssary*/
			virtual unsigned AddContact(CParticle* p_contact, unsigned p_limit) = 0;
		};
	}
}


