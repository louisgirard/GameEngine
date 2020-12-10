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

		Matrix3x4 _transform;
	public:
		static const int PLANE_CODE;
		static const int SPHERE_CODE;

		Collider(int p_flag, int p_mask, SceneGraph::CMeshObject* p_owner, int p_geometryCode);

		const int getFlag() const;

		const int getGeometryCode() const;

		const SceneGraph::CMeshObject* getOwner() const;

		void setTransform(const Matrix3x4& p_newTransform);

		virtual bool insideRegion(const GraphicEngine::SceneBase::BoundingBox& p_region) = 0;

		virtual bool resolveCollision(Collider& const p_collider, CollisionData* p_data);
	};
}


