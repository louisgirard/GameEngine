#pragma once
#include <PhysicEngine/Header/ARigidBody.hpp>

namespace PhysicEngine {
	namespace Forces {
		class BodyForceGenerator {
		public:
			virtual void updateForce(ARigidBody* p_rigidBody, double p_dt) = 0;
		};

	}
}