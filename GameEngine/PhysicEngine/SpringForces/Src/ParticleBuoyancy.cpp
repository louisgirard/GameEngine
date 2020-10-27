#include <PhysicEngine/SpringForces/Header/ParticleBuoyancy.hpp>

namespace PhysicEngine 
{
	namespace SpringForces {
		ParticleBuoyancy::ParticleBuoyancy(float p_maxDepth, float p_volume, float p_waterHeight, float p_gravity, float p_density)
		{
			this->_maxDepth = p_maxDepth;
			this->_volume = p_volume;
			this->_waterHeight = p_waterHeight;
			this->_gravity = p_gravity;
			this->_density = p_density;
		}

		void ParticleBuoyancy::updateForce(CParticle* p_particle, double p_dt)
		{
			Vector3 objectPos = p_particle->getPosition();
			if (objectPos._y > _maxDepth + _waterHeight) {
				return;
			}
			float d = (_waterHeight - objectPos._y + _maxDepth) / (2 * _maxDepth);
			Vector3 force(0, 0, 0);

			if (d <= 0)
			{
				return;
			}
			else if (d >= 1)
			{
				force._y = _volume * _density * (-_gravity);
			}
			else
			{
				force._y = d * _volume * _density * (-_gravity);
			}
			p_particle->addForce(force);
		}
	}
}