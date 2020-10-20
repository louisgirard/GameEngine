#ifndef _GRAPHIC_ENGINE_ELEMENT_BUFFER_OBJECT_HPP_
#define _GRAPHIC_ENGINE_ELEMENT_BUFFER_OBJECT_HPP_

#include <vector>
#include <GL/glew.h>

#include <GraphicEngine/Header/GraphicEnum.hpp>
#include <GraphicEngine/Buffers/Header/VertexBufferObject.hpp>

namespace GraphicEngine {
	namespace Buffers {
		class ElementBufferObject
		{
		protected:
			/* Identifier of the EBO */
			GLuint _id;
			/* Size of the EBO */
			size_t _size;

		public:

			/*
			* Constructor 
			* @param p_indices : Indicices buffer
			* @param p_usage : Update frequency for this buffer
			*/
			ElementBufferObject(const std::vector<GLuint>& p_indices, BufferUpdate p_usage = BufferUpdate::staticDraw);

			/* Destructor */
			~ElementBufferObject();

#pragma region COPY
			/*Disallow copying from simple reference*/
			ElementBufferObject(const ElementBufferObject&) = delete;
			ElementBufferObject& operator= (const ElementBufferObject&) = delete;

			/*
			* Move constructor
			* @param p_other : VBO to move
			*/
			ElementBufferObject(ElementBufferObject&& p_other);

			/*
			*  Move assignment
			*  @param p_other : VBO to move
			*/
			ElementBufferObject& operator= (ElementBufferObject&& p_other);
#pragma endregion
	
#pragma region GETTERS
			/*
			* Determines whether this EBO is valid
			* @return true if the EBO is valid, else false
			*/
			bool isValid() const;

			/*
			* Gets the buffer identifier in openGL
			* @return the identifier of the EBO
			*/
			GLuint getId() const;

			/*
			* Gets the type of the elements in the buffer 
			* @return GL_UNSIGNED_INT
			*/
			GLenum glElementType() const;

			/*
			* Gets the size of the buffer
			* @return number of element in the buffer
			*/
			size_t size() const;
#pragma endregion

#pragma region BINDING
			/*
			* Binds this buffer in openGL
			*/
			void bind() const;

			/*
			* Unbinds this buffer
			*/
			void unbind() const;
#pragma endregion
		};
	}

}

#endif // !_GRAPHIC_ENGINE_ELEMENT_BUFFER_OBJECT_HPP_



