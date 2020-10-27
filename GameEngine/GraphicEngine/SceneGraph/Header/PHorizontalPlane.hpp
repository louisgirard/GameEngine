#pragma once
#include <PhysicEngine/Header/Vector3.hpp>
#include <GraphicEngine/SceneGraph/Header/PMeshObject.hpp>

using namespace PhysicEngine;

namespace GraphicEngine::PSceneGraph {
	class PHorizontalPlane : public PMeshObject
	{
	public:
		/*Constructor*/
		PHorizontalPlane(Vector3 p_center, float p_length, float p_width,const Vector3& p_color,const Vector3& p_specularColor);
	};
}

