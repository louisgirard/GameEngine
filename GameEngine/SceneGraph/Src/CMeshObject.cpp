#include <SceneGraph/Header/CMeshObject.hpp>

namespace SceneGraph {

	CMeshObject::CMeshObject(GraphicEngine::PSceneGraph::Mesh* p_mesh, std::shared_ptr<GraphicEngine::Materials::PhongMaterial> p_material, std::string p_shaderName, bool p_forcesTexture) : EmptyNode(), _presentation(new GraphicEngine::PSceneGraph::PMeshObject(p_mesh, p_material, p_shaderName, p_forcesTexture)) {}

	void CMeshObject::draw(std::string p_shaderName) {
		_presentation->draw(p_shaderName);
		EmptyNode::draw(p_shaderName);
	}

	GraphicEngine::SceneBase::BoundingBox CMeshObject::computeSceneBoundingBox() {
		return _presentation->computeSceneBoundingBox() + EmptyNode::computeSceneBoundingBox();
	}

#pragma region GETTERS

	GraphicEngine::PSceneGraph::Mesh* CMeshObject::getMesh() const {
		return _presentation->getMesh();
	}

	std::shared_ptr<GraphicEngine::Materials::PhongMaterial> CMeshObject::getMaterial() const {
		return _presentation->getMaterial();
	}
#pragma endregion

#pragma region SETTERS
	void CMeshObject::setMesh(GraphicEngine::PSceneGraph::Mesh* p_mesh) {
		_presentation->setMesh(p_mesh);
	}

	void CMeshObject::setMaterial(std::shared_ptr<GraphicEngine::Materials::PhongMaterial> p_material) {
		_presentation->setMaterial(p_material);
	}

	void CMeshObject::registerShader(std::string p_shaderName) {
		_presentation->registerShader(p_shaderName);
	}
#pragma endregion
}