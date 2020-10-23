#ifndef _GRAPHIC_ENGINE_TEXTURE_2D_HPP_
#define _GRAPHIC_ENGINE_TEXTURE_2D_HPP_

#include <filesystem>
#include <exception>
#include <cassert>
#include <iostream>

#include <GL/glew.h>
#include <SOIL/SOIL.h>

#include <GraphicEngine/Header/GraphicEnum.hpp>

namespace GraphicEngine {
	namespace Textures {
		class Texture2D
		{
		protected:

			/* Identifier of the texture inside openGL*/
			GLuint _id;
			/* Texture dimension */
			GLuint _dimX, _dimY;
			/* Texture internal format */
			TextureInternalFormat _internalFormat;

		public:

			/*
			* Constructor
			* Generates a new empty texture of size width x height, with internal representation in internalFormat.
			* The wrapping is set to clampToEdge and the filtering is set to nearest.
			* 
			* @param p_width : Width of the texture
			* @param p_height : Height of the texture
			* @param p_internalFormat: Internal format of the texture
			*/
			Texture2D(GLuint p_width, GLuint p_height, TextureInternalFormat p_internalFormat);

			/*
			* Constructor
			* Generates a new texture from an image file. The clamping is set to repeat by default.
			* The interpolation is set to linear, except if generateMipmaps is true. In that case, the nim filter
			* if set to linearMipmapLinear (it should be the best quality).
			*
			* @param p_texturePath : Path to the texture
			* @param p_channels : Number of channels for the texture
			* (1 = red, 2 = red/green, 3 = red/green/blue, 4 = red/green/blue/alpha)
			* @param p_generateMipmaps: If set to true generate mipmaps
			*/
			Texture2D(std::filesystem::path p_textureFile, size_t p_channels = 4, bool p_generateMipmaps = false);

			/* Destructor */
			~Texture2D();

			/*
			* Associates this texture to a texture unit
			* @param p_unitNumber : The texture unit number
			*/
			void associateWithTextureUnit(GLuint p_unitNumber) const;

#pragma region COPY
			/*Disallow copying from simple reference*/
			Texture2D(const Texture2D&) = delete;
			Texture2D& operator = (const Texture2D&) = delete;

			/*
			* Move constructor
			* @param p_other : Shader to move
			*/
			Texture2D(Texture2D&& p_other);

			/*
			*  Move assignment
			*  @param p_other : Shader to move
			*/
			Texture2D& operator = (Texture2D&& p_other);
#pragma endregion

#pragma region GETTERS
			/*
			* Determines whether this texture is valid
			* @return true if this texture is valid, else false
			*/
			bool isValid() const;

			/*
			* Gets the texture's identifier in openGL
			* @return texture's identifier
			*/
			GLuint getId() const;

			/*
			* Gets the width of the texture
			* @return texture's width
			*/
			GLuint getWidth() const;

			/*
			* Gets the height of the texture
			* @return texture's height
			*/
			GLuint getHeight() const;

			/*
			* Gets internalFormat types
			* @return pair of texture's internal format and openGL Type
			*/
			std::pair<GLenum, GLenum> textureInternalFormatBaseType(TextureInternalFormat format);
#pragma endregion

#pragma region BINDING
			/*
			* Binds this texture inside openGL
			*/
			void bind() const;

			/*
			* Unbinds this texture in openGL
			*/
			void unbind() const;
#pragma endregion

#pragma region SETTERS
			/*
			* Sets the texture wrapping mode 
			* @param p_target : The wrapping target
			* @param p_mode : The wrapping mode
			*/
			void set(TextureWrappingTarget p_target, TextureWrappingMode p_mode);

			/*
			* Sets the filter mode
			* @param p_target : the filter target
			* @param p_mode : the filter mode
			*/
			void set(TextureFilterTarget p_target, TextureFilterMode p_mode);
#pragma endregion
		};
	}
}

#endif // !_GRAPHIC_ENGINE_TEXTURE_2D_HPP_



