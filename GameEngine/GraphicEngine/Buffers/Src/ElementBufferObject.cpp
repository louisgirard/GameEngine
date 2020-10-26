#include <GraphicEngine/Buffers/Header/ElementBufferObject.hpp>

namespace GraphicEngine::Buffers {
	ElementBufferObject::ElementBufferObject(const std::vector<GLuint>& p_indices, BufferUpdate p_usage)
	{
		// Creation of the element buffer object
		glGenBuffers(1, &_id);

		// Initialization of the element buffer object in openGL
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * p_indices.size(), p_indices.data(), static_cast<GLenum>(p_usage));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		_size = p_indices.size();
	}

	ElementBufferObject::~ElementBufferObject()
	{
		//Release memory in openGL
		if (_id != 0) { glDeleteBuffers(1, &_id); }
	}

#pragma region COPY
	ElementBufferObject::ElementBufferObject(ElementBufferObject&& p_other)
	{
		_id = p_other._id;
		_size = p_other._size;
		p_other._id = 0;
	}

	ElementBufferObject& ElementBufferObject::operator= (ElementBufferObject&& p_other)
	{
		if (_id != 0) { glDeleteBuffers(1, &_id); }

		_id = p_other._id;
		_size = p_other._size;
		p_other._id = 0;

		return *this;
	}
#pragma endregion

#pragma region GETTERS
	bool ElementBufferObject::isValid() const {
		return _id != 0;
	}

	GLuint ElementBufferObject::getId() const {
		assert(isValid() && "ElementBufferObject::getId called but the EBO is not initialized");
		return _id;
	}

	GLenum ElementBufferObject::glElementType() const {
		assert(isValid() && "ElementBufferObject::glElementType called but the EBO is not initialized");
		return GL_UNSIGNED_INT;
	}

	size_t ElementBufferObject::size() const {
		assert(isValid() && "ElementBufferObject::size called but the EBO is not initialized");
		return _size;
	}
#pragma endregion

#pragma region BINDING
	void ElementBufferObject::bind() const
	{
		assert(isValid() && "ElementBufferObject::bind called but the EBO is not initialized");
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}

	void ElementBufferObject::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
#pragma endregion
}