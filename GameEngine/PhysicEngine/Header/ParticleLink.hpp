#pragma once
#include <PhysicEngine/Header/ParticleContactGenerator.hpp>

namespace PhysicEngine {
	class ParticleLink : ParticleContactGenerator
	{
	private:
		/*Particules linked by the link (cable or rod) */
		CParticle* _particule[2];

	public:
		/*Calculate the length of the link
		* @return return the length of the link
		*/
		float CurrentLenth() const;

		/*idk*/
		virtual unsigned AddContact(CParticle* p_contact, unsigned p_limit) = 0;
	};
}


