#ifndef _GRAPHIC_ENGINE_RENDER_BUFFER_HPP_
#define _GRAPHIC_ENGINE_RENDER_BUFFER_HPP_

#include <GraphicEngine/Textures/Header/Texture2D.hpp>

namespace GraphicEngine::Buffers {
		class RenderBuffer
		{
			/* Identifier of the buffer */
			GLuint _id;
			/* Screen dimension*/
			GLuint _width, _height;

		public:
			/* 
			* Default constuctor
			* Warning the buffer is invalid
			*/
			RenderBuffer():_id(0), _width(0), _height(0){}

			/*
			* Constructor
			* @param p_width : Width of the render buffer
			* @param p_height : Height of the buffer
			* @param p_format : Format of the data inside the buffer
			*/
			RenderBuffer(GLuint p_width, GLuint p_height, TextureInternalFormat p_format);

			/* Destructor */
			~RenderBuffer();

#pragma region COPY
			/*Disallow copying from simple reference*/
			RenderBuffer(const RenderBuffer&) = delete;
			RenderBuffer& operator=(const RenderBuffer&) = delete;

			/*
			* Move constructor
			* @param p_other : Buffer to move
			*/
			RenderBuffer(RenderBuffer&& p_other);

			/*
			*  Move assignment
			*  @param p_other : Buffer to move
			*/
			RenderBuffer& operator= (RenderBuffer&& p_other);
#pragma endregion

#pragma region GETTERS
			/*
			* Determines whether this buffer is valid.
			* @return true if the buffer is valid, else false
			*/
			bool isValid() const;

			/*
			* Gets the buffer's identifier in openGL
			* @return the identifier of the buffer
			*/
			GLuint getId() const; 

			/*
			* Gets the width
			* @return buffer's width
			*/
			GLuint getWidth() const; 

			/*
			* Gets the height
			* @return buffer's height
			*/
			GLuint getHeight() const; 
#pragma endregion
		};
}

#endif // !_GRAPHIC_ENGINE_RENDER_BUFFER_HPP_



