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
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="p_flag">Sphere flag</param>
		/// <param name="p_mask">Sphere mask</param>
		/// <param name="p_owner">Sphere owner</param>
		/// <param name="p_transform">Sphere transform</param>
		/// <param name="p_center">Sphere center</param>
		/// <param name="p_radius">Sphere radius</param>
		SphereCollider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Matrix3x4* p_transform, Vector3 p_center, float p_radius);

		bool insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) override;

		bool resolveCollision(Collider&  p_collider, CollisionData* p_data) override;

		/// <summary>
		/// Resolve collision with a plane
		/// </summary>
		/// <param name="p_planeCollider">The plane collider</param>
		/// <param name="p_data">Collision data if there was a collision</param>
		/// <returns>true if the they collide</returns>
		bool resolvePlaneCollision(const PlaneCollider& p_planeCollider, CollisionData* p_data);
	};
}

