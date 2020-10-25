#pragma once
#include <PhysicEngine/Collisions/Header/ParticleContact.hpp>

namespace PhysicEngine {
	namespace Collisions {
		class ParticleContactGenerator
		{
		public:
			/*Generate the contact, if necesssary
			*@param the array to write the contacts in
			*@param p_limit the max number of contacts that can be written
			*/
			virtual unsigned AddContact(ParticleContact* p_contact, unsigned p_limit) = 0;
		private:

		};
	}
}