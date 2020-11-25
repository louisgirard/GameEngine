#ifndef _GRAPHIC_ENGINE_FRAME_BUFFER_HPP_
#define _GRAPHIC_ENGINE_FRAME_BUFFER_HPP_

#include <unordered_map>
#include <variant>
#include <vector>

#include <GraphicEngine/Buffers/Header/FrameBufferObject.hpp>

namespace GraphicEngine::Buffers {
		class FrameBuffer
		{
		protected:
			/* Configuration for a each FBO channels */
			std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>> _configuration;
			/* Texture or render buffer attach to an FBO channel */
			std::unordered_map<FBOAttachement, std::variant<RenderBuffer, Textures::Texture2D>> _objectAttached;
			/* FBO linked to this buffer */
			FrameBufferObject _FBO;
			/* Screen size*/
			size_t _width, _height;

		private:
			/*
			* Initialize the buffer
			* @param p_width : Width of the buffer
			* @param p_height : Height of the buffer
			*/
			void initialize(size_t p_width, size_t p_height);

		public:

			/*
			* Default constructor
			* Warning this buffer is invalid
			*/
			FrameBuffer():_height(0),_width(0){}

			/*
			* Constructor
			* @param p_configuration : The configuration of each channel of the frame buffer
			* @param p_width : Width of the buffer
			* @param p_height : Height of the buffer
			*/
			FrameBuffer(const std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>>& p_configuration,size_t p_width, size_t p_height);
		
			/*
			* Resizes the frame buffer. In case you inherit this class, this method is virtual and allows
			* you to handle some specific post initializations.
			* @param p_width : The new width
			* @param p_height : The new height
			**/
			virtual void resize(size_t p_width, size_t p_height);

#pragma region COPY
			/*Disallow copying from simple reference*/
			FrameBuffer(const FrameBuffer&) = delete;
			FrameBuffer& operator= (const FrameBuffer&) = delete;

			/*
			* Move constructor
			* @param p_other : VBO to move
			*/
			FrameBuffer(FrameBuffer&& p_other);

			/*
			*  Move assignment
			*  @param p_other : VBO to move
			*/
			virtual FrameBuffer& operator= (FrameBuffer&& p_other);
#pragma endregion

#pragma region GETTERS
			/*
			* Determines whether this frame buffer is valid
			* @return true if this frame buffer is valid, else false
			*/
			bool isValid() const;

			/*
			* Gets the texture associated with the provided attachment
			* @param p_attachment : The FBO attachment
			* @return A pointer to the texture or nullptr if there is no attachment or a the attachment is a render buffer
			*/
			const Textures::Texture2D* getTexture(FBOAttachement p_attachment) const;

			/*
			* Gets the render buffer associated with the provided attachment
			* @param p_attachment : The FBO attachment
			* @return A pointer to the render buffer or nullptr if there is no attachment or a the attachment is a texture
			**/
			const RenderBuffer* getRenderBuffer(FBOAttachement p_attachment) const;

			/*
			* Gets the width of the frame buffer
			* @return width of the frame buffer
			*/
			size_t getWidth() const;

			/*
			* Gets the height of the frame buffer
			* @return height of the frame buffer
			*/
			size_t getHeight() const;
#pragma endregion

#pragma region BINDING
			/*
			* Binds this frame buffer in openGL
			*/
			void bind() const;

			/*
			* Unbinds this frame buffer
			*/
			void unbind() const;
#pragma endregion
		};
}

#endif // !_GRAPHIC_ENGINE_FRAME_BUFFER_HPP_



