#pragma once

#include <GraphicEngine/Header/GraphicConfig.hpp>
#include <GraphicEngine/Shaders/Header/ShaderProgram.hpp>
#include <GraphicEngine/Textures/Header/CubeMap.hpp>
#include <GraphicEngine/SceneBase/Header/SkyboxGeometry.hpp>

namespace GraphicEngine::Shaders {
		class SkyboxShader : public ShaderProgram
		{
		protected:

			static const std::string CUBE_MAP, VIEW, PROJECTION;

			GLint _uniViewMatrix, _uniProjectionMatrix, _uniskybox;

			Textures::CubeMap* _texture;

#pragma region INITIALIZATION
			/* Init this shader */
			void initialise();
#pragma endregion

		public:
#pragma region INITIALIZATION
			/* Default Constructor */
			SkyboxShader();

			/*
			* Constructor
			* Initialize a program shader with a vertex and a fragment shader
			* @param p_vertex : Vertex shader to attach to this program
			* @param p_fragment : Fragment shader to attach to this program
			*/
			SkyboxShader(const Shader& p_vertex, const Shader& p_fragment);

			/*
			* Constructor
			* Initialize a program shader with a vertex and a fragment shader
			* @param p_vertexPath : Path to the vertex shader to attach to this program
			* @param p_fragmentPath : Path ot the fragment shader to attach to this program
			*/
			SkyboxShader(const std::filesystem::path& p_vertexPath, const std::filesystem::path& p_fragmentPath);
#pragma endregion

			/* Destructor */
			~SkyboxShader();

			/* Render the shader */
			void render();

#pragma region COPY
			/*
			* Move constructor
			* @param p_other : Shader to move
			*/
			SkyboxShader(SkyboxShader&& p_other);

			/*
			*  Move assignment
			*  @param p_other : Shader to move
			*/
			virtual SkyboxShader& operator= (SkyboxShader&& p_other);
#pragma endregion

#pragma region GETTERS
			/*
			* Gets skybox tetxure
			* @return the skybox texture
			*/
			Textures::CubeMap* getTexture() const;
#pragma endregion


#pragma region SETTERS
			/*
			* Sets the transforms associated with this shader.
			* Note that the shader verifies the capabilities of the shader before setting transforms
			* @param p_view : New view matrix
			* @param p_projection : New projection matrix
			*/
			virtual void setTransforms(const glm::mat4& p_view, const glm::mat4& p_projection);

			/*
			* Sets the skybox texture.
			* @param p_texture : New texture
			*/
			virtual void setTexture(Textures::CubeMap* p_texture);
#pragma endregion
		};
}


