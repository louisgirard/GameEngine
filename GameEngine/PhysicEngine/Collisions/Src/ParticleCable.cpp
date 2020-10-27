#include <PhysicEngine/Collisions/Header/ParticleCable.hpp>

namespace PhysicEngine{
	namespace Collisions {
		ParticleCable::ParticleCable(CParticle* p_particle1, CParticle* p_particle2, float p_maxLength)
		{
			_particle[0] = p_particle1;
			_particle[1] = p_particle2;
			_maxLength = p_maxLength;
		}
		unsigned ParticleCable::AddContact(ParticleContact* p_contact, unsigned p_limit)
		{
			float current_length = CurrentLength();
			if(current_length < _maxLength) return 0;
			//Calculate the normal 
			Vector3 p1 = _particle[0]->getPosition();
			Vector3 p2 = _particle[1]->getPosition();
			Vector3 contactNormal = p2-p1;
			contactNormal.normalize();
			float penetration = current_length - _maxLength;
			*p_contact = ParticleContact(_particle[0], _particle[1], 1, contactNormal, penetration);
			return 1;
		}
	}
}