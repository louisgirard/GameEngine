#pragma once

#include <PhysicEngine/Collisions/Header/Collider.hpp>
#include <PhysicEngine/Collisions/Header/PlaneCollider.hpp>

namespace PhysicEngine::Collisions {
	class SphereCollider : public Collider
	{
	protected:
		Vector3 _center;
		float _radius;
	public:
		
		SphereCollider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Matrix3x4* p_transform, Vector3 p_center, float p_radius);

		bool insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) override;

		bool resolveCollision(Collider& const p_collider, CollisionData* p_data) override;

		bool resolvePlaneCollision(const PlaneCollider& p_boxCollider, CollisionData* p_data);
	};
}

