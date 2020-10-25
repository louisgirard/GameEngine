#include <GraphicEngine/Textures/Header/Texture2D.hpp>

namespace GraphicEngine::Textures {

		Texture2D::Texture2D(GLuint p_width, GLuint p_height, TextureInternalFormat p_internalFormat)
		{
			 _internalFormat = p_internalFormat;
			// We store the dimensions of the texture
			_dimX = p_width;
			_dimY = p_height;
			
			//Generate the texture inside openGL
			glGenTextures(1, &_id);
			glBindTexture(GL_TEXTURE_2D, _id);

			// Get Format information
			std::pair<GLenum, GLenum> internalFormatInfo = textureInternalFormatBaseType(_internalFormat);
			// Create texture in openGL
			glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLenum>(_internalFormat), _dimX, _dimY, 0, static_cast<GLenum>(internalFormatInfo.first), static_cast<GLenum>(internalFormatInfo.second), nullptr);
			
			// We set the default texture options
			set(TextureWrappingTarget::wrapS, TextureWrappingMode::clampToEdge);
			set(TextureWrappingTarget::wrapT, TextureWrappingMode::clampToEdge);
			set(TextureFilterTarget::minFilter, TextureFilterMode::nearest);
			set(TextureFilterTarget::magFilter, TextureFilterMode::nearest);
			
			// We unbind the texture
			glBindTexture(GL_TEXTURE_2D, 0);
			
		}

		Texture2D::Texture2D(std::filesystem::path p_textureFile, size_t p_channels, bool p_generateMipmaps)
		{

			// Verify channels number is supported in engine
			assert(p_channels <= 4 && p_channels > 0);

			// Get internal format from channel number
			switch (p_channels)
			{
			case 1:
				_internalFormat = TextureInternalFormat::red;
				break;
			case 2:
				_internalFormat = TextureInternalFormat::rg;
				break;
			case 3:
				_internalFormat = TextureInternalFormat::rgb;
				break;
			case 4:
				_internalFormat = TextureInternalFormat::rgba;
				break;
			}

			// Verify the path lead to the texture
			if (!std::filesystem::exists(p_textureFile))
			{
				std::cerr << "Texture2D: could not find texture " << p_textureFile.string() << std::endl;
				throw std::ios_base::failure("Texture2D: " + std::string("File ") + p_textureFile.string() + " not found.");
			}

			// Get the texture with SOIL
			// Set mipmap options
			size_t flag = SOIL_FLAG_POWER_OF_TWO;
			if (p_generateMipmaps) { flag = flag | SOIL_FLAG_MIPMAPS; }
			// Load texture
			_id = SOIL_load_OGL_texture(p_textureFile.string().c_str(), (int)p_channels, 0, (unsigned int)flag);
			// Verify the texture has been loaded correctly
			if (_id == 0)
			{
				std::cerr << "Texture2D: SOIL could not load texture:" << p_textureFile.string() << std::endl;
				throw std::ios_base::failure("Texture2D: SOIL library is unable to load file " + p_textureFile.string());
			}

			bind();
			// Set default Texture options
			set(TextureWrappingTarget::wrapS, TextureWrappingMode::repeat);
			set(TextureWrappingTarget::wrapT, TextureWrappingMode::repeat);
			if (!p_generateMipmaps)
			{
				set(TextureFilterTarget::minFilter, TextureFilterMode::linear);
			}
			else
			{
				set(TextureFilterTarget::minFilter, TextureFilterMode::linearMipmapLinear); // Best quality
			}
			set(TextureFilterTarget::magFilter, TextureFilterMode::linear);
			
			// Retrieves the dimensions of the texture
			GLint sizeX, sizeY;
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &sizeX);
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &sizeY);
			_dimX = sizeX;
			_dimY = sizeY;

			unbind();
		}

		Texture2D::~Texture2D()
		{
			// Release memory in openGL
			if (_id != 0) glDeleteTextures(1, &_id);
		}

		void Texture2D::associateWithTextureUnit(GLuint p_unitNumber) const
		{
			glActiveTexture(GL_TEXTURE0 + p_unitNumber);
			bind();
		}

#pragma region COPY
		Texture2D::Texture2D(Texture2D&& p_other)
		{
			_id = p_other._id;

			_dimX = p_other._dimX;
			_dimY = p_other._dimY;
			_internalFormat = p_other._internalFormat;

			p_other._id = 0;
		}

		Texture2D& Texture2D::operator = (Texture2D&& p_other)
		{
			if (_id != 0) glDeleteTextures(1, &_id);

			_id = p_other._id;
			_dimX = p_other._dimX;
			_dimY = p_other._dimY;
			_internalFormat = p_other._internalFormat;
			p_other._id = 0;

			return *this;
		}
#pragma endregion

#pragma region GETTERS
		bool Texture2D::isValid() const { 
			return _id != 0; 
		}

		GLuint Texture2D::getId() const { 
			assert(isValid());
			return _id;
		}

		GLuint Texture2D::getWidth() const { 
			return _dimX; 
		}

		GLuint Texture2D::getHeight() const { 
			return _dimY; 
		}

		std::pair<GLenum, GLenum>  Texture2D::textureInternalFormatBaseType(TextureInternalFormat format)
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
#pragma endregion

#pragma region BINDING
		void Texture2D::bind() const
		{
			assert(isValid());
			glBindTexture(GL_TEXTURE_2D, _id);
		}

		void Texture2D::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
#pragma endregion

#pragma region SETTERS
		void Texture2D::set(TextureWrappingTarget p_target, TextureWrappingMode p_mode)
		{
			assert(isValid());
			bind();
			glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(p_target), static_cast<GLenum>(p_mode));
			unbind();
		}

		void Texture2D::set(TextureFilterTarget p_target, TextureFilterMode p_mode)
		{
			assert(isValid());
			bind();
			glTexParameteri(GL_TEXTURE_2D, static_cast<GLenum>(p_target), static_cast<GLenum>(p_mode));
			unbind();
		}
#pragma endregion

}