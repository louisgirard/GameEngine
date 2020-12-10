#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <GraphicEngine/SceneGraph/Header/PMeshObject.hpp>

using namespace PhysicEngine;

namespace GraphicEngine::PSceneGraph {
	class PWall : public PMeshObject
	{
	public:
		/*Constructor*/
		PWall(Vector3 p_center, Vector3 p_normal, float p_length, float p_width, const Vector3& p_color, const Vector3& p_specularColor);
	};
}


