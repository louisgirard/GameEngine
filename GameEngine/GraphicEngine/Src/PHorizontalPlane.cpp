#include <GraphicEngine/Header/PHorizontalPlane.hpp>
#include <GL/freeglut_std.h>

namespace GraphicEngine {
	PHorizontalPlane::PHorizontalPlane(Vector3 p_center, float p_length, float p_width, Vector3 p_color)
	{
		_position = p_center;
		_length = p_length;
		_width = p_width;
		_color = p_color;
	}

	void PHorizontalPlane::draw()
	{
		glColor3f(_color._x, _color._y, _color._z);
		glTranslatef(_position._x, _position._y, _position._z);
		glScalef(_length, .1f, _width);
		glutSolidCube(1);
	}
}