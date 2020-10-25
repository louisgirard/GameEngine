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
			float CurrentLength() const
			{
				Vector3 p1 = _particle[0]->getPosition();
				Vector3 p2 = _particle[1]->getPosition();
				return (p1 - p2).magnitude();
			}

		};
	}
}


