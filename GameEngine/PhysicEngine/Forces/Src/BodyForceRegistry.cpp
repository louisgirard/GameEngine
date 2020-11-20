#include <PhysicEngine/Forces/Header/BodyForceRegistry.hpp>

namespace PhysicEngine {
	namespace Forces {
		void BodyForceRegistry::add(ARigidBody* p_body, BodyForceGenerator* p_forceGenerator)
		{
			for (auto r = _registrations.begin(); r != _registrations.end(); ++r)
			{
				if (r->_body == p_body && r->_forceGenerator == p_forceGenerator) {
					return;
				}
			}
			_registrations.push_back({ p_body, p_forceGenerator });
		}

		void BodyForceRegistry::remove(ARigidBody* p_body, BodyForceGenerator* p_forceGenerator)
		{
			for (auto r = _registrations.begin(); r != _registrations.end(); ++r)
			{
				if (r->_body == p_body && r->_forceGenerator == p_forceGenerator) {
					_registrations.erase(r);
					return;
				}
			}
		}

		void BodyForceRegistry::clear()
		{
			_registrations.clear();
		}

		void BodyForceRegistry::updatePhysic(double p_dt)
		{
			for (auto r = _registrations.begin(); r != _registrations.end(); ++r) {
				r->_forceGenerator->updateForce(r->_body, p_dt);
			}
		}
	}
}
