#ifndef _GRAPHIC_ENGINE_SHADER_LOADER_HPP_
#define  _GRAPHIC_ENGINE_SHADER_LOADER_HPP_

#include <map>

#include <GraphicEngine/Shaders/Header/MeshShader.hpp>
#include <GraphicEngine/Shaders/Header/SkyboxShader.hpp>
#include <GraphicEngine/Shaders/Header/VFXShader.hpp>

namespace GraphicEngine::Servers {
		class ShaderServer
		{
		public:
			/* Default mesh shader */
			static const std::string PHONG;
		protected :

			/* The skybox loaded loaded */
			Shaders::SkyboxShader* _skyboxShader;

			/* Loaded custom shader */
			std::map<std::string, Shaders::ShaderProgram*> _customShaders;

			/* Name of the loaded shader used as default for a mesh */
			std::string _defaultMeshShader;
			/* Loaded mesh shader */
			std::map<std::string, Shaders::MeshShader*> _meshShaders;

			/* Loaded VFX shader */
			std::map<std::string, Shaders::VFXShader*> _vfxShaders;

			/*Default Constructor*/
			ShaderServer();


#pragma region COPY
			/*Disallow copying */
			ShaderServer(const ShaderServer&) = delete;
			ShaderServer& operator= (const ShaderServer&) = delete;
#pragma endregion

		public:
			/*
			* Gets the singleton
			* @return a single instance of this class
			*/
			static ShaderServer* getSingleton();

			/*Destructor*/
			~ShaderServer();

			/*
			* Init the server 
			* Call this every time you have reseted GLUT
			*/
			void init();

			/*
			* Clears the server
			* Call this every time before reseted GLUT 
			*/
			void clear();

			/*
			* Load in openGl and register a shader program
			* 
			* @param p_type : The type of the loaded shader
			* @param p_shaderName : The name to which the program will be registered
			* @param p_vertexFile : File containing the vertex shader linked to this program
			* @param p_fragmentFile :  File containing the fragment shader linked to this program
			* @return true if the shader has been loaded, false if it was already registered or couldn't be loaded
			*/
			bool loadAndRegisterShader(ShaderProgramType p_type, std::string p_shaderName, std::string p_vertexFile, std::string p_fragmentFile);

			/* Renders the skybox
			* @param p_view : View matrix
			* @param p_projection : Projection matrix
			*/
			void renderSkybox(const glm::mat4& p_view, const glm::mat4& p_projection);

			void renderScene(){}

			/*
			* Renders a specific mesh with a specified material with this shader
			* Warning the shader must be the one in use and the uniform not related to the material must have been set
			* @param p_shaderName : The name of the shader to render
			* @param p_modelTransform : Transform matrix of the model
			* @param p_meshVAO : The vao related to the mesh we want to render
			* @param p_material : The material to render the mesh with
			*/
			void renderMesh(const std::string p_shaderName, const glm::mat4& p_modelTransform, const Buffers::VertexArrayObject& p_meshVAO, const Materials::PhongMaterial& p_material);

#pragma region GETTERS
			/*
			* Gets the shader use as default for a mesh
			* @return the shader use as default for a mesh
			*/
			std::string getDefaultMeshShader() const;

			/*
			* Gets mesh VertexArrayObject for a specified shader
			* @param p_shaderName : The name of the shader
			* @param p_mesh : The mesh linked to this shader
			* @return a mesh VAO 
			*/
			Buffers::VertexArrayObject* getMeshVAO(std::string p_shaderName, PSceneGraph::Mesh& p_mesh);

			/*
			* Gets skybox texture
			* @return the skybox texture
			*/
			Textures::CubeMap* getSkyboxTexture();
#pragma endregion

#pragma region SETTERS
			/*
			* Sets the shader use as default for a mesh
			* @param p_shader :  New default shader
			* @return true if the shader has been set, false if this shader was not loaded 
			*/
			bool setDefaultMeshShader(std::string p_shader);
#pragma endregion

#pragma region VFX
			/*
			* Initialise the vfx frame buffer attached to the shader 
			* @param p_shader : The shader that contains the frame buffer
			* @param p_configuration : The configuration of each channel of the frame buffer
			* @param p_width : Width of the buffer
			* @param p_height : Height of the buffer
			*/
			void initVFX(std::string p_shader, std::vector<std::tuple<FBOAttachement, FBOAttachmentType, TextureInternalFormat>> p_configuration, size_t p_width, size_t p_height);

			/*
			* Echo the screen resizes to all the vfx shader
			* @param p_width :New width
			* @param p_height : New height
			*/
			void resizeScreen(size_t p_width, size_t p_height);

			/*
			* Binds the texture bind to an attachment of this shader to the screen
			* @param p_shader : The shader to bind to the screen
			* @param p_attachment ; The attachment to bind to
			*/
			void bindScreenTo(std::string p_shader, FBOAttachement p_attachment);

			/*
			* Unbinds any texture from the screen
			*/
			void unbindsScreen();
#pragma endregion

#pragma region BINDING
			/*
			* Use a program as the current program in openGL
			* @param p_name : Name of the program to use 
			* @param p_currentShader [in, out] : Current shader, as the value of the current used shader prog after this function
			*/
			void use(std::string p_name, Shaders::ShaderProgram*& p_currentShader);

			/*
			* Unuse a programs
			* Warning, the passed pointer will be null after a call to this function
			* @param p_currentShader [in, out] : The shader to unuse 
			*/
			void unuse(Shaders::ShaderProgram*& p_currentShader);
#pragma endregion
		};
}

#endif // !_GRAPHIC_ENGINE_SHADER_LOADER_HPP_



