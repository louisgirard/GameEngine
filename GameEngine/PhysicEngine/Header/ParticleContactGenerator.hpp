#pragma once
#include <PhysicEngine/Header/CParticle.hpp>
namespace PhysicEngine {
	class ParticleContactGenerator
	{
	public:
		/*...idk*/
		virtual unsigned AddContact(CParticle *p_contact, unsigned p_limit) = 0;
	private:

	};
}