#pragma once
#include <PhysicEngine\Header\MathEnabler.hpp>

namespace PhysicEngine::Collisions {
	class CollisionData
	{
	private:
		Vector3 _contactPoint;
		Vector3 _contactNormal;
		float _penetration;

	public:
		Vector3 getContactPoint();
		void setContactPoint(Vector3 p_contactPoint);

		Vector3 getContactNormal();
		void setContactNormal(Vector3 p_contactNormal);

		float getPenetration();
		void setPenetration(float p_penetration);
	};
}


