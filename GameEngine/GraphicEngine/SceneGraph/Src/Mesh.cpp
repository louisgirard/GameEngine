#include <GraphicEngine/SceneGraph/Header/Mesh.hpp>

namespace GraphicEngine::PSceneGraph {
	void Mesh::updateBoundingBox() const
	{
		assert(_vertices && "Mesh::updateBoundingBox called with no vertices in the mesh");

		// Verify bounding box has been activated
		if (_boundingBox) { return; }

		_boundingBox = SceneBase::BoundingBox();
		// Add every vertices from mesh in the bounding box
		(*_boundingBox).update((*_vertices).begin(), (*_vertices).end());
	}

	void Mesh::forceTextureCoordinates()
	{
		if (!getTextureCoordinates()) {
			_textureCoordinatesVBO.reset();
			std::vector<glm::vec2> textureCoordinate;
			std::fill(textureCoordinate.begin(), textureCoordinate.end(), glm::vec2(0, 0));
			_textureCoordinates = textureCoordinate;
		}
	}

#pragma region Buffers
	void Mesh::createEbo() const
	{
		if (_indicesEBO) { return; }
		_indicesEBO = Buffers::ElementBufferObject(*_indices);
	}
#pragma endregion

#pragma region TRANSFORM
	void Mesh::applyTransform(const glm::mat4& p_transform)
	{
		if (_vertices)
		{
			GraphicEngine::applyTransform(p_transform, *_vertices);
			updateVbo(_verticesVBO, *_vertices);
			_boundingBox.reset();
		}
		if (_normals)
		{
			// Update matrix to compute normal transform
			glm::mat3 normalTransform = glm::transpose(inverse(glm::mat3(p_transform)));
			GraphicEngine::applyTransform(normalTransform, *_normals);
			updateVbo(_normalsVBO, *_normals);
		}
	}

	void Mesh::applyTransform(const glm::mat4x3& p_transform)
	{
		if (_vertices)
		{
			GraphicEngine::applyTransform(p_transform, *_vertices);
			updateVbo(_verticesVBO, *_vertices);
			_boundingBox.reset();
		}
		if (_normals)
		{
			glm::mat3 normalTransform = glm::transpose(inverse(glm::mat3(p_transform)));
			GraphicEngine::applyTransform(normalTransform, *_normals);
			updateVbo(_normalsVBO, *_normals);
		}
	}

	void Mesh::fit(const SceneBase::BoundingBox& box)
	{
		SceneBase::BoundingBox thisBB = boundingBox();

		glm::mat4 transform = glm::translate(box.center()) * glm::scale(box.extent() / boundingBox().extent()) * glm::translate(-thisBB.center());
		applyTransform(transform);
	}
#pragma endregion

#pragma region GETTERS
	const SceneBase::BoundingBox& Mesh::boundingBox() const
	{
		updateBoundingBox();
		return *_boundingBox;
	}

	const std::optional<std::vector<glm::vec3>>& Mesh::getVertices() const {
		return _vertices;
	}

	const Buffers::VertexBufferObject* Mesh::getVerticesVbo() const
	{
		assert(_vertices && "Mesh::getVerticesVbo called with no vertices in the mesh");
		createVbo(_verticesVBO, *_vertices);
		return &(*_verticesVBO);
	}

	const std::optional<std::vector<glm::vec3>>& Mesh::getNormals() const {
		return _normals;
	}

	const Buffers::VertexBufferObject* Mesh::getNormalsVbo() const
	{
		assert(_normals && "Mesh::getNormalsVbo called with no normals in the mesh");
		createVbo(_normalsVBO, *_normals);
		return &(*_normalsVBO);
	}

	const std::optional<std::vector<glm::vec3>>& Mesh::getTangents() const {
		return _tangents;
	}

	const Buffers::VertexBufferObject* Mesh::getTagentsVbo() const
	{
		assert(_tangents && "Mesh::getTagentsVbo called with no tangents in the mesh");
		createVbo(_normalsVBO, *_normals);
		return &(*_normalsVBO);
	}

	const std::optional<std::vector<glm::vec3>>& Mesh::getBitangents() const {
		return _bitangents;
	}

	const Buffers::VertexBufferObject* Mesh::getBitangentsVbo() const
	{
		assert(_bitangents && "Mesh::getBitangentsVbo called with no bitangents in the mesh");
		createVbo(_bitangentsVBO, *_bitangents);
		return &(*_bitangentsVBO);
	}

	const std::optional<std::vector<glm::vec2>>& Mesh::getTextureCoordinates() const {
		return _textureCoordinates;
	}

	const Buffers::VertexBufferObject* Mesh::getTextureCoordinatesVbo() const
	{
		assert(_textureCoordinates && "Mesh::getTextureCoordinatesVbo called with no texture coordinates in the mesh");
		createVbo(_textureCoordinatesVBO, *_textureCoordinates);
		return &(*_textureCoordinatesVBO);
	}

	const std::optional<std::vector<GLuint>>& Mesh::getIndices() const {
		return _indices;
	}

	const Buffers::ElementBufferObject* Mesh::getIndicesEbo() const
	{
		assert(_indices && "Mesh::getIndicesEbo called with no indices in the mesh");
		createEbo();
		return &(*_indicesEBO);
	}
#pragma endregion

#pragma region SETTERS
	void Mesh::setVertices(const std::vector<glm::vec3>& p_vertices)
	{
		_boundingBox.reset();
		_verticesVBO.reset();
		_vertices = p_vertices;
	}

	void Mesh::setNormals(const std::vector<glm::vec3>& p_normals)
	{
		_normalsVBO.reset();
		_normals = p_normals;
	}

	void Mesh::setTangents(const std::vector<glm::vec3>& p_tangents)
	{
		_tangentsVBO.reset();
		_tangents = p_tangents;
	}

	void Mesh::setBitagents(const std::vector<glm::vec3>& p_bitangents)
	{
		_tangentsVBO.reset();
		_bitangents = p_bitangents;
	}

	void Mesh::setTextureCoodinates(const std::vector<glm::vec2>& p_textureCoordinates)
	{
		_textureCoordinatesVBO.reset();
		_textureCoordinates = p_textureCoordinates;
	}

	void Mesh::setIndices(const std::vector<GLuint>& p_indices)
	{
		_indicesEBO.reset();
		_indices = p_indices;
	}
#pragma endregion
}