#pragma once

#include <GraphicEngine/Servers/Header/ShaderServer.hpp>

namespace GraphicEngine::PSceneGraph {
		class PMeshObject
		{
		protected:

			/* Mesh attached to this object */
			Mesh* _mesh;
			/* Material attached to this material */
			std::shared_ptr<Materials::PhongMaterial> _material;
			/* Shader program used to render the object in openGL  */
			std::string _shaderName;

			/* VAO linked to the mesh and shader attached*/
			Buffers::VertexArrayObject* _VAO;

			/* Determines whether the mesh need to have texture coordinate in any case*/
			bool _forcesTextureCoordinate;

		public:

			/* Default Constructor */
			PMeshObject();

			/*
			* Constructor
			* @param p_mesh : Mesh to attach
			* @param p_material : Material to attach
			* @param p_shaderName : The name of the shader to attach
			* @param p_forcesTextures : true if mesh should have texture coordinate
			*/
			PMeshObject(Mesh* p_mesh, std::shared_ptr<Materials::PhongMaterial> p_material, std::string p_shaderName, bool p_forcesTextures);

			/* Destructor */
			~PMeshObject();

			/*
			* Draws this node
			* @param p_shaderName : Name of the shader we are using now to render the node
			*/
			void draw(std::string p_shaderName);

			/*
			* Compute a bounding box for this node and its child
			* @return a bounding box encompassing the scene contained in this node
			*/
			SceneBase::BoundingBox computeSceneBoundingBox();

#pragma region GETTERS
			/*
			* Gets the mesh attached to this object
			* @return a mesh attached to this node
			*/
			Mesh* getMesh() const;

			/*
			* Gets the material attached to this object
			* @return a material atteched to this object
			*/
			std::shared_ptr<Materials::PhongMaterial> getMaterial() const;

			/*
			* Gets the name of the shader attached to this object
			* @return the name of the shader attache to this object
			*/
			std::string getShaderName() const;
#pragma endregion

#pragma region SETTERS
			/*
			* Sets a mesh 
			* @param p_mesh : New mesh
			*/
			void setMesh(Mesh* p_mesh);

			/*
			* Sets a material 
			* @param p_material : New material
			*/
			void setMaterial(std::shared_ptr<Materials::PhongMaterial> p_material);

			/*
			* Register the shader to render this object
			* @param p_shaderName : Name of the new shader
			*/
			void registerShader(std::string p_shaderName);
#pragma endregion
		};
}



