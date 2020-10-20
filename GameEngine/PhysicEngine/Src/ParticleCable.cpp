#include <PhysicEngine/Header/ParticleCable.hpp>

namespace PhysicEngine{
	float ParticleLink::CurrentLenth() const
	{
		Vector3 p1 = _particule[0]->getPosition;
		Vector3 p2 = _particule[1]->getPosition;
		return (p1 - p2).magnitude();
	}

	unsigned ParticleCable::AddContact(ParticleContact* p_contact, unsigned p_limit) const
	{

	}
}