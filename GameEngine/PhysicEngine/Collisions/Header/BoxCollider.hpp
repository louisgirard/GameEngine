#pragma once

#include <vector>

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <GraphicEngine/SceneBase/Header/BoundingBox.hpp>
#include <PhysicEngine/Collisions/Header/CollisionData.hpp>

namespace PhysicEngine::Collisions {
	class BoxCollider
	{
	protected:
		std::vector<Vector3> _vertices;
		Matrix3x4 _transform;
	public:

		BoxCollider(GraphicEngine::SceneBase::BoundingBox p_boundingBox);

		void setTransform(Matrix3x4 p_newTransform);

		bool resolvePlanCollision(Vector3 p_position, Vector3 p_normal, CollisionData p_data);
	};
}


