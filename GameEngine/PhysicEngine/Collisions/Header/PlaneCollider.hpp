#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <PhysicEngine/Collisions/Header/SphereCollider.hpp>

namespace PhysicEngine::Collisions {
	class PlaneCollider : public Collider
	{
	protected:
		Vector3 _center;
		Vector3 _normal;

	public:
		
		PlaneCollider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Vector3 p_center, Vector3 p_normal);

		Vector3 getCenter();

		Vector3 getNormal();

		bool insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) override;

		bool resolveCollision(Collider& const p_collider, CollisionData* p_data) override;
	};
}


