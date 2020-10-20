#pragma once
#include <PhysicEngine/Header/ParticleLink.hpp>

namespace PhysicEngine
{
	class ParticleCable : ParticleLink
	{
	private:
		float _maxLength;
		float _restitution;
		
	public:
		virtual unsigned AddContact(ParticleContact* p_contact,unsigned p_limit) const;
	};
}