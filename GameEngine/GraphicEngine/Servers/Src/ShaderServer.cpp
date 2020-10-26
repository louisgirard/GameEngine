#include <GraphicEngine/Servers/Header/ShaderServer.hpp>

namespace GraphicEngine::Servers {
		const std::string ShaderServer::PHONG = "PhongDirectional";

		ShaderServer::ShaderServer():_defaultMeshShader(PHONG),_skyboxShader(nullptr) {}

		void ShaderServer::init() {
			if (_skyboxShader == nullptr)_skyboxShader = new Shaders::SkyboxShader();
			loadAndRegisterShader(ShaderProgramType::MESH, PHONG, defaultPhongVertex().filename().string(), defaultPhongFragment().filename().string());
		}

		void ShaderServer::clear() {
			// Release memory from ShaderProgram 
			// Prepare to reset the server
			delete _skyboxShader;
			_skyboxShader = nullptr;
			for (std::map<std::string, Shaders::ShaderProgram*>::iterator it = _customShaders.begin();
				it != _customShaders.end(); ++it) {
				delete (*it).second;
			}
			for (std::map<std::string, Shaders::MeshShader*>::iterator it = _meshShaders.begin();
				it != _meshShaders.end(); ++it) {
				delete (*it).second;
			}
			for (std::map<std::string, Shaders::VFXShader*>::iterator it = _vfxShaders.begin();
				it != _vfxShaders.end(); ++it) {
				delete (*it).second;
			}
			_customShaders.clear();
			_meshShaders.clear();
			_vfxShaders.clear();
			SceneBase::ScreenRenderQuad::getSingleton()->reset();
			SceneBase::SkyboxGeometry::getSingleton()->reset();
		}

		ShaderServer* ShaderServer::getSingleton() {
			static ShaderServer server;
			return &server;
		}

		ShaderServer::~ShaderServer() {
			//Release memory from ShaderProgram 
			delete _skyboxShader;
			for (std::map<std::string, Shaders::ShaderProgram*>::iterator it = _customShaders.begin();
				it != _customShaders.end(); ++it) {
				delete (*it).second;
			}
			for (std::map<std::string, Shaders::MeshShader*>::iterator it = _meshShaders.begin();
				it != _meshShaders.end(); ++it) {
				delete (*it).second;
			}
			for (std::map<std::string, Shaders::VFXShader*>::iterator it = _vfxShaders.begin();
					it != _vfxShaders.end(); ++it) {
				delete (*it).second;
			}
		}


		bool ShaderServer::loadAndRegisterShader(ShaderProgramType p_type, std::string p_shaderName, std::string p_vertexFile, std::string p_fragmentFile) {
		
			// Find a shader already generated
			auto found = _customShaders.find(p_shaderName);
			auto found2 = _meshShaders.find(p_shaderName);
			auto found3 = _vfxShaders.find(p_shaderName);
			if (found != _customShaders.end() || found2 != _meshShaders.end() || found3 != _vfxShaders.end()) {
				std::cout << "A loaded shader as the same name"<< std::endl;
				return false; 
			}

			// Define path to vertex and fragment shader
			std::filesystem::path vertexPath = defaultShaderPath() / p_vertexFile;
			std::filesystem::path fragmentPath = defaultShaderPath() / p_fragmentFile;

			// Load and Register program
			switch (p_type) {
			case ShaderProgramType::CUSTOM:
				_customShaders[p_shaderName] = new Shaders::ShaderProgram(vertexPath, fragmentPath);
				break;
			case ShaderProgramType::MESH:
				_meshShaders[p_shaderName] = new Shaders::MeshShader(vertexPath, fragmentPath);
				break;
			case ShaderProgramType::SKYBOX:
				std::cout << "Can't load a new skybox texture for now, if you really needs to use one pass it as custom";
				break;
			case ShaderProgramType::VFX:
				_vfxShaders[p_shaderName] = new Shaders::VFXShader(vertexPath, fragmentPath);
				break;
			default:
				return false;
			}
			return true;
		}

		void ShaderServer::renderSkybox(const glm::mat4& p_view, const glm::mat4& p_projection) {
			
			glDisable(GL_DEPTH_TEST); // Desactivate zBuffer test
			glDepthMask(GL_FALSE); // Desactivate wrinting in zBuffer
			
			_skyboxShader->use();
			_skyboxShader->setTransforms(p_view, p_projection);
			_skyboxShader->render();
			_skyboxShader->unuse();

			glDepthMask(GL_TRUE); // Activate wrinting in zBuffer
			glEnable(GL_DEPTH_TEST); // Activate zBuffer test
		}

