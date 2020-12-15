#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <GraphicEngine/SceneBase/Header/BoundingBox.hpp>
#include <PhysicEngine/Collisions/Header/CollisionData.hpp>

namespace SceneGraph { class CMeshObject; }

namespace PhysicEngine::Collisions {
	class Collider
	{
	protected:
		int _flag;
		int _mask;

		int _geometryCode;

		SceneGraph::CMeshObject* _owner;

		Matrix3x4* _transform;
	public:
		static const int PLANE_CODE;
		static const int SPHERE_CODE;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="p_flag">Collider flag</param>
		/// <param name="p_mask">Collider mask</param>
		/// <param name="p_owner">Collider owner</param>
		/// <param name="p_transform">Collider transform</param>
		/// <param name="p_geometryCode">Collider geometry code, used to upcast</param>
		Collider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, Matrix3x4* p_transform, int p_geometryCode);

		/// <summary>
		/// Get collider's flag
		/// </summary>
		/// <returns>collider's flag</returns>
		const int getFlag() const;

		/// <summary>
		/// Get collider's geometry code
		/// </summary>
		/// <returns>collider's geometry code</returns>
		const int getGeometryCode() const;

		/// <summary>
		/// Get collider's owner
		/// </summary>
		/// <returns>collider's owner</returns>
		const SceneGraph::CMeshObject* getOwner() const;

		/// <summary>
		/// Get collider transform
		/// </summary>
		/// <returns>collider transformr</returns>
		void setTransform(Matrix3x4* p_newTransform);

		/// <summary>
		/// Tell if the collider is inside or partially inside the specified region
		/// </summary>
		/// <param name="p_region">The region to test</param>
		/// <returns>True if the collider is insied else false</returns>
		virtual bool insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) = 0;

		/// <summary>
		/// Resolve collider collision with another collision
		/// </summary>
		/// <param name="p_collider">The other collider</param>
		/// <param name="p_data">Collision data if there was a collision</param>
		/// <returns>true if the they collide</returns>
		virtual bool resolveCollision(Collider& p_collider, CollisionData* p_data);
	};
}


