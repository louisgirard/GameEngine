#ifndef _GRAPHIC_ENGINE_TEXTURE_SERVER_HPP_
#define _GRAPHIC_ENGINE_TEXTURE_SERVER_HPP_

#include <map>
#include <tuple>

#include <GraphicEngine/Textures/Header/Texture2D.hpp>

namespace GraphicEngine::Servers {
		class TextureServer
		{
		protected:
			/* Map texture with their path and option */
			std::map<std::tuple<std::filesystem::path, size_t, bool>, Textures::Texture2D> _textures;

			/* Default Constuctor */
			TextureServer() {}

#pragma region COPY
			/*Disallow copying */
			TextureServer(const TextureServer&) = delete;
			TextureServer& operator= (const TextureServer&) = delete;
#pragma endregion

		public:
			/*
			* Gets the singleton
			* @return a single instance of this class
			*/
			static TextureServer* getSingleton();

			/*
			* Loads a texture if necessary and return a pointer to it
			* @param p_texturePath : The path to the texture
			* @param p_nbChannels : The number of channels inside the texture
			* @param p_generateMipmap : if true generate texture's mipmap
			*/
			Textures::Texture2D* loadTexture(const std::filesystem::path& p_texturePath, size_t p_nbChannels = 4, bool p_generateMipmap = false);

			/*
			* Clear the server
			* Call this every time you want to reste GLUT
			*/
			void clear();
		};
}

#endif // !_GRAPHIC_ENGINE_TEXTURE_SERVER_HPP_



