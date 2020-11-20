#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <GraphicEngine/SceneGraph/Header/PMeshObject.hpp>

namespace GraphicEngine::PSceneGraph {
	class PIrregularCube : public PMeshObject
	{
	public:

		/*
		* Constructor
		* @param p_vertices : array of vertices must be of size 8 and have a vertices sorted in this order : frontNW, backNW, frontNE, backNE, frontSW, backSW, frontNE, backSE
		* @param p_color : object color
		* @param p_specularColor : object specular color
		*/
		PIrregularCube(const std::vector<PhysicEngine::Vector3>& p_vertices, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor);
	};
}