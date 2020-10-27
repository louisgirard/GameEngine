#include <SceneGraph/Header/CHorizontalPlane.hpp>

namespace SceneGraph {
	CHorizontalPlane::CHorizontalPlane(Vector3 p_center, float p_length, float p_width) :CHorizontalPlane(p_center, p_length, p_width, Vector3(1.f,1.f, 1.f), Vector3(0.f,0.f,0.f)){}

	CHorizontalPlane::CHorizontalPlane(Vector3 p_center, float p_length, float p_width,const Vector3& p_color,const Vector3& p_specularColor) {
		_abstraction = std::make_shared<AHorizontalPlane>(p_center, p_length, p_width);
		_presentation = std::make_shared<GraphicEngine::PSceneGraph::PHorizontalPlane>(p_center, p_length, p_width, p_color, p_specularColor);
	}

	float CHorizontalPlane::getHeight()
	{
		return _abstraction->getHeight();
	}

	bool CHorizontalPlane::isAboveOrUnder(Vector3 p_position)
	{
		return _abstraction->isAboveOrUnder(p_position);
	}
	
	void CHorizontalPlane::draw(std::string p_shaderName)
	{
		_presentation->draw(p_shaderName);
	}
}