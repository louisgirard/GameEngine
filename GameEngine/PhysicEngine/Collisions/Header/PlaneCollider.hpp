#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <PhysicEngine/Collisions/Header/Collider.hpp>

namespace PhysicEngine::Collisions {
	class PlaneCollider : public Collider
	{
	protected:
		Vector3 _center;
		Vector3 _normal;

	public:
		
		PlaneCollider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Matrix3x4* p_transform, Vector3 p_center, Vector3 p_normal);

		const Vector3 getCenter() const;

		const Vector3 getNormal() const;

		bool insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) override;

		bool resolveCollision(Collider& const p_collider, CollisionData* p_data) override;
	};
}


