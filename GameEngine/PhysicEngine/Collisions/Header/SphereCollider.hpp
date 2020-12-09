#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <GraphicEngine/SceneBase/Header/BoundingBox.hpp>

namespace PhysicEngine::Collisions {
	class SphereCollider
	{
	protected:
		Vector3 _center;
		float _radius;

		Matrix3x4 _transform;
	public:
		SphereCollider(GraphicEngine::SceneBase::BoundingBox p_boundingBox);

		void setTransform(Matrix3x4 p_newTransform);

		bool insideRegion(GraphicEngine::SceneBase::BoundingBox p_region);
	};
}

