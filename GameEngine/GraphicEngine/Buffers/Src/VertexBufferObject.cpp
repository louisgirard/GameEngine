#include <GraphicEngine/Buffers/Header/VertexBufferObject.hpp>

namespace GraphicEngine::Buffers {
		VertexBufferObject::~VertexBufferObject() {
			// Release buffer memory in openGL
			if (_id != 0) { glDeleteBuffers(1, &_id); }
		}

		void VertexBufferObject::passAsAttribute(GLint p_shaderAttributeIndex, GLuint nbInstances) const
		{
			bind();

			// Register the connexion between the VBO and the shader program
			glEnableVertexAttribArray(p_shaderAttributeIndex);
			glVertexAttribPointer(p_shaderAttributeIndex, dataSize(), glScalarType(), GL_FALSE, 0, nullptr);
			
			// Wait for a certain amount of instances to update content
			if (nbInstances > 0) { glVertexAttribDivisor(p_shaderAttributeIndex, nbInstances); }
		}

#pragma region COPY
		VertexBufferObject::VertexBufferObject(VertexBufferObject&& p_other)
		{
			_id = p_other._id;
			_scalarType = p_other._scalarType;
			_bufferSize = p_other._bufferSize;
			_dataSize = p_other._dataSize;
			p_other._id = 0;
		}

		VertexBufferObject& VertexBufferObject::operator= (VertexBufferObject&& p_other)
		{
			if (_id != 0) { glDeleteBuffers(1, &_id); }
			_id = p_other._id;
			_scalarType = p_other._scalarType;
			_bufferSize = p_other._bufferSize;
			_dataSize = p_other._dataSize;
			p_other._id = 0;

			return *this;
		}
#pragma endregion

#pragma region GETTERS
		bool VertexBufferObject::isValid() const { 
			return _id != 0; 
		}

		GLuint  VertexBufferObject::getId() const { 
			assert(isValid()); 
			return _id; 
		}

		GLenum VertexBufferObject::glScalarType() const { 
			assert(isValid()); 
			return _scalarType; 
		}

		size_t VertexBufferObject::bufferSize() const {
			assert(isValid());
			return _bufferSize;
		}

		unsigned int VertexBufferObject::dataSize() const {
			assert(isValid()); 
			return (unsigned int)_dataSize; 
		}
#pragma endregion

#pragma region BINDING
		void VertexBufferObject::bind() const
		{
			assert(isValid());
			glBindBuffer(GL_ARRAY_BUFFER, _id);
		}

		void VertexBufferObject::unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
#pragma endregion
}