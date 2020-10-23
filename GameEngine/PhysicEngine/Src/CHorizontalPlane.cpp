#include <PhysicEngine/Header/CHorizontalPlane.hpp>

namespace PhysicEngine {
	CHorizontalPlane::CHorizontalPlane(Vector3 p_bottomLeftCorner, float p_length, float p_width)
	{
		_abstraction = std::make_shared<AHorizontalPlane>(p_bottomLeftCorner, p_length, p_width);
	}

	float CHorizontalPlane::getHeight()
	{
		return _abstraction->getHeight();
	}

	bool CHorizontalPlane::isAboveOrUnder(Vector3 p_position)
	{
		return _abstraction->isAboveOrUnder(p_position);
	}
}