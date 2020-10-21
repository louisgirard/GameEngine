#include <PhysicEngine/Collisions/Header/ParticleRod.hpp>
#include <PhysicEngine/Collisions/Header/ParticleContact.hpp>

namespace PhysicEngine
{
	namespace Collisions {
		unsigned ParticleRod::AddContact(ParticleContact *p_contact, unsigned p_limit) const
		{
			float current_length = CurrentLength();
		
			if (current_length == this->_length) return 0;
			//Calculate the normal 
			Vector3 p1 = _particle[0]->getPosition();
			Vector3 p2 = _particle[1]->getPosition();
			Vector3 contactNormal = p2-p1;
			contactNormal.normalize();
			if(current_length > _length)
			{
				float penetration = current_length - _length;
				*p_contact = ParticleContact(_particle[0], _particle[1], 0, contactNormal,penetration );
			}
			else
			{
				float penetration =  _length - current_length;
				*p_contact = ParticleContact(_particle[0], _particle[1], 0, (contactNormal*-1),penetration );
			}
			return 1;
		}
	}
	
}