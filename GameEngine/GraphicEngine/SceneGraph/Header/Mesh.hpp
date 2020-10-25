#ifndef _GRAPHIC_ENGINE_MESH_HPP_
#define _GRAPHIC_ENGINE_MESH_HPP_

#include <map>
#include <optional>
#include <filesystem>

#include <glm/gtx/transform.hpp>

#include <GraphicEngine/Header/GraphicEnum.hpp>
#include <GraphicEngine/SceneBase/Header/BoundingBox.hpp>
#include <GraphicEngine/Buffers/Header/VertexArrayObject.hpp>
#include <GraphicEngine/Header/GraphicUtils.hpp>

namespace GraphicEngine::PSceneGraph {
		class Mesh 
		{
		private:

			/* Meshs vertices */
			std::optional<std::vector<glm::vec3>> _vertices;
			/* Meshs normals */
			std::optional<std::vector<glm::vec3>> _normals;
			/* Meshs tangents */
			std::optional<std::vector<glm::vec3>> _tangents;
			/* Meshs bitangents */
			std::optional<std::vector<glm::vec3>> _bitangents;
			/* Meshs texture coordinates */
			std::optional<std::vector<glm::vec2>> _textureCoordinates;
			/* Meshs indices */
			std::optional<std::vector<GLuint>> _indices;

			/* VBO linked to mesh's vertices */
			mutable std::optional<Buffers::VertexBufferObject> _verticesVBO;
			/* VBO linked to mesh's normals */
			mutable std::optional<Buffers::VertexBufferObject> _normalsVBO;
			/* VBO linked to mesh's tangents */
			mutable std::optional<Buffers::VertexBufferObject> _tangentsVBO;
			/* VBO linked to mesh's bitangents */
			mutable std::optional<Buffers::VertexBufferObject> _bitangentsVBO;
			/* VBO linked to texture mesh's coordinate */
			mutable std::optional<Buffers::VertexBufferObject> _textureCoordinatesVBO;
			/* Mesh's EBO */
			mutable std::optional<Buffers::ElementBufferObject> _indicesEBO;

			/* Mesh's bounding box*/
			mutable std::optional<SceneBase::BoundingBox> _boundingBox;

			/* Updates bounding box to fit the mesh */
			void updateBoundingBox() const;

#pragma region Buffers
			/*
			* Create a vbo if needed 
			* 
			* @param p_vbo (out) : The vbo to create
			* @param p_data : Data to pass to the buffer
			*/
			template <typename Type>
			void createVbo(std::optional<Buffers::VertexBufferObject>& p_vbo, const std::vector<Type>& p_data) const
			{
				if (p_vbo) { return; }
				p_vbo = Buffers::VertexBufferObject(p_data);
			}

			/*
			* Updates the vbo if it was created earlier
			* 
			* @param p_vbo : The VBO to update
			* @param p_data : Data to pass the VBO
			*/
			template <typename Type>
			void updateVbo(std::optional<Buffers::VertexBufferObject>& p_vbo, const std::vector<Type>& p_data) const
			{
				if (!p_vbo) { return; }
				(*p_vbo).update(p_data);
			}

			/*
			* Creates the EBO if needed
			*/
			void createEbo() const;
#pragma endregion

		public:

			/*
			* Default constructor
			*/
			Mesh(){}

			/*
			* Forces mesh to have texture coordinate
			*/
			void forceTextureCoordinates();

#pragma region TRANSFORM
			/*
			* Applies a transformation to all vertices and normals of this mesh
			* @param p_transform : The transform to apply
			*/
			void applyTransform(const glm::mat4& p_transform);

			/*
			* Applies a transformation to all vertices and normals of this mesh
			* @param p_transform : The transform to apply
			*/
			void applyTransform(const glm::mat4x3& p_transform);

			/*
			* Transforms the geometry such as its fits the provided bounding box
			* @param p_box : The box to fit
			*/
			void fit(const SceneBase::BoundingBox& box);
#pragma endregion

#pragma region GETTERS
			/*
			* Computes the extend of the geometry
			* @return A bounding box related to this geometry
			*/
			const SceneBase::BoundingBox& boundingBox() const;

			/*
			* Gets the mesh's vertices
			* @return the vertices of the mesh
			*/
			const std::optional<std::vector<glm::vec3>>& getVertices() const;

			/*
			* Gets a pointer to the vertices VBO
			* @return pointer to the vertices VBO
			*/
			const Buffers::VertexBufferObject* getVerticesVbo() const;

			/*
			* Gets the mesh's normals
			* @return the normal of the mesh
			*/
			const std::optional<std::vector<glm::vec3>>& getNormals() const;

			/*
			* Gets a pointer to the normals VBO
			* @return pointer to the normals VBO
			*/
			const Buffers::VertexBufferObject* getNormalsVbo() const;

			/*
			* Gets the mesh's tangents 
			* @return the tangents of the mesh
			*/
			const std::optional<std::vector<glm::vec3>>& getTangents() const;

			/*
			* Gets a pointer to the tangents VBO
			* @return pointer to the tangents VBO
			*/
			const Buffers::VertexBufferObject* getTagentsVbo() const;

			/*
			* Gets the mesh's bitangents
			* 
			* @return the bitangents of the mesh
			*/
			const std::optional<std::vector<glm::vec3>>& getBitangents() const;

			/*
			* Gets a pointer to the bitangents VBO
			* @return a point to the bitangents VBO
			*/
			const Buffers::VertexBufferObject* getBitangentsVbo() const;

			/*
			* Gets the mesh's texture coordinates 
			* @return the texture coordinates of the mesh
			*/
			const std::optional<std::vector<glm::vec2>>& getTextureCoordinates() const;

			/*
			* Gets a pointer to the texture coordinates VBO
			* @return a pointer to the texture coordinates VBO
			*/
			const Buffers::VertexBufferObject* getTextureCoordinatesVbo() const;

			/*
			* Gets the mesh's indices 
			* @return indices of the mesh
			*/
			const std::optional<std::vector<GLuint>>& getIndices() const;

			/*
			* Gets a pointer to the EBO
			* @return a pointer to the EBO
			*/
			const Buffers::ElementBufferObject* getIndicesEbo() const;
#pragma endregion

#pragma region SETTERS
			/*
			* Sets the mesh's vertices
			* @param p_vertices : New vertices
			*/
			void setVertices(const std::vector<glm::vec3>& p_vertices);

			/*
			* Sets the mesh's normals
			* @param p_normals : New normals
			*/
			void setNormals(const std::vector<glm::vec3>& p_normals);

			/*
			* Sets the mesh's tangents
			* @param p_tangents : New tangents
			*/
			void setTangents(const std::vector<glm::vec3>& p_tangents);

			/*
			* Sets the bitangents
			* @param p_bitangents : New bitangents
			*/
			void setBitagents(const std::vector<glm::vec3>& p_bitangents);

			/*
			* Sets the mesh's texture coordinates
			* @param p_textureCoordinates : New texture coordinates
			*/
			void setTextureCoodinates(const std::vector<glm::vec2>& p_textureCoordinates);

			/*
			* Sets the mesh's indices
			* @param p_indices : New indices
			*/
			void setIndices(const std::vector<GLuint>& p_indices);
#pragma endregion
		};
}

#endif // !_GRAPHIC_ENGINE_MESH_HPP_



