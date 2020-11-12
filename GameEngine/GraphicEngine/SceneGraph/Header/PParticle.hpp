#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <GraphicEngine/SceneGraph/Header/PMeshObject.hpp>

using namespace PhysicEngine;

namespace GraphicEngine::PSceneGraph {
	class PParticle : public PMeshObject
	{
	private:
		Vector3 _color;
		float _size;
	public:
		/*Constructor
		@param p_color the color of the particle
		@param p_size the size of the particle
		*/
		PParticle(Vector3 p_color, float p_size);

		/*@returns the size of the particle*/
		float getSize() const;

		virtual void draw(Vector3 p_position);
	};
}

