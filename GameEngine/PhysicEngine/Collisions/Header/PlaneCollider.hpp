#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <PhysicEngine/Collisions/Header/SphereCollider.hpp>
#include <PhysicEngine/Collisions/Header/BoxCollider.hpp>

namespace PhysicEngine::Collisions {
	class PlaneCollider
	{
	protected:
		Vector3 _center;
		Vector3 _normal;

	public:

		PlaneCollider(Vector3 p_center, Vector3 p_normal);

		bool insideRegion(GraphicEngine::SceneBase::BoundingBox p_region);

		bool resolveBoxCollision(BoxCollider p_boxCollider, CollisionData p_data);
	};
}