		void ShaderServer::renderMesh(const std::string p_shaderName, const glm::mat4& p_modelTransform, const Buffers::VertexArrayObject& p_meshVAO, const Materials::PhongMaterial& p_material) {
			// Verify that the shader exist and that it has been register has a MeshShader
			std::map<std::string, Shaders::MeshShader*>::const_iterator it = _meshShaders.find(_defaultMeshShader);
			if (it == _meshShaders.end()) throw std::ios_base::failure(std::string("Mesh shader program  ") + p_shaderName + " does not exists.");
			it->second->setModelTransform(p_modelTransform);
			it->second->renderMesh(p_meshVAO, p_material);
		}

#pragma region GETTERS
		std::string ShaderServer::getDefaultMeshShader() const{
			return _defaultMeshShader;
		}

		Buffers::VertexArrayObject* ShaderServer::getMeshVAO(std::string p_shaderName, PSceneGraph::Mesh& p_mesh) {
			// Verify that the shader exist and that it has been register has a MeshShader
			std::map<std::string, Shaders::MeshShader*>::const_iterator it = _meshShaders.find(_defaultMeshShader);
			if (it == _meshShaders.end()) throw std::ios_base::failure(std::string("Mesh shader program  ") + p_shaderName + " does not exists.");
			return 	it->second->getMeshVAO(p_mesh);
		}

		Textures::CubeMap* ShaderServer::getSkyboxTexture() {
			return _skyboxShader->getTexture();
		}
#pragma endregion

#pragma region SETTERS
		bool ShaderServer::setDefaultMeshShader(std::string p_shader){
			std::map<std::string, Shaders::MeshShader*>::const_iterator it = _meshShaders.find(_defaultMeshShader);
			if (it == _meshShaders.end()) return false;
			_defaultMeshShader = p_shader;
			return true;
		}
#pragma endregion

#pragma region VFX
		void ShaderServer::initVFX(std::string p_shader, std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>> p_configuration, size_t p_width, size_t p_height) {
			std::map<std::string, Shaders::VFXShader*>::const_iterator it = _vfxShaders.find(p_shader);
			if (it == _vfxShaders.end()) throw std::ios_base::failure(std::string("VFX shader program  ") + p_shader + " does not exists.");
			it->second->initFrameBuffer(p_configuration, p_width, p_height);
		}

		void ShaderServer::resizeScreen(size_t p_width, size_t p_height) {
			for (std::map<std::string, Shaders::VFXShader*>::iterator it = _vfxShaders.begin();
				it != _vfxShaders.end(); ++it) {
				(*it).second->resize(p_width, p_height);
			}
		}

		void ShaderServer::bindScreenTo(std::string p_shader, FBOAttachement p_attachment) {
			std::map<std::string, Shaders::VFXShader*>::const_iterator it = _vfxShaders.find(p_shader);
			if (it == _vfxShaders.end()) throw std::ios_base::failure(std::string("VFX shader program  ") + p_shader + " does not exists.");
		 	it->second->bindScreenTo(p_attachment);
		}

		void ShaderServer::unbindsScreen() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glFlush();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
#pragma endregion


#pragma region BINDING

		void ShaderServer::use(std::string p_name, Shaders::ShaderProgram*& p_currentShader) {
			unuse(p_currentShader);

			Shaders::ShaderProgram* res;
			std::map<std::string, Shaders::ShaderProgram*>::const_iterator it = _customShaders.find(p_name);
			if (it == _customShaders.end()) {
				std::map<std::string, Shaders::MeshShader*>::const_iterator it2 = _meshShaders.find(p_name);
				if (it2 == _meshShaders.end()) {
					std::map<std::string, Shaders::VFXShader*>::const_iterator it3 =  _vfxShaders.find(p_name);
					if (it3 == _vfxShaders.end())throw std::ios_base::failure(std::string("Shader program  ") + p_name + " does not exists.");
					else res = it3->second;
				} 
				else res = it2->second;
			}
			else res = it->second;

			p_currentShader = res;
			p_currentShader->use();
		}

		void ShaderServer::unuse(Shaders::ShaderProgram*& p_currentShader) {
			if (p_currentShader != nullptr) {
				p_currentShader->unuse();
				p_currentShader = nullptr;
			}
		}
#pragma endregion
}
