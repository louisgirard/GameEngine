#ifndef _GRAPHIC_ENGINE_FRAME_BUFFER_OBJECT_HPP_
#define _GRAPHIC_ENGINE_FRAME_BUFFER_OBJECT_HPP_

#include <GraphicEngine/Buffers/Header/RenderBuffer.hpp>
#include <vector>

namespace GraphicEngine::Buffers {
		class FrameBufferObject
		{
		protected :
			/* Identifier of the FBO */
			GLuint _id;
			/* Screen dimension */
			GLuint _width, _height;
			
		public:
			/* Default Constructor*/
			FrameBufferObject(): _id(0),_height(0),_width(0){}

			/*
			* Constructor
			* @param p_textures : Texture associated with an openGL FBO attachment
			* @param p_renderBuffers : Render buffer associated with an openGL FBO attachment
			*/
			FrameBufferObject(const std::vector<std::pair<FBOAttachement, Textures::Texture2D*>>& p_textures,
				const std::vector<std::pair<FBOAttachement, RenderBuffer*>>& p_renderBuffers);

			/* Destructor */
			~FrameBufferObject();

#pragma region COPY
			/*Disallow copying from simple reference*/
			FrameBufferObject(const FrameBufferObject&) = delete;
			FrameBufferObject& operator= (const FrameBufferObject&) = delete;

			/*
			* Move constructor
			* @param p_other : VBO to move
			*/
			FrameBufferObject(FrameBufferObject&& p_other);

			/*
			*  Move assignment
			*  @param p_other : VBO to move
			*/
			FrameBufferObject& operator = (FrameBufferObject&& p_other);
#pragma endregion

#pragma region GETTERS
			/*
			* Determines whether this buffer is valid 
			* @return true if this buffer is valid, else false
			*/
			bool isValid() const; 

			/*
			* Gets the buffer's identifier in openGL
			* @return buffer's identifier
			*/
			GLuint getId() const;

			/*
			* Gets width
			* @return buffer's width
			*/
			GLuint getWidth() const;

			/*
			* Gets height
			* @return buffer's height
			*/
			GLuint getHeight() const;
#pragma endregion

#pragma region BINDING
			/*
			* Binds this buffer in openGL
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


