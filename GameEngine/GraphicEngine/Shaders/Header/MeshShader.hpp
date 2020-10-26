#pragma once

#include <GraphicEngine/Shaders/Header/ShaderProgram.hpp>
#include <GraphicEngine/Materials/Header/PhongMaterial.hpp>
#include <GraphicEngine/SceneGraph/Header/Mesh.hpp>
#include <GraphicEngine/Textures/Header/CubeMap.hpp>

namespace GraphicEngine::Shaders   {
		class MeshShader : public ShaderProgram
		{
		protected:
			/* Save the attribute default name for a phong shader */
			static const std::string POSITION, NORMAL, TANGENT, BITANGENT, TEXTURECOORD;
			static const std::string MODEL, VIEW, PROJECTION, NORMALMATRX;
			static const std::string EMISSIVE, AMBIENT, DIFFUSE, SPECULAR, SHININESS;
			static const std::string DIFFUSETEXT, SPECULARTEXT, NORMALTEXT, ENVIRONMENTTEXT;
			static const std::string VIEW_POSITION, LIGHT_DIRECTION, LIGHT_COLOR, CLIPPING_DISTANCE;

			/* Saves the attribute identifier */
			GLint _inPosition, _inNormal, _inTangent, _inBitangent, _inTextureCoordinate;
			GLint _uniModelMatrix, _uniViewMatrix, _uniProjectionMatrix, _uniNormalMatrix;
			GLint _uniEmissiveColor, _uniAmbientColor, _uniDiffuseColor, _uniSpecularColor, _uniShininess;
			GLint _uniDiffuseTexture, _uniSpecularTexture, _uniNormalTexture, _uniEnvironmentTexture;
			GLint _uniViewPos, _uniLightDir, _uniLightColor, _uniClippingDistance;

			/* Saves a view matrix associated with this shader (to help with setting new model)*/
			glm::mat4 _view;
		
#pragma region INITIALIZATION
			/* Init this shader */
			void initialise();
#pragma endregion
			
		public:
#pragma region INITIALIZATION
			/* Default Constructor */
			MeshShader();

			/*
			* Constructor
			* Initialize a program shader with a vertex and a fragment shader
			* @param p_vertex : Vertex shader to attach to this program
			* @param p_fragment : Fragment shader to attach to this program
			*/
			MeshShader(const Shader& p_vertex, const Shader& p_fragment);

			/*
			* Constructor
			* Initialize a program shader with a vertex and a fragment shader
			* @param p_vertexPath : Path to the vertex shader to attach to this program
			* @param p_fragmentPath : Path ot the fragment shader to attach to this program
			*/
			MeshShader(const std::filesystem::path& p_vertexPath, const std::filesystem::path& p_fragmentPath);
#pragma endregion

			/*
			* Renders a specific mesh with a specified material with this shader
			* @param p_meshVAO : The vao related to the mesh we want to render
			* @param p_material : The material to render the mesh with
			*/
			void renderMesh(const Buffers::VertexArrayObject& p_meshVAO, const Materials::PhongMaterial& p_material);

#pragma region COPY
			/*
			* Move constructor
			* @param p_other : Shader to move
			*/
			MeshShader(MeshShader&& p_other);

			/*
			*  Move assignment
			*  @param p_other : Shader to move
			*/
			virtual MeshShader& operator= (MeshShader&& p_other);

#pragma endregion

#pragma region GETTERS
			/*
			* Gets a mesh VAO linked to this shader
			* @param p_mesh : New mesh input
			*/
			virtual Buffers::VertexArrayObject* getMeshVAO(const PSceneGraph::Mesh& p_mesh);
#pragma endregion

#pragma region SETTERS
			/*
			* Sets the material associated with this shader.
			* Note that this method verifies the capabilities of the shader before trying to set any uniform.
			* @param p_material : New material
			*/
			virtual void setMaterial(const Materials::PhongMaterial& p_material) const;

			/*
			* Sets the transforms associated with this shader.
			* Note that the shader verifies the capabilities of the shader before setting transforms
			* @param p_model : New model matrix 
			* @param p_view : New view matrix
			* @param p_projection : New projection matrix
			*/
			virtual void setTransforms(const glm::mat4& p_model, const glm::mat4& p_view, const glm::mat4& p_projection);

			/*
			* Sets the transforms associated with a model.
			* @param p_model : New model matrix
			*/
			virtual void setModelTransform(const glm::mat4& p_model);

			/*
			* Sets the transforms associated with a camera.
			* @param p_view : New view matrix
			*/
			virtual void setViewTransform(const glm::mat4& p_view);

			/*
			* Sets the transforms associated with a projection.
			* @param p_projection : New projection matrix
			*/
			virtual void setProjectionTransform(const glm::mat4& p_projection);

			/*
			* Sets the light option
			* @param p_direction : Light's direction
			* @param p_color : Light's color
			*/
			virtual void setLights(glm::vec3 p_direction, glm::vec3 p_color);

			/*
			* Sets the viewer position
			* @param p_position : Viewer current position
			*/
			virtual void setViewPosition(glm::vec3 p_position);

			/*
			* Sets the clipping distance 
			* @param p_distance : New clipping distance
			*/
			virtual void setClippingDistance(float p_distance);

			/*
			* Sets the environment texture
			* @param p_texture : New environment texture
			*/
			virtual void setEnvTexture(Textures::CubeMap* p_texture);
#pragma endregion
		};
}




