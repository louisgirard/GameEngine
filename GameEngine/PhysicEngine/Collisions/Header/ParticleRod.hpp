#pragma once
#include <PhysicEngine/Collisions/Header/ParticleLink.hpp>

namespace PhysicEngine
{
	namespace Collisions 
	{
		class ParticleRod : ParticleLink
		{
		private:
			/*Length of the rod*/
			float _length;

		public:
			virtual unsigned AddContact(ParticleContact* p_contact, unsigned p_limit) const;
		};
	}
}