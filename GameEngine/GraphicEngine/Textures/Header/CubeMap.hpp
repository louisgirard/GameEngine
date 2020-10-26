#pragma once

#include <GraphicEngine/Header/GraphicEnum.hpp>

#include <unordered_map>
#include <cassert>
#include <filesystem>

#include <SOIL/SOIL.h>

namespace GraphicEngine::Textures {
		class CubeMap
		{
		protected:
			/* Texture identifier in openGL*/
			GLuint _id;

			/*
			* Verify if a provided texture exists
			* @param p_textureFile : File name of the texture
			* @param p_entry : Position of the texture inside the cube map
			*/
			static bool exists(const std::unordered_map<CubeMapPosition, std::filesystem::path>& p_texturesFile, CubeMapPosition p_entry);

#pragma region GETTERS
			/*
			* Gets internalFormat types
			* @return pair of texture's internal format and openGL Type
			*/
			std::pair<GLenum, GLenum> textureInternalFormatBaseType(TextureInternalFormat format);
#pragma endregion

		public:
			
			/*
			* Constructor
			* Constructs a cube map of the provided internal format
			* 
			* @param p_width : The width of a face texture
			* @param p_height : The height of a face texture
			* @param p_format : The internal format of the cube map textures
			*/
			CubeMap(GLuint p_width, GLuint p_height, TextureInternalFormat p_format);

			/*
			* Constructor 
			* Constructs  a cube map texture based on texture files
			* 
			* @param p_files : The files names
			*/
			CubeMap(const std::unordered_map<CubeMapPosition, std::filesystem::path>& files);

			/* Destructor */
			~CubeMap();

			/*
			* Associates this cube map texture to a texture unit 
			* Warning, the texture is bind after this function
			* @param p_unitNumber : The texture unit number to associate to
			*/
			void associateWithTextureUnit(GLuint unitNumber) const;

#pragma region COPY
			/*Disallow copying from simple reference*/
			CubeMap(const CubeMap&) = delete;
			CubeMap& operator= (const CubeMap&) = delete;

			/*
			* Move constructor
			* @param p_other : Texture to move
			*/
			CubeMap(CubeMap&& p_other);

			/*
			*  Move assignment
			*  @param p_other : Texture to move
			*/
			CubeMap& operator= (CubeMap&& p_other);
#pragma endregion

			
#pragma region GETTERS
			/*
			* Determines whether the cube map is valid
			* @return true if this texture is valid, else false
			*/
			bool isValid() const;

			/*
			* Gets the identifier of the cube map texture in openGL
			* @return the identifier of the texture 
			*/
			GLuint getId() const;
#pragma endregion

#pragma region BINDING
			/*
			* Binds this cube map in openGL
			*/
			void bind() const;

			/*
			* Unbinds this cube maap in openGL
			*/
			void unbind() const;
#pragma endregion
		};
}



