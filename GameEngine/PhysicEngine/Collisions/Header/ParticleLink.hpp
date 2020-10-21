#pragma once
#include <PhysicEngine/Collisions/Header/ParticleContactGenerator.hpp>

namespace PhysicEngine {
	namespace Collisions {
		class ParticleLink : ParticleContactGenerator
		{
		protected :
			/*Particules linked by the link (cable or rod) */
			CParticle* _particle[2];

			/*Calculate the length of the link
			* @return return the length of the link
			*/
			float CurrentLength() const;
		};
	}
}


