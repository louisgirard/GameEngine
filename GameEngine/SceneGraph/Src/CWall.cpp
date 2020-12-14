#include <SceneGraph/Header/CWall.hpp>
#include <GraphicEngine/SceneGraph/Header/PWall.hpp>

namespace SceneGraph {

	const int CWall::FLAG = 2;

	CWall::CWall(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_normal, float p_length, float p_width) :
		CWall(p_center, p_normal, p_length, p_width, PhysicEngine::Vector3::ONE, PhysicEngine::Vector3::ZERO) {}

	CWall::CWall(const PhysicEngine::Vector3& p_center, const PhysicEngine::Vector3& p_normal, float p_length, float p_width, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor) {
		_presentation = std::make_shared<GraphicEngine::PSceneGraph::PWall>(p_center, p_normal, p_length, p_width, p_color, p_specularColor);
		_colliders.push_back(new PhysicEngine::Collisions::PlaneCollider(FLAG, 1, this, nullptr, p_center, p_normal ));
	}

	void CWall::draw(std::string p_shaderName)
	{
		_presentation->draw(p_shaderName);
	}
}