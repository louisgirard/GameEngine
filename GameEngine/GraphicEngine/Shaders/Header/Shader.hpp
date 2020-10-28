#ifndef _GRAPHIC_ENGINE_SHADER_HPP_
#define _GRAPHIC_ENGINE_SHADER_HPP_

#include <cassert>

#include <GraphicEngine/Header/GraphicEnum.hpp>
#include <GraphicEngine/Shaders/Header/ShaderSource.hpp>

namespace GraphicEngine::Shaders {
		class Shader
		{
		protected:

			/*Type of this shader*/
			ShaderType _type;
			/*ID of this shader in openGL*/
			GLuint _shaderID;

		public:

			/*
			* Default constructor
			* Warning this shader is invalid
			*/
			Shader():_type(ShaderType::vertexShader),_shaderID(0){}

			/* Default Constructor
			* Throws a exception if the source does not compile
			* @param p_sourcePath : The path to the source code of the shader.
			* @param p_type : The type of the shader
			*/
			Shader(const ShaderSource p_source, ShaderType p_type);

			/* Destructor */
			~Shader();

#pragma region GETTERS
			/*
			* Determines whether this shader is valid
			* @return true if this shader is valid, else false
			*/
			bool isValid() const;

			/*
			* Gets the type of the shader.
			* @return the type of the shader
			*/
			ShaderType getType() const;


			/*
			* Gets the identifier of the shader.
			* @return the identifier of the shader
			*/
			GLuint getId() const;
#pragma endregion

#pragma region COPY		
			/*Disallow copying from simple reference*/
			Shader(const Shader&) = delete;
			Shader& operator=(const Shader&) = delete;

			/*
			* Move constructor
			* @param p_other : Shader to move
			*/
			Shader(Shader&& p_other);

			/*
			*  Move assignment
			*  @param p_other : Shader to move
			*/
			Shader& operator= (Shader&& p_other);
#pragma endregion
		};
}

#endif // !_GRAPHIC_ENGINE_SHADER_HPP_



