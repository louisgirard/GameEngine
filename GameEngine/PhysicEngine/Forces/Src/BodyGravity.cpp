#include <PhysicEngine/Forces/Header/BodyGravity.hpp>

namespace PhysicEngine {
	namespace Forces {
		BodyGravity::BodyGravity(const Vector3& p_gravity)
		{
			_gravity = p_gravity;
		}

		void BodyGravity::updateForce(ARigidBody* p_body, double p_dt)
		{
			//No update if the mass is infinite
			if (p_body->getInverseMass() <= 0) {
				return;
			}
			p_body->addForce(_gravity * p_body->getMass());
		}
	}
}