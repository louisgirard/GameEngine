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
		
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="p_flag">Plane flag</param>
		/// <param name="p_mask">Plane mask</param>
		/// <param name="p_owner">Plane owner</param>
		/// <param name="p_transform">Plane transform</param>
		/// <param name="p_center">Plane center</param>
		/// <param name="p_normal">Plane normal</param>
		PlaneCollider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Matrix3x4* p_transform, Vector3 p_center, Vector3 p_normal);

		/// <summary>
		/// Gets plane center
		/// </summary>
		/// <returns>plane's center</returns>
		const Vector3 getCenter() const;
		
		/// <summary>
		/// Gets plane's normal
		/// </summary>
		/// <returns>plane's normal</returns>
		const Vector3 getNormal() const;

		bool insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) override;

		bool resolveCollision(Collider& p_collider, CollisionData* p_data) override;
	};
}


