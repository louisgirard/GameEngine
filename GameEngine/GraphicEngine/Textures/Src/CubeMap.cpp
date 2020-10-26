#include <GraphicEngine/Textures/Header/CubeMap.hpp>

namespace GraphicEngine::Textures {

		bool CubeMap::exists(const std::unordered_map<CubeMapPosition, std::filesystem::path>& p_texturesFile, CubeMapPosition p_entry)
		{
			return p_texturesFile.find(p_entry) != p_texturesFile.end();
		}

		CubeMap::CubeMap(GLuint p_width, GLuint p_height, TextureInternalFormat p_format)
		{
			// Create an bind the texture as a cube map
			glGenTextures(1, &_id);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

			// Iterate through all face and instantiate a texture for each one of them
			for (GLenum it = GL_TEXTURE_CUBE_MAP_POSITIVE_X, end = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z + 1; it != end; ++it)
			{
				std::pair<GLenum, GLenum> baseTypes = textureInternalFormatBaseType(p_format);
				glTexImage2D(it, 0, static_cast<GLenum>(p_format), p_width, p_height, 0, baseTypes.first, baseTypes.second, nullptr);
			}
			
			// Sets the default property of the texture
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureFilterTarget::magFilter), static_cast<GLenum>(TextureFilterMode::nearest));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureFilterTarget::minFilter), static_cast<GLenum>(TextureFilterMode::nearest));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureWrappingTarget::wrapS), static_cast<GLenum>(TextureWrappingMode::clampToEdge));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureWrappingTarget::wrapT), static_cast<GLenum>(TextureWrappingMode::clampToEdge));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureWrappingTarget::wrapR), static_cast<GLenum>(TextureWrappingMode::clampToEdge));
			
			// Unbind texture
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		CubeMap::CubeMap(const std::unordered_map<CubeMapPosition, std::filesystem::path>& files)
		{
			// Verify each side of the cube as a texture
			assert(exists(files, CubeMapPosition::front) && "CubeMap::CubeMap texture file does not exist");
			assert(exists(files, CubeMapPosition::back) && "CubeMap::CubeMap texture file does not exist");
			assert(exists(files, CubeMapPosition::left) && "CubeMap::CubeMap texture file does not exist");
			assert(exists(files, CubeMapPosition::right) && "CubeMap::CubeMap texture file does not exist");
			assert(exists(files, CubeMapPosition::top) && "CubeMap::CubeMap texture file does not exist");
			assert(exists(files, CubeMapPosition::bottom) && "CubeMap::CubeMap texture file does not exist");
			assert(files.size() == 6 && "CubeMap::CubeMap you should provide 6 textures!");

			// Find each texture file path
			std::string fileXpositive = files.find(CubeMapPosition::xPositive)->second.string();
			std::string fileXnegative = files.find(CubeMapPosition::xNegative)->second.string();
			std::string fileYpositive = files.find(CubeMapPosition::yPositive)->second.string();
			std::string fileYnegative = files.find(CubeMapPosition::yNegative)->second.string();
			std::string fileZpositive = files.find(CubeMapPosition::zPositive)->second.string();
			std::string fileZnegative = files.find(CubeMapPosition::zNegative)->second.string();

			// Loads the cube map with the SOIL library, this will create the texture
			_id = SOIL_load_OGL_cubemap(
				fileXpositive.c_str(),
				fileXnegative.c_str(),
				fileYpositive.c_str(),
				fileYnegative.c_str(),
				fileZpositive.c_str(),
				fileZnegative.c_str(),
				SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

			// Bind the Texture and set its default property
			glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureFilterTarget::magFilter), static_cast<GLenum>(TextureFilterMode::linear));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureFilterTarget::minFilter), static_cast<GLenum>(TextureFilterMode::linearMipmapLinear));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureWrappingTarget::wrapS), static_cast<GLenum>(TextureWrappingMode::clampToEdge));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureWrappingTarget::wrapT), static_cast<GLenum>(TextureWrappingMode::clampToEdge));
			glTexParameteri(GL_TEXTURE_CUBE_MAP, static_cast<GLenum>(TextureWrappingTarget::wrapR), static_cast<GLenum>(TextureWrappingMode::clampToEdge));
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}

		CubeMap::~CubeMap()
		{
			// Release the memory in openGL
			if (_id != 0) { glDeleteTextures(1, &_id); }
		}

		void CubeMap::associateWithTextureUnit(GLuint unitNumber) const
		{
			glActiveTexture(GL_TEXTURE0 + unitNumber);
			bind();
		}

#pragma region COPY
		CubeMap::CubeMap(CubeMap&& p_other)
			: _id(p_other._id)
		{
			p_other._id = 0;
		}

		CubeMap& CubeMap::operator= (CubeMap&& p_other)
		{
			_id = p_other._id;
			p_other._id = 0;

			return *this;
		}
#pragma endregion

#pragma region GETTERS
		std::pair<GLenum, GLenum>  CubeMap::textureInternalFormatBaseType(TextureInternalFormat format)
		{
			if (format == TextureInternalFormat::depth || format == TextureInternalFormat::depth16 || format == TextureInternalFormat::depth32) { return { GL_DEPTH_COMPONENT, GL_FLOAT }; }
			if (format == TextureInternalFormat::depthStencil) { return { GL_DEPTH_STENCIL, GL_FLOAT }; }
			if (format == TextureInternalFormat::red || format == TextureInternalFormat::r32f || format == TextureInternalFormat::r16f || format == TextureInternalFormat::r32ui) { return { GL_RED, GL_UNSIGNED_BYTE }; }
			if (format == TextureInternalFormat::rg || format == TextureInternalFormat::rg32f || format == TextureInternalFormat::rg16f || format == TextureInternalFormat::rg32ui) { return { GL_RG, GL_UNSIGNED_BYTE }; }
			if (format == TextureInternalFormat::rgb || format == TextureInternalFormat::rgb32f || format == TextureInternalFormat::rgb16f || format == TextureInternalFormat::rgb32ui) { return { GL_RGB, GL_UNSIGNED_BYTE }; }
			if (format == TextureInternalFormat::rgba || format == TextureInternalFormat::rgba16f || format == TextureInternalFormat::rgba32f || format == TextureInternalFormat::rgba32ui) { return { GL_RGBA, GL_UNSIGNED_BYTE }; }
			assert(false && "textureInternalFormatBaseType called with an invalid parameter");
			throw std::runtime_error("textureInternalFormatBaseType: enum value not found!!!!");
		}

		bool CubeMap::isValid() const {
			return _id != 0;
		}

		GLuint CubeMap::getId() const {
			return _id;
		}
#pragma endregion

#pragma region BINDING
		void CubeMap::bind() const
		{
			assert(isValid() && "CubeMap::bind called but the cube map is not initialized");
			glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
		}

		void CubeMap::unbind() const
		{
			assert(isValid() && "CubeMap::unbind called but the cube map is not initialized");
			glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
		}
#pragma endregion	
}