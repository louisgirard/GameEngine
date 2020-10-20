#ifndef _GRAPHIC_ENGINE_SHADER_LOADER_HPP_
#define  _GRAPHIC_ENGINE_SHADER_LOADER_HPP_

#include <map>
#include <string>

#include <Games/Header/DefaultConfig.hpp>
#include <GraphicEngine/Shaders/Header/ShaderProgram.hpp>

namespace GraphicEngine {
	namespace Shaders {
		class ShaderManager
		{
		protected :
			// Registry of loaded program shader
			std::map<std::string, ShaderProgram*> _registry;
			// Current program used in openGL
			ShaderProgram* _currentProgram;

		public :

			/*Default Constructor*/
			ShaderManager(){}

			/*Destructor*/
			~ShaderManager();

			/*
			* Load in openGl and register a shader program
			* @param p_shaderName : The name to which the program will be registered
			* @param p_vertexFile : File containing the vertex shader linked to this program
			* @param p_fragmentFile :  File containing the fragment shader linked to this program
			*/
			void loadAndRegisterShader(std::string p_shaderName, std::string p_vertexFile, std::string p_fragmentFile);


#pragma region BINDING
			/*
			* Use a program as the current program in openGL
			* @param p_name : Name of the program to use 
			*/
			void use(std::string p_name);

			/*
			* Unuse programs
			*/
			void unuse();
#pragma endregion

#pragma region UNIFORMS
			/*
			* Tries to sets the uniform value based on its name
			* @param p_name : Name of the uniform
			* @param p_value : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			* @return true if the uniform has been set, else false
			*/
			template <typename Type>
			bool trySetUniform(const std::string& p_name, const Type& p_value, size_t p_size = 1)
			{
				assert(_currentProgram == nullptr && "ShaderManager::trySetUniform called while no shader is assigned ");
				
				_currentProgram->trySetUniform(p_name, p_value, p_size);
			}

			/*
			* Tries to set the value of a uniform array based on its name
			* @param p_name : Name of the uniform
			* @param p_value : Value to set
			* @return true if the uniform has been set, else false
			*/
			template <typename Type>
			bool trySetUniform(const std::string& p_name, const std::vector<Type>& p_value)
			{
				assert(_currentProgram == nullptr && "ShaderManager::trySetUniform called while no shader is assigned ");

				_currentProgram->trySetUniform(p_name, p_value);
			}
#pragma endregion

#pragma region ATTRIBUTES
			/*
			* Sets an attribute of the shader
			* @param p_name : The name of the attribute
			* @param p_buffer : Vertex buffer object to associate with this attribute
			* @param p_nbInstances : Numbre of instances to skip until updating the attribute
			*/
			void setAttribute(const std::string& p_name, const Buffers::VertexBufferObject* p_buffer, GLuint p_nbInstances = 0);
#pragma endregion
		};
	}
}

#endif // !_GRAPHIC_ENGINE_SHADER_LOADER_HPP_



