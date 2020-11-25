#include <GraphicEngine/Buffers/Header/GeometryBuffer.hpp>

namespace GraphicEngine {
	namespace Buffers {

		std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>> GeometryBuffer::configuration()
		{
			std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>> result;

			// Texture for positions
			result.push_back({ FBOAttachement::colorAttachment0, FBOAttachmentType::texture, TextureInternalFormat::rgb32f });
			// Texture for normals
			result.push_back({ FBOAttachement::colorAttachment1, FBOAttachmentType::texture, TextureInternalFormat::rgb32f });
			// Diffuse color
			result.push_back({ FBOAttachement::colorAttachment2, FBOAttachmentType::texture, TextureInternalFormat::rgba });
			// Specular color
			result.push_back({ FBOAttachement::colorAttachment3, FBOAttachmentType::texture, TextureInternalFormat::rgba });
			// Depth
			result.push_back({ FBOAttachement::colorAttachment4, FBOAttachmentType::texture, TextureInternalFormat::r32f });
			// z buffer
			result.push_back({ FBOAttachement::depthAttachment, FBOAttachmentType::renderBuffer, TextureInternalFormat::depth });
			return result;
		}

		void GeometryBuffer::updateAttachments()
		{
			_positions = getTexture(FBOAttachement::colorAttachment0);
			_normals = getTexture(FBOAttachement::colorAttachment1);
			_diffuse = getTexture(FBOAttachement::colorAttachment2);
			_specular = getTexture(FBOAttachement::colorAttachment3);
			_depth = getTexture(FBOAttachement::colorAttachment4);
			_zbuffer = getRenderBuffer(FBOAttachement::depthAttachment);
		}

		GeometryBuffer::GeometryBuffer(size_t p_width, size_t p_height) : FrameBuffer(configuration(), p_width, p_height)
		{
			updateAttachments();
		}

		void GeometryBuffer::resize(size_t width, size_t height)
		{
			FrameBuffer::resize(width, height);
			updateAttachments();
		}

#pragma region COPY
		GeometryBuffer::GeometryBuffer(GeometryBuffer&& p_other): FrameBuffer(std::move(p_other))
		{
			updateAttachments();
		}

		GeometryBuffer& GeometryBuffer::operator= (GeometryBuffer&& p_other)
		{
			FrameBuffer::operator=(std::move(p_other));

			if (isValid()) { updateAttachments(); }

			return (*this);
		}
#pragma endregion

#pragma region GETTERS
		const Textures::Texture2D* GeometryBuffer::getPositions() const {
			return _positions; 
		}

		const Textures::Texture2D* GeometryBuffer::getNormals() const { 
			return _normals; 
		}

		const Textures::Texture2D* GeometryBuffer::getDiffuse() const { 
			return _diffuse; 
		}

		const Textures::Texture2D* GeometryBuffer::getSpecular() const { 
			return _specular; 
		}

		const Textures::Texture2D* GeometryBuffer::getDepth() const { 
			return _depth; 
		}

		const RenderBuffer* GeometryBuffer::getZBuffer() const { 
			return _zbuffer; 
		}
#pragma endregion
	}
}
