#include <GraphicEngine/Header/PParticle.hpp>
#include <GL/freeglut_std.h>

namespace PhysicEngine {
	PParticle::PParticle(Vector3 p_color, float p_size)
	{
		_color = p_color;
		_size = p_size;
	}
	void PParticle::setColor(const Vector3& p_color)
	{
		_color = p_color;
	}
	void PParticle::setSize(float p_size)
	{
		_size = p_size;
	}
	void PParticle::draw(Vector3 p_position)
	{
		glColor3f(_color._x, _color._y, _color._z);
		//glLoadIdentity();
		glTranslatef(p_position._x, p_position._y, p_position._z);
		glutWireSphere(_size, 20, 16);
	}
}