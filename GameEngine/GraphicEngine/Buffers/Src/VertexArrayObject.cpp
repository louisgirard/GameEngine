#include <GraphicEngine/Buffers/Header/VertexArrayObject.hpp>

namespace GraphicEngine {
	namespace Buffers {
		VertexArrayObject::VertexArrayObject(const std::vector<std::pair<GLint, const VertexBufferObject*>>& p_vbos, const ElementBufferObject* p_ebo = nullptr)
		{
			// Creation and binding of the VAO
			glGenVertexArrays(1, &_id);
			glBindVertexArray(_id);

			// Association of VBOS with the VAO and the shader program
			for (auto it = p_vbos.begin(), end = p_vbos.end(); it != end; ++it)
			{
				const std::pair<GLuint, const VertexBufferObject*>& current = (*it);
				// Pass the vbo as an attribute in the shader program
				current.second->passAsAttribute(current.first);
			}

			// Association of the element buffer object with the VAO
			if (p_ebo != nullptr) { p_ebo->bind(); }

			// We unbind the VAO
			glBindVertexArray(0);
			//// We store the configuration
			_eboSize = p_ebo->size();
		}

		VertexArrayObject::VertexArrayObject(const Shaders::ShaderProgram& p_program, const std::vector<std::pair<std::string, const VertexBufferObject*>>& p_vbos, const ElementBufferObject* p_ebo = nullptr)
			: VertexArrayObject(convert(p_program, p_vbos), p_ebo)
		{}

		VertexArrayObject::~VertexArrayObject()
		{
			// Release memory in openGL
			if (_id != 0) { glDeleteVertexArrays(1, &_id); }
		}

#pragma region COPY
		VertexArrayObject::VertexArrayObject(VertexArrayObject&& p_other)
		{
			_id = p_other._id;
			_eboSize = p_other._eboSize;
			p_other._id = 0;
		}

		VertexArrayObject& VertexArrayObject::operator= (VertexArrayObject&& p_other)
		{
			if (_id != 0) { glDeleteVertexArrays(1, &_id); }

			_id = p_other._id;
			_eboSize = p_other._eboSize;
			p_other._id = 0;

			return *this;
		}
#pragma endregion


#pragma region GETTERS
		bool VertexArrayObject::isValid() const { 
			return _id != 0; 
		}

		size_t  VertexArrayObject::eboSize() const { 
			return _eboSize; 
		}
#pragma endregion

#pragma region BINDING
		void VertexArrayObject::bind() const
		{
			assert(isValid());
			glBindVertexArray(_id);
		}

		void VertexArrayObject::unbind() const
		{
			glBindVertexArray(0);
		}
#pragma endregion	
	}
}