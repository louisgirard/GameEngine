#include <PhysicEngine/Collisions/Header/CollisionData.hpp>

namespace PhysicEngine::Collisions {
	Vector3 CollisionData::getContactPoint()
	{
		return _contactPoint;
	}

	void CollisionData::setContactPoint(Vector3 p_contactPoint)
	{
		_contactPoint = p_contactPoint;
	}

	Vector3 CollisionData::getContactNormal()
	{
		return _contactNormal;
	}

	void CollisionData::setContactNormal(Vector3 p_contactNormal)
	{
		_contactNormal = p_contactNormal;
	}

	float CollisionData::getPenetration()
	{
		return _penetration;
	}

	void CollisionData::setPenetration(float p_penetration)
	{
		_penetration = p_penetration;
	}
}