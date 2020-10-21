#include <PhysicEngine/Collisions/Header/ParticleCable.hpp>

namespace PhysicEngine{
	namespace Collisions {
		float ParticleLink::CurrentLenth() const
		{
			Vector3 p1 = _particule[0]->getPosition();
			Vector3 p2 = _particule[1]->getPosition();
			return (p1 - p2).magnitude();
		}

		unsigned ParticleCable::AddContact(ParticleContact* p_contact, unsigned p_limit) const
		{
			float current_length = CurrentLenth();
			if(current_length < _maxLength) return 0;
			//Calculate the normal 
			Vector3 p1 = _particule[0]->getPosition();
			Vector3 p2 = _particule[1]->getPosition();
			Vector3 contactNormal = p2-p1;
			contactNormal.normalize();
			float penetration = current_length - _maxLength;
			*p_contact = ParticleContact(_particule[0], _particule[1], this->_restitution, contactNormal, penetration);
			return 1;
		}
	}
}