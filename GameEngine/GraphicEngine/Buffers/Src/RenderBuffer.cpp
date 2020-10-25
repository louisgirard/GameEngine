#include <GraphicEngine/Buffers/Header/RenderBuffer.hpp>

namespace GraphicEngine::Buffers {

		RenderBuffer::RenderBuffer(GLuint p_width, GLuint p_height, TextureInternalFormat p_format)
		{
			// Generate and bind the buffer inside openGL
			glGenRenderbuffers(1, &_id);
			glBindRenderbuffer(GL_RENDERBUFFER, _id);
			glRenderbufferStorage(GL_RENDERBUFFER, static_cast<GLenum>(p_format), p_width, p_height);

			// Save dimension
			_width = p_width;
			_height = p_height;
		}

		RenderBuffer::~RenderBuffer()
		{
			// Release memory inside oenGL
			if (_id != 0) { glDeleteRenderbuffers(1, &_id); }
		}

#pragma region COPY
		RenderBuffer::RenderBuffer(RenderBuffer&& p_other)
		{
			_id = p_other._id;
			_width = p_other._width;
			_height = p_other._height;
			p_other._id = 0;
		}

		RenderBuffer& RenderBuffer::operator= (RenderBuffer&& p_other)
		{
			if (_id != 0) { glDeleteRenderbuffers(1, &_id); }

			_id = p_other._id;
			_width = p_other._width;
			_height = p_other._height;
			p_other._id = 0;

			return (*this);
		}
#pragma endregion

#pragma region GETTERS
		bool RenderBuffer::isValid() const {
			return _id != 0; 
		}

		GLuint RenderBuffer::getId() const { 
			assert(isValid() && "RenderBuffer::getId called on an invalid RenderBuffer"); 
			return _id; }

		GLuint RenderBuffer::getWidth() const { 
			assert(isValid() && "RenderBuffer::getWidth called on an invalid RenderBuffer");
			return _width; 
		}

		GLuint RenderBuffer::getHeight() const { 
			assert(isValid() && "RenderBuffer::getHeight called on an invalid RenderBuffer"); 
			return _height; 
		}
#pragma endregion
}