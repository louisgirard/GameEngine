#pragma once
#include <PhysicEngine/Header/Vector3.hpp>

using namespace PhysicEngine;

namespace GraphicEngine {
	class PHorizontalPlane
	{
	private:
		Vector3 _position;
		Vector3 _color;
		float _length;
		float _width;

	public:
		/*Constructor*/
		PHorizontalPlane(Vector3 p_center, float p_length, float p_width, Vector3 p_color);

		/* Draw the plane */
		void draw();
	};
}

