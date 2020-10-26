#ifndef _GRAPHIC_ENGINE_VERTEX_BUFFER_OBJECT_HPP_
#define _GRAPHIC_ENGINE_VERTEX_BUFFER_OBJECT_HPP_

#include <vector>
#include <iostream>

#include <glm/common.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <GraphicEngine/Header/GraphicConfig.hpp>
#include <GraphicEngine/TypeSpec/Header/GLMTypesSpec.hpp>

namespace GraphicEngine::Buffers {
		class VertexBufferObject
		{
		protected:

			/* Buffer identifier */
			GLuint _id;
			/* Type of the scalar used in this buffer*/
			GLenum _scalarType;
			/* Size of the buffer */
			size_t _bufferSize;
			/* Number of components per vertex attribute */
			size_t _dataSize;

		public:

			/*
			* Default constructor
			* Warning this buffer is invalid
			*/
			VertexBufferObject():_id(0), _scalarType(), _bufferSize(0), _dataSize(0){}

			/*
			* Constructor
			* @param p_buffer : The buffer linked to this object
			* @param p_usage : Update frequency for this buffer
			*/
			template <class T>
			VertexBufferObject(const std::vector<T>& p_buffer, BufferUpdate p_usage = BufferUpdate::staticDraw)
			{
				//Verify the type used in this buffer is compatible with our engine
				static_assert(GLMTypesSpec<T>::isCompatible() && (GLMTypesSpec<T>::isScalar() || GLMTypesSpec<T>::isVector()), "Invalid type provided in VertexBufferObject constructor");
				

				// Création of the vertex buffer object
				// (We want only one buffer to be generated)
				glGenBuffers(1, &_id);
				handleGLerror("VBO()");
				//std::cout << "Vertex Buffer object created " << _id << std::endl;

				// Bind buffer to openGL
				bind();
				// Set Buffer Data
				glBufferData(GL_ARRAY_BUFFER, sizeof(T) * p_buffer.size(), p_buffer.data(), static_cast<GLenum>(p_usage));
				handleGLerror("VBO()");
				//Init attributes
				_scalarType = GLenum(GLMTypesSpec<T>::glType());
				_bufferSize = p_buffer.size();
				_dataSize = GLMTypesSpec<T>::size();

				// Unbind Buffer
				unbind();
			}

			/* Destructor */
			~VertexBufferObject();

			/*
			* Update the content of the buffer
			* @param p_buffer : New content to pass in the buffer
			*/
			template <class T>
			void update(const std::vector<T>& p_buffer) const
			{
				// Verify the type used in this buffer is compatible with our engine
				static_assert(GLMTypesSpec<T>::isCompatible() && (GLMTypesSpec<T>::isScalar() || GLMTypesSpec<T>::isVector()), "Invalid type provided in VertexBufferObject constructor");
				
				// Verify data provided meet the requirement to update this buffer
				assert(isValid());
				assert(_scalarType == GLenum(GLMTypesSpec<T>::glType()));
				assert(_dataSize == GLMTypesSpec<T>::size());
				assert(p_buffer.size() == _bufferSize);

				//Update the data in openGL
				bind();
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(T) * p_buffer.size(), p_buffer.data());
				handleGLerror("VBO::update()");
				unbind();
			}

			/*
			* Associates this vertex buffer object with the attribute of a shader
			* Warning, the buffer is bound after calling this method
			* @param p_shaderAttributeIndex : Index of the attribut in the shader
			* @param p_nbInstances : number of instance before updating the attribute
			*/
			void passAsAttribute(GLint p_shaderAttributeIndex, GLuint nbInstances = 0) const;

#pragma region COPY
			/*Disallow copying from simple reference*/
			VertexBufferObject(const VertexBufferObject&) = delete;
			VertexBufferObject& operator = (const VertexBufferObject&) = delete;

			/*
			* Move constructor
			* @param p_other : VBO to move
			*/
			VertexBufferObject(VertexBufferObject&& p_other);

			/*
			*  Move assignment
			*  @param p_other : VBO to move
			*/
			VertexBufferObject& operator= (VertexBufferObject&& p_other);
#pragma endregion

#pragma region GETTERS
			/*
			* Determines whether this VBO is valid
			* @return true if this buffer is valid, else false
			*/
			bool isValid() const;

			/*
			* Gets the identifier of the VBO
			* @return the identifier of this VBO
			*/
			GLuint getId() const;

			/*
			* Gets the scalar type as a GLenum 
			* @return the scalar type
			*/
			GLenum glScalarType() const;

			/*
			* Gets the buffer size
			* @return buffer size
			*/
			size_t bufferSize() const;

			/*
			* Gets the number of components per vertex attribute
			* @return number of components per vertex attribute
			*/
			unsigned int dataSize() const; 
#pragma endregion

#pragma region BINDING
			/*
			* Binds this buffer in openGl
			*/
			void bind() const;

			/*
			* Unbinds this buffer in openGL
			*/
			void unbind() const;
#pragma endregion
		};
}

#endif



