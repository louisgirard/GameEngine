#include <PhysicEngine/Header/CHorizontalPlane.hpp>

namespace PhysicEngine {
	CHorizontalPlane::CHorizontalPlane(Vector3 p_center, float p_length, float p_width)
	{
		_abstraction = std::make_shared<AHorizontalPlane>(p_center, p_length, p_width);
		_presentation = std::make_shared<GraphicEngine::PHorizontalPlane>(p_center, p_length, p_width, Vector3(1,1,1));
	}

	float CHorizontalPlane::getHeight()
	{
		return _abstraction->getHeight();
	}

	bool CHorizontalPlane::isAboveOrUnder(Vector3 p_position)
	{
		return _abstraction->isAboveOrUnder(p_position);
	}
	
	void CHorizontalPlane::updateFrame()
	{
		_presentation->draw();
	}
}