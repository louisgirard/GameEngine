#ifndef _GRAPHIC_ENGINE_GRAPHIC_CONFIG_HPP_
#define _GRAPHIC_ENGINE_GRAPHIC_CONFIG_HPP_

#include <unordered_map>

#include <GraphicEngine/Header/GraphicEnum.hpp>
#include <Games/Header/DefaultConfig.hpp>

/**
* File used to define default graphic options
**/
namespace GraphicEngine {

	/*
	* Gets path to a default white texture
	* @return path to a default white texture
	*/
	inline std::filesystem::path defaultWhiteTexture() { return Games::dataPath() / "textures" / "default" / "white.png"; }

	/*
	* Gets path to a default black texture
	* @return path to a default black texture
	*/
	inline std::filesystem::path defaultBlackTexture() { return Games::dataPath() / "textures" / "default" / "black.png"; }

	/*
	* Gets path to a default normal texture
	* @return path to a default normal texture
	*/
	inline std::filesystem::path defaultNormalMap() { return Games::dataPath() / "textures" / "default" / "normals.png"; }

	/*
	* Gets path to a default shader directory
	* @return path to a default shader directory
	*/
	inline std::filesystem::path defaultShaderPath() { return  Games::dataPath() / "Shaders"; }

	/*
	* Gets path to a default phong vertex shader
	* @return path to a default phong vertex shader 
	*/
	inline std::filesystem::path defaultPhongVertex() { return defaultShaderPath() / "PhongDirectional.vert"; }

	/*
	* Gets path to a default phong fragment shader
	* @return path to a default phong fragment shader
	*/
	inline std::filesystem::path defaultPhongFragment() { return defaultShaderPath() / "PhongDirectional.frag"; }

	/*
	* Gets path to a default skybox vertex shader
	* @return path to a default skybox vertex shader
	*/
	inline std::filesystem::path defaultSkyboxVertex() { return defaultShaderPath() / "skybox.vert"; }

	/*
	* Gets path to a default skybox fragment shader
	* @return path to a default skybox fragment shader
	*/
	inline std::filesystem::path defaultSkyboxFragment() { return defaultShaderPath() / "skybox.frag"; }

	/*
	* Gets path to default skybox textures
	* @return path to default skybox textures
	*/
	inline std::unordered_map<CubeMapPosition, std::filesystem::path> defaultSkyboxTextures() {
		std::filesystem::path skyboxPath = Games::dataPath() / "textures" / "cubemaps" / "sky";
		std::unordered_map<CubeMapPosition, std::filesystem::path> files =
		{
			{ CubeMapPosition::front,  skyboxPath / "cloudtop_ft.jpg"},
			{ CubeMapPosition::back,  skyboxPath / "cloudtop_bk.jpg"},
			{ CubeMapPosition::left,  skyboxPath / "cloudtop_lf.jpg"},
			{ CubeMapPosition::right,  skyboxPath / "cloudtop_rt.jpg"},
			{ CubeMapPosition::bottom,  skyboxPath / "cloudtop_dn.jpg"},
			{ CubeMapPosition::top,  skyboxPath / "cloudtop_up.jpg"}
		};
		return files;
	}

}

#endif // !_GRAPHIC_ENGINE_GRAPHIC_CONFIG_HPP_