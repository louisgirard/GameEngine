#include <GraphicEngine/Buffers/Header/FrameBuffer.hpp>

namespace GraphicEngine::Buffers {

		void FrameBuffer::initialize(size_t p_width, size_t p_height)
		{
			// Texture or render buffer attachment
			std::vector <std::pair<FBOAttachement, Textures::Texture2D*>> textures;
			std::vector<std::pair<FBOAttachement, RenderBuffer*>> renderBuffers;

			// For each configuration create an empty corresponding buffer
			for (auto it = _configuration.begin(), end = _configuration.end(); it != end; ++it)
			{
				const std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>& current = (*it);

				if (std::get<1>(current) == FBOAttachmentType::texture)
				{
					// Create the texture and register it
					Textures::Texture2D texture((GLuint)p_width, (GLuint)p_height, std::get<2>(current));
					_objectAttached[std::get<0>(current)] = std::move(texture);
					textures.push_back({ std::get<0>(current), &std::get<1>(_objectAttached[std::get<0>(current)]) });
				}
				else
				{
					// Create the render buffer and register it
					RenderBuffer renderBuffer((GLuint)p_width, (GLuint)p_height, std::get<2>(current));
					_objectAttached[std::get<0>(current)] = std::move(renderBuffer);
					renderBuffers.push_back({ std::get<0>(current), &std::get<0>(_objectAttached[std::get<0>(current)]) });
				}
			}

			// Init attribute
			_FBO = FrameBufferObject(textures, renderBuffers);
			_width = p_width;
			_height = p_height;
		}

		FrameBuffer::FrameBuffer(const std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>>& p_configuration,size_t p_width, size_t p_height): _configuration(p_configuration)
		{
			initialize(p_width, p_height);
		}

		void FrameBuffer::resize(size_t p_width, size_t p_height)
		{
			assert(isValid() && "FrameBuffer::resize called but the frame buffer is not initialized");
			initialize(p_width, p_height);
		}

#pragma region COPY
		FrameBuffer::FrameBuffer(FrameBuffer&& p_other)
			: _configuration(std::move(p_other._configuration)),
			_objectAttached(std::move(p_other._objectAttached)),
			_FBO(std::move(p_other._FBO)),
			_width(p_other._width),
			_height(p_other._height)
		{}

		FrameBuffer& FrameBuffer::operator= (FrameBuffer&& p_other)
		{
			_configuration = std::move(p_other._configuration);
			_objectAttached = std::move(p_other._objectAttached);
			_FBO = std::move(p_other._FBO);
			_width = p_other._width;
			_height = p_other._height;

			return (*this);
		}
#pragma endregion

#pragma region GETTERS
		bool FrameBuffer::isValid() const { 
			return _FBO.isValid(); 
		}

		const Textures::Texture2D* FrameBuffer::getTexture(FBOAttachement p_attachment) const
		{
			assert(isValid() && "FrameBuffer::getTexture called but the frame buffer is not initialized");

			auto it = _objectAttached.find(p_attachment);
			if (it != _objectAttached.end() && std::holds_alternative<Textures::Texture2D>(it->second))
			{
				return &std::get<1>(it->second);
			}
			return nullptr;
		}

		const RenderBuffer* FrameBuffer::getRenderBuffer(FBOAttachement attachment) const
		{
			assert(isValid() && "FrameBuffer::getRenderBuffer called but the frame buffer is not initialized");
			auto it = _objectAttached.find(attachment);
			if (it != _objectAttached.end() && std::holds_alternative<RenderBuffer>(it->second))
			{
				return &std::get<0>(it->second);
			}
			return nullptr;
		}

		size_t FrameBuffer::getWidth() const { return _width; }

		size_t FrameBuffer::getHeight() const { return _height; }
#pragma endregion

#pragma region BINDING
		void FrameBuffer::bind() const
		{
			assert(isValid() && "FrameBuffer::bind called but the frame buffer is not initialized");
			_FBO.bind();
		}

		void FrameBuffer::unbind() const
		{
			_FBO.unbind();
		}
#pragma endregion
}