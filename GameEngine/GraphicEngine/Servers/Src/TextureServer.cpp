#include <GraphicEngine/Servers/Header/TextureServer.hpp>

namespace GraphicEngine::Servers {
		TextureServer* TextureServer::getSingleton()
		{
			static TextureServer server;
			return &server;
		}

		Textures::Texture2D* TextureServer::loadTexture(const std::filesystem::path& p_texturePath, size_t p_nbChannels, bool p_generateMipmap)
		{
			// Find a texture already generated
			auto found = _textures.find({ p_texturePath, p_nbChannels, p_generateMipmap });
			if (found != _textures.end()) { return &found->second; }

			//If this texture does not exists, load it and register it to the server
			_textures[{p_texturePath, p_nbChannels, p_generateMipmap}] = Textures::Texture2D(p_texturePath, p_nbChannels, p_generateMipmap);
			return &_textures.find({ p_texturePath, p_nbChannels, p_generateMipmap })->second;
		}

		void TextureServer::clear() {
			_textures.clear();
		}
}