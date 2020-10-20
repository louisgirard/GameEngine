#include <GraphicEngine/Shaders/Header/ShaderManager.hpp>

namespace GraphicEngine {
	namespace Shaders {
	
		ShaderManager::~ShaderManager() {
			//Release memory from ShaderProgram 
			for (std::map<std::string, ShaderProgram*>::iterator it = _registry.begin();
				it != _registry.end(); ++it) {
				delete (*it).second;
			}
		}

		void ShaderManager::loadAndRegisterShader(std::string p_shaderName, std::string p_vertexFile, std::string p_fragmentFile) {
		
			// They can not be two shader program with the same name
			if(_registry.find(p_shaderName) != _registry.end()) throw std::ios_base::failure(std::string("Shader program  ") + p_shaderName + " already exists.");
			
			// Define path to vertex and fragment shader
			std::filesystem::path vertexPath = Games::dataPath() / "Shaders" / p_vertexFile;
			std::filesystem::path fragmentPath = Games::dataPath() / "Shaders" / p_fragmentFile;

			// Load program 
			ShaderProgram* newProgram = new ShaderProgram(p_vertexFile, p_fragmentFile);
			// Register program
			_registry.insert(std::pair<std::string, ShaderProgram*>(p_shaderName, newProgram));
		}

#pragma region BINDING

		void ShaderManager::use(std::string p_name) {
			unuse();

			std::map<std::string, ShaderProgram*>::const_iterator it =  _registry.find(p_name);
			if(it == _registry.end()) throw std::ios_base::failure(std::string("Shader program  ") + p_name + " does not exists.");
			
			_currentProgram = it->second;
			_currentProgram->use();
		}

		void ShaderManager::unuse() {
			if (_currentProgram != nullptr) {
				_currentProgram->unuse();
				_currentProgram = nullptr;
			}
		}
#pragma endregion

#pragma region ATTRIBUTES
		void ShaderManager::setAttribute(const std::string& p_name, const Buffers::VertexBufferObject* p_buffer, GLuint p_nbInstances = 0) {
			assert(_currentProgram == nullptr && "ShaderManager::setAttribute called while no shader is assigned ");
			
			_currentProgram->setAttribute(p_name, p_buffer, p_nbInstances);
		}
#pragma endregion
	}
}
