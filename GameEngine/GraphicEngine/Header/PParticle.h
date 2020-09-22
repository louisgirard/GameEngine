#pragma once
#include <PhysicEngine\Header\Vector3.h>

namespace PhysicEngine {
	class PParticle
	{
	private:
		Vector3 _color;
		float _size;
	public:
		PParticle(Vector3 p_color, float p_size);

		void setColor(const Vector3& p_color);
		void setSize(float p_size);
		void draw(Vector3 p_position);
	};
}

