#include <GraphicEngine/Buffers/Header/FrameBufferObject.hpp>

namespace GraphicEngine::Buffers {

		FrameBufferObject::FrameBufferObject(const std::vector<std::pair<FBOAttachement, Textures::Texture2D*>>& p_textures,
			const std::vector<std::pair<FBOAttachement, RenderBuffer*>>& p_renderBuffers)
		{
			assert((p_textures.size() > 0 || p_renderBuffers.size() > 0) && "FrameBufferObject::FrameBufferObject called with no attachment provided");

			// The buffer attachments
			GLenum bufferAttachment[] = { GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE, GL_NONE };

			// We create the frame buffer object and bind it
			glGenFramebuffers(1, &_id);
			glBindFramebuffer(GL_FRAMEBUFFER, _id);

			// We get the dimensions of one existing buffer in order to verify the size consistency over all buffers
			if (p_textures.size() > 0)
			{
				_width = p_textures[0].second->getWidth();
				_height = p_textures[0].second->getHeight();
			}
			else
			{
				_width = p_renderBuffers[0].second->getWidth();
				_height = p_renderBuffers[0].second->getHeight();
			}

			//Iterates through textures 
			for (auto it = p_textures.begin(), end = p_textures.end(); it != end; ++it)
			{
				const auto& current = *it;
				FBOAttachement attachment = current.first;
				Textures::Texture2D* texture = current.second; 

				// Verify that every textures and renderBuffer have the same size
				assert(_width == current.second->getWidth() && _height == current.second->getHeight() && "FrameBufferObject::FrameBufferObject called with textures / render buffers of different sizes");
				
				// Attach the texture to the corresponding FBO
				glFramebufferTexture2D(GL_FRAMEBUFFER, static_cast<GLenum>(attachment), GL_TEXTURE_2D, texture->getId(), 0);
				
				// Inquire the attachment used
				if (static_cast<GLenum>(attachment) >= GL_COLOR_ATTACHMENT0 && static_cast<GLenum>(attachment) < GL_COLOR_ATTACHMENT0 + 8)
				{
					bufferAttachment[static_cast<GLenum>(attachment) - GL_COLOR_ATTACHMENT0] = static_cast<GLenum>(attachment);
				}
			}

			//Iterates through render buffer 
			for (auto it = p_renderBuffers.begin(), end = p_renderBuffers.end(); it != end; ++it)
			{
				const auto& current = *it;

				// Verify that every textures and renderBuffer have the same size
				assert(_width == current.second->getWidth() && _height == current.second->getHeight() && "FrameBufferObject::FrameBufferObject called with textures / render buffers of different sizes");
				
				// Attach the render buffer to the corresponding FBO
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, static_cast<GLenum>(current.first), GL_RENDERBUFFER, current.second->getId());
				// Inquire the attachment used
				FBOAttachement attachment = current.first;
				if (static_cast<GLenum>(attachment) >= GL_COLOR_ATTACHMENT0 && static_cast<GLenum>(attachment) < GL_COLOR_ATTACHMENT0 + 8)
				{
					bufferAttachment[static_cast<GLenum>(attachment) - GL_COLOR_ATTACHMENT0] = static_cast<GLenum>(attachment);
				}
			}

			//Inquire openGL the draw buffer that will be drawn into
			glDrawBuffers(8, bufferAttachment);

			// Verify FBO status
			{
				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_UNSUPPORTED)
				{
					std::cerr << "FrameBufferObject: GL_FRAMEBUFFER_UNSUPPORTED this format is not supported by your graphics card" << std::endl;
				}

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_UNDEFINED)
				{
					std::cerr << "FrameBufferObject: GL_FRAMEBUFFER_UNDEFINED the specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist." << std::endl;
				}

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
				{
					std::cerr << "FrameBufferObject: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT at least one of the framebuffer attachment points are framebuffer incomplete" << std::endl;
				}

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
				{
					std::cerr << "FrameBufferObject: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT the framebuffer does not have at least one image attached to it." << std::endl;
				}

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
				{
					std::cerr << "FrameBufferObject: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi." << std::endl;
				}

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
				{
					std::cerr << "FrameBufferObject: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER. " << std::endl;
				}

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
				{
					std::cerr << "FrameBufferObject: GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; or the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES." << std::endl;
				}

				if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				{
					std::cerr << "FrameBufferObject: initialization failed" << std::endl;
					glBindFramebuffer(GL_FRAMEBUFFER, 0);
					throw std::runtime_error("FrameBufferObject: could not initialize the frame buffer.");
				}
			}
			
			//Unbind buffer in openGL
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	
		FrameBufferObject::~FrameBufferObject()
		{
			if (_id != 0) glDeleteFramebuffers(1, &_id);
		}

#pragma region COPY
		FrameBufferObject::FrameBufferObject(FrameBufferObject&& p_other) 
		{
			_id = p_other._id;
			_width = p_other._width;
			_height = p_other._height;
			p_other._id = 0;
		}

		FrameBufferObject& FrameBufferObject::operator = (FrameBufferObject&& p_other) 
		{
			if (_id != 0) glDeleteFramebuffers(1, &_id);

			_id = p_other._id;
			_width = p_other._width;
			_height = p_other._height;
			p_other._id = 0;

			return (*this);
		}
#pragma endregion

#pragma region GETTERS
		bool FrameBufferObject::isValid() const { 
			return _id != 0; 
		}

		GLuint FrameBufferObject::getId() const { 
			assert(isValid() && "FrameBufferObject::getId called on an uninitialized frame buffer object"); 
			return _id; 
		}

		GLuint FrameBufferObject::getWidth() const { 
			assert(isValid() && "FrameBufferObject::getWidth called on an uninitialized frame buffer object"); 
			return _width;
		}

		GLuint FrameBufferObject::getHeight() const { 
			assert(isValid() && "FrameBufferObject::getHeight called on an uninitialized frame buffer object"); 
			return _height; 
		}
#pragma endregion

#pragma region BINDING
		void FrameBufferObject::bind() const
		{
			assert(isValid() && "FrameBufferObject::bind called on an uninitialized frame buffer object");
			glBindFramebuffer(GL_FRAMEBUFFER, _id);
		}

		void FrameBufferObject::unbind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
#pragma endregion
}