#include <GraphicEngine/SceneGraph/Header/PMeshObject.hpp>

namespace GraphicEngine::PSceneGraph {
		PMeshObject::PMeshObject() : _mesh(new Mesh()), _material(nullptr), _shaderName(""), _VAO(nullptr), _forcesTextureCoordinate(false) {}

		PMeshObject::PMeshObject(Mesh* p_mesh, std::shared_ptr<Materials::PhongMaterial> p_material, std::string p_shaderName, bool p_forcesTextures)
			: _mesh(p_mesh), _material(p_material), _shaderName(p_shaderName), _forcesTextureCoordinate(p_forcesTextures) {
			if (p_forcesTextures) _mesh->forceTextureCoordinates();
			_VAO = Servers::ShaderServer::getSingleton()->getMeshVAO(p_shaderName, *_mesh);
		}

		PMeshObject::~PMeshObject() {
			delete _VAO;
			delete _mesh;
		}

		void PMeshObject::draw(std::string p_shaderName) {
			glm::mat4 modelMatrix = glm::mat4(1.0);
			if (p_shaderName == _shaderName) {
				Servers::ShaderServer::getSingleton()->renderMesh(p_shaderName, modelMatrix, (*_VAO), (*_material));
			}
		}

		SceneBase::BoundingBox PMeshObject::computeSceneBoundingBox() {
			return _mesh->boundingBox();
		}

#pragma region GETTERS
		Mesh* PMeshObject::getMesh() const {
			return _mesh;
		}

		std::shared_ptr<Materials::PhongMaterial> PMeshObject::getMaterial() const {
			return _material;
		}

		std::string PMeshObject::getShaderName() const {
			return _shaderName;
		}
#pragma endregion

#pragma region SETTERS
		void PMeshObject::setMesh(Mesh* p_mesh) {
			_mesh = p_mesh;
			if (_forcesTextureCoordinate) _mesh->forceTextureCoordinates();
			if (_shaderName != "") {
				delete _VAO;
				_VAO = Servers::ShaderServer::getSingleton()->getMeshVAO(_shaderName, *_mesh);
			}	
		}

		void PMeshObject::setMaterial(std::shared_ptr<Materials::PhongMaterial> p_material) {
			
			_material = p_material;
		}

		void PMeshObject::registerShader(std::string p_shaderName) {
			_shaderName = p_shaderName;
			if (_mesh != nullptr) {
				delete _VAO;
				_VAO = Servers::ShaderServer::getSingleton()->getMeshVAO(p_shaderName, *_mesh);
			}
		}
#pragma endregion
}