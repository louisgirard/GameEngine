#include <PhysicEngine/Collisions/Header/ParticleCable.hpp>

namespace PhysicEngine{
	namespace Collisions {
		unsigned ParticleCable::AddContact(ParticleContact* p_contact, unsigned p_limit) const
		{
			float current_length = CurrentLength();
			if(current_length < _maxLength) return 0;
			//Calculate the normal 
			Vector3 p1 = _particle[0]->getPosition();
			Vector3 p2 = _particle[1]->getPosition();
			Vector3 contactNormal = p2-p1;
			contactNormal.normalize();
			float penetration = current_length - _maxLength;
			*p_contact = ParticleContact(_particle[0], _particle[1], this->_restitution, contactNormal, penetration);
			return 1;
		}
	}
}