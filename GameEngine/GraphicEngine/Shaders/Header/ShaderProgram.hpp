#ifndef _GRAPHIC_ENGINE_SHADER_PROGRAM_
#define _GRAPHIC_ENGINE_SHADER_PROGRAM_

#include <cassert>

#include <glm/gtc/type_ptr.hpp>

#include <GraphicEngine/Shaders/Header/Shader.hpp>
#include <GraphicEngine/Buffers/Header/VertexBufferObject.hpp>

namespace GraphicEngine {
	namespace Shaders {
		class ShaderProgram
		{
		protected :
			
			/* Program identifier in openGL */
			GLuint _programID;

		private:
			
			/*
			* Link the shader program in openGL
			*/
			void link();

#pragma region UNIFORMS
			/*
			* Gets a uniform location in program
			* @param p_name : name of the uniform we are looking for
			* @return -1 if the uniform does not exist, else the uniform id
			*/
			GLint getUniformLocation(const std::string& p_name) const;

			/*
			* Sets the value of a uniform array based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_values : Value to set
			*/
			template <typename T>
			void setUniform(GLint p_id, const std::vector<T>& p_values)
			{
				assert(id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
				assert(isValid() && isActive());

				setUniform(id, vector[0], vector.size());
			}

			/*
			* Sets the value of an int uniform based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_value : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			*/
			void setUniform(GLint p_id, const GLint& p_value, size_t p_size = 1) const;

			/*
			* Sets the value of a float uniform based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_values : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			*/
			void setUniform(GLint p_id, const GLfloat& p_value, size_t p_size = 1) const;

			/*
			* Sets the value of a vec2 uniform based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_values : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			*/
			void setUniform(GLint p_id, const glm::vec2& p_value, size_t p_size = 1) const;

			/*
			* Sets the value of a vec3 uniform based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_values : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			*/
			void setUniform(GLint p_id, const glm::vec3& p_value, size_t p_size = 1) const;

			/*
			* Sets the value of a vec4 uniform based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_values : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			*/
			void setUniform(GLint id, const glm::vec4& p_value, size_t p_size = 1) const;

			/*
			* Sets the value of a matrix 2x2 uniform based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_values : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			*/
			void setUniform(GLint p_id, const glm::mat2x2& p_value, size_t p_size = 1) const;

			/*
			* Sets the value of a matrix 3x3 uniform based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_values : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			*/
			void setUniform(GLint p_id, const glm::mat3x3& p_value, size_t p_size = 1) const;

			/*
			* Sets the value of a matrix 4x4 uniform based on its id.
			* @param p_id : Identifier of the uniform
			* @param p_values : Value to set
			* @param p_size : Size of the array if the reference designate the first reference in an array
			*/
			void setUniform(GLint p_id, const glm::mat4x4& p_value, size_t p_size = 1) const;
#pragma endregion

#pragma region ATTRIBUTES
			/*
			* Gets the attribute location
			* @param p_name : The name of the attribute
			* @return -1 if the attribute does not exist, else the uniform id
			*/
			GLint getAttributeLocation(const std::string& p_name) const
			{
				assert(isValid());
				return glGetAttribLocation(_programID, p_name.c_str());
			}
#pragma endregion


		public :

			/*
			* Constructor 
			* Initialize a program shader with a vertex and a fragment shader
			* @param p_vertex : Vertex shader to attach to this program
			* @param p_fragment : Fragment shader to attach to this program
			*/
			ShaderProgram(const Shader& p_vertex, const Shader& p_fragment);

			/*
			* Constructor 
			* Initialize a program shader with a vertex and a fragment shader
			* @param p_vertexPath : Path to the vertex shader to attach to this program
			* @param p_fragmentPath : Path ot the fragment shader to attach to this program
			*/
			ShaderProgram(const std::filesystem::path& p_vertexPath, const std::filesystem::path& p_fragmentPath);

			/* Destructor */
			~ShaderProgram();

#pragma region GETTERS
			/*
			* Determine whether this programm is valid
			* @return true if the program is valid, else false
			*/
			bool isValid() const;

			/*
			* Gets the program's identifier
			* @return the identifier of the shader program
			*/
			GLuint getId() const;

			/*
			* Determines whether this shader program is active
			* @return true if this shader program is active, else false
			*/
			bool isActive() const;

			/*
			* Gets the identifier of the active shader program
			* @return active shader program's identifier
			*/
			static GLint getActive();
#pragma endregion

#pragma region COPY
			/*Disallow copying from simple reference*/
			ShaderProgram(const ShaderProgram&) = delete;
			ShaderProgram& operator=(const ShaderProgram&) = delete;
			
			/*
			* Move constructor
			* @param p_other : Shader to move
			*/
			ShaderProgram(ShaderProgram&& p_other);

			/*
			*  Move assignment
			*  @param p_other : Shader to move
			*/
			ShaderProgram& operator= (ShaderProgram&& p_other);

#pragma endregion

#pragma region BINDING
			/*
			* Use this program as the current program in openGL
			*/
			void use() const;

			/*
			* Unuse this program as current in openGL
			*/
			void unuse() const; 
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
				GLint id = getUniformLocation(p_name);

				if (id != -1)
				{
					setUniform(id, p_value, p_size);
					return true;
				}
				return false;
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
				GLint id = getUniformLocation(p_name);
				if (id != -1)
				{
					setUniform(id, p_value);
					return true;
				}
				return false;
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

#endif // !_GRAPHIC_ENGINE_SHADER_PROGRAM_



