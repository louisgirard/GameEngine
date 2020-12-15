#pragma once

#include <SceneGraph/Header/EmptyNode.hpp>
#include <GraphicEngine/SceneGraph/Header/PMeshObject.hpp>

namespace PhysicEngine::Collisions { class Collider;}
using PhysicEngine::Collisions::Collider;

namespace SceneGraph {
	class CMeshObject : public EmptyNode
	{
	protected:
		std::shared_ptr<GraphicEngine::PSceneGraph::PMeshObject> _presentation;

		std::vector<std::shared_ptr<Collider>> _colliders;

	public:

		/*Default constructor*/
		CMeshObject() : EmptyNode(), _presentation(std::make_shared<GraphicEngine::PSceneGraph::PMeshObject>()){}

		/*
		* Constructor
		* @param p_mesh : Mesh attached
		* @param p_material : Material attached
		* @param p_shaderName : The name of the shader to attach
		* @param p_attributes : The attributes to get from the mesh
		* @param p_forcesTexture : true if the mesh attached to this object needs to have texture coordinates
		*/
		CMeshObject(GraphicEngine::PSceneGraph::Mesh* p_mesh, std::shared_ptr<GraphicEngine::Materials::PhongMaterial> p_material, std::string p_shaderName, bool p_forcesTexture = false);

		std::vector<std::shared_ptr<Collider>> getColliders();

		/*
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		*/
		virtual void draw(std::string p_shaderName);

		/*
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		* @param p_transform : transformation matrix
		*/
		virtual void draw(std::string p_shaderName, glm::mat4 p_transform);

		/*
		* Compute a bounding box for this node and its child
		* @return a bounding box encompassing the scene contained in this node
		*/
		virtual GraphicEngine::SceneBase::BoundingBox computeSceneBoundingBox();

#pragma region GETTERS
		/*
		* Gets the mesh attached to this object
		* @return a mesh attached to this node
		*/
		GraphicEngine::PSceneGraph::Mesh* getMesh() const;

		/*
		* Gets the material attached to this object
		* @return a material atteched to this object
		*/
		std::shared_ptr<GraphicEngine::Materials::PhongMaterial> getMaterial() const;
#pragma endregion

#pragma region SETTERS
		/*
		* Sets a mesh
		* @param p_mesh : New mesh
		*/
		void setMesh(GraphicEngine::PSceneGraph::Mesh* p_mesh);

		/*
		* Sets a material
		* @param p_material : New material
		*/
		void setMaterial(std::shared_ptr<GraphicEngine::Materials::PhongMaterial> p_material);

		/*
		* Register the shader to render this object
		* @param p_shaderName : Name of the new shader
		*/
		void registerShader(std::string p_shaderName);
#pragma endregion
	};
}



