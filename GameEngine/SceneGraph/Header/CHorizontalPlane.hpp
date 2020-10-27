#pragma once

#include <SceneGraph/Header/CMeshObject.hpp>
#include <PhysicEngine/Header/AHorizontalPlane.hpp>
#include <GraphicEngine/SceneGraph/Header/PHorizontalPlane.hpp>

namespace SceneGraph {
	class CHorizontalPlane : public CMeshObject
	{
	private:
		std::shared_ptr<AHorizontalPlane> _abstraction;

	public:
		CHorizontalPlane(Vector3 p_center, float p_length, float p_width);

		CHorizontalPlane(Vector3 p_center, float p_length, float p_width,const Vector3& p_color,const Vector3& p_specularColor);

		//returns the height of the plane
		float getHeight();

		/*Returns true if the position is vertically above or under the plane
		* @param p_position the position to check
		*/
		bool isAboveOrUnder(Vector3 p_position);

		/*
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		*/
		virtual void draw(std::string p_shaderName);
	};
}
