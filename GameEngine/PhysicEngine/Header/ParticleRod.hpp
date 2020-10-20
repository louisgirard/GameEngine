#pragma once
#include <PhysicEngine/Header/ParticleLink.hpp>

namespace PhysicEngine
{
	class ParticleRod : ParticleLink
	{
	private:
		float _length;

	public:
		virtual unsigned AddContact(ParticleContact* p_contact, unsigned p_limit) const;
	};
}