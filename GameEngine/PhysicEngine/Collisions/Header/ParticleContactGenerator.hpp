#pragma once
#include <PhysicEngine/Collisions/Header/ParticleContact.hpp>

namespace PhysicEngine {
	namespace Collisions {
		class ParticleContactGenerator
		{
		public:
			/*Generate the contact, if necesssary*/
			virtual unsigned AddContact(ParticleContact* p_contact, unsigned p_limit) = 0;
		private:

		};
	}
}