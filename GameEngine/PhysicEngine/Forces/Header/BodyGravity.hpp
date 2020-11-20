#pragma once

#include <PhysicEngine/Forces/Header/BodyForceGenerator.hpp>

namespace PhysicEngine {
	namespace Forces {
		class BodyGravity : public BodyForceGenerator
		{
		private:
			/*Holds the acceleration due to gravity*/
			Vector3 _gravity;

		public:
			BodyGravity(const Vector3& p_gravity);

			/*Applies gravity to a particle
			* @param p_particle the particle to apply gravity on
			* @param p_dt the elapsed time since the last update
			*/
			virtual void updateForce(ARigidBody* p_body, double p_dt);
		};
	}
}
