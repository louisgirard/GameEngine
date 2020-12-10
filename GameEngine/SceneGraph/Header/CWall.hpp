#pragma once

#include <SceneGraph/Header/CMeshObject.hpp>
#include <PhysicEngine/Collisions/Header/PlaneCollider.hpp>
#include <GraphicEngine/SceneGraph/Header/PHorizontalPlane.hpp>

namespace SceneGraph {
	class CWall : public CMeshObject
	{
	public:

		static const int FLAG;

		CWall(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_normal, float p_length, float p_width);

		CWall(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_normal, float p_length, float p_width, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor);

		/*
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		*/
		virtual void draw(std::string p_shaderName);
	};
}


