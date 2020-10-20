#include <PhysicEngine/Forces/Header/ParticleForceRegistry.hpp>

namespace PhysicEngine {
	namespace Forces {
		void ParticleForceRegistry::add(CParticle* p_particle, ParticleForceGenerator* p_forceGenerator)
		{
			for (auto r = _registrations.begin(); r != _registrations.end(); ++r)
			{
				if (r->_particle == p_particle && r->_forceGenerator == p_forceGenerator) {
					return;
				}
			}
			_registrations.push_back({ p_particle, p_forceGenerator });
		}

		void ParticleForceRegistry::remove(CParticle* p_particle, ParticleForceGenerator* p_forceGenerator)
		{
			for (auto r = _registrations.begin(); r != _registrations.end(); ++r)
			{
				if (r->_particle == p_particle && r->_forceGenerator == p_forceGenerator) {
					_registrations.erase(r);
					return;
				}
			}
		}

		void ParticleForceRegistry::clear()
		{
			_registrations.clear();
		}

		void ParticleForceRegistry::updatePhysic(double p_dt)
		{
			for (auto r = _registrations.begin(); r != _registrations.end(); ++r) {
				r->_forceGenerator->updateForce(r->_particle, p_dt);
			}
		}
	}
}
