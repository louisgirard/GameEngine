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
	* Handle openGL error
	*/
	inline void handleGLerror(std::string p_functionName) {
		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			std::string log = p_functionName ;
			switch (error) {
			case GL_INVALID_ENUM:
				log += " : GL error, an unacceptable value is specified for an enumerated argument. The offending command is ignored";
				break;
			case GL_INVALID_VALUE:
				log += " : GL error, a numeric argument is out of range. The offending command is ignored";
				break;
			case GL_INVALID_OPERATION:
				log += " : GL error, the previous operation is not allowed in the current state. The offending command is ignored";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				log += " : GL error, the framebuffer object is not complete. The offending command is ignored";
				break;
			case GL_OUT_OF_MEMORY:
				log += " : GL error, there is not enough memory left to execute the command. The state of the GL is undefined";
				break;
			case GL_STACK_UNDERFLOW:
				log += " : GL error, an attempt has been made to perform an operation that would cause an internal stack to underflow";
				break;
			case GL_STACK_OVERFLOW:
				log += " : GL error, an attempt has been made to perform an operation that would cause an internal stack to overflow";
				break;
			default:
				log += " : GL error unhandled";
				break;
			}
			std::cout << log << std::endl;
		}
	}

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