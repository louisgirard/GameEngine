#pragma once

#include <tuple>
#include <type_traits>

#include <GraphicEngine/Buffers/Header/VertexBufferObject.hpp>

namespace GraphicEngine::Buffers {
		template <typename FirstType, typename... OtherTypes>
		class MultipleDataVBO
		{
		public:
			/* The type of the data stored in the buffer. It is a tuple if the number of provided types is more than one, the provided type otherwise */
			using Data = typename std::conditional<sizeof...(OtherTypes) == 0, FirstType, std::tuple<FirstType, OtherTypes...>>::type;

		protected:

			/* Buffer id in openGL*/
			GLuint _id;
			/* Size of the buffer*/
			GLuint _size;

		public:

			/*
			* Default constructor 
			* Warning this buffer is invalid
			*/
			MultipleDataVBO():_id(0), _size(0){}

			/*
			* Constructor
			* @param p_data : The data to pass to the buffer
			* @param p_usage : Update frequency of the buffer
			*/
			MultipleDataVBO(const std::vector<Data>& p_buffer, BufferUpdate p_usage = BufferUpdate::staticDraw)
			{
				// Création of the vertex buffer object
				glGenBuffers(1, &_id);

				// Initialisation of the vertex buffer object
				glBindBuffer(GL_ARRAY_BUFFER, _id);
				glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Data) * p_buffer.size()), p_buffer.data(), static_cast<GLenum>(p_usage));
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				// Save the size
				_size = (GLuint)p_buffer.size();
			}

			/* Destructor */
			~MultipleDataVBO()
			{
				if (_id != 0) { glDeleteBuffers(1, &_id); }
			}

			/*
			* Associates the element of index struct index in the vertex buffer object with an attribute of a shader.
			* Warning, the buffer is bound after calling this method.
			* 
			* @param p_shaderAttributeIndex : Index of the shader attribute
			* @param p_nbInstances : The number of instances befor changing the value
			*/
			template <size_t structIndex = 0>
			void passAsAttribute(GLint p_shaderAttributeIndex, GLint p_nbInstancestances = 0) const
			{
				static_assert(structIndex < (1 + sizeof...(OtherTypes)), "PackedVertexBufferObject::attribPointer: Index out of range");

				assert(isValid() && "PackedVertexBufferObject::attribPointer called on an invalid packed vertex buffer object");

				// Binds this buffer
				bind();

				// We compute the offset of the value for a buffer that does not contains tuples
				size_t valueOffset = 0;
				
				GLenum glType = GLenum(GraphicEngine::GLMTypesSpec<FirstType>::glType()); // The scalar data type
				size_t nbSlots = GraphicEngine::GLMTypesSpec<FirstType>::columns(); // The number of slots occupied by the data type (1 per column)
				size_t slotSize = GraphicEngine::GLMTypesSpec<FirstType>::rows(); // The size of the data in the slot

				// If the buffer contains tuples, we handle it
				// (We look for the given (by structIndex) type and get the buffer spec for this type)
				if constexpr (sizeof...(OtherTypes) > 0)
				{
					using TypeConst = typename std::remove_const<decltype(std::get<structIndex>(Data()))>::type;
					using Type = typename std::remove_reference<TypeConst>::type;
					Data tmp;
					auto* value = &std::get<structIndex>(tmp);
					valueOffset = ((char*)value) - ((char*)&tmp);
					using typeSpec = GraphicEngine::GLMTypesSpec<Type>;
					nbSlots = typeSpec::columns();
					slotSize = typeSpec::rows();
					glType = GLenum(typeSpec::glType());
				}

				// We associate the buffer with the input of the shader program
				for (size_t cpt = 0; cpt < nbSlots; ++cpt)
				{
					glVertexAttribPointer(p_shaderAttributeIndex + (GLint)cpt, (GLint)slotSize, glType, GL_FALSE, sizeof(Data), (void*)((GLint)valueOffset + (GLint)slotSize * sizeof(float) * (GLint)cpt));
					glEnableVertexAttribArray(p_shaderAttributeIndex + (GLint)cpt);
					if (p_nbInstancestances > 0) { glVertexAttribDivisor(p_shaderAttributeIndex + (GLint)cpt, p_nbInstancestances); }
				}
			}

			/*
			* Updates the content of the buffer
			* @param p_data : The data to update
			*/
			void update(const std::vector<Data>& p_data) const
			{
				assert(isValid() && "PackedVertexBufferObject::update called on an invalid packed vertex buffer object");
				assert(p_data.size() == _size);
				bind();
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Data) * p_data.size(), p_data.data());
				unbind();
			}

			/*
			* Updates the content of the buffer
			* @param p_data : The data to update
			* @param p_startIndex : The start index in the VBO
			*/
			void update(const std::vector<Data>& p_data, size_t p_startIndex) const
			{
				assert(isValid() && "PackedVertexBufferObject::update called on an invalid packed vertex buffer object");
				assert((p_startIndex + p_data.size()) <= _size &&"PackedVertexBufferObject::update called with a buffer too big ");
				bind();
				glBufferSubData(GL_ARRAY_BUFFER, sizeof(Data) * p_startIndex, sizeof(Data) * p_data.size(), p_data.data());
				unbind();
			}

#pragma region COPY
			/*Disallow copying from simple reference*/
			MultipleDataVBO(const MultipleDataVBO&) = delete;
			MultipleDataVBO& operator=(const MultipleDataVBO&) = delete;

			/*
			* Move constructor
			* @param p_other : VBO to move
			*/
			MultipleDataVBO(MultipleDataVBO&& p_other)
				: _id(p_other._id), _size(p_other._size)
			{
				p_other._id = 0;
			}

			/*
			*  Move assignment
			*  @param p_other : VBO to move
			*/
			MultipleDataVBO& operator= (MultipleDataVBO&& p_other)
			{
				_id = p_other._id;
				_size = p_other._size;
				p_other._id = 0;

				return (*this);
			}
#pragma endregion
			
#pragma region GETTERS
			/*
			* Determines whether this buffer is valid
			* @return true if this buffer is valid, else false
			*/
			bool isValid() const {
				return _id != 0; 
			}

			/*
			* Gets the identifier of the buffer in openGL
			* @return the buffer's identifier
			*/
			GLuint getId() const {
				return _id;
			}

			/*
			* Gets the size of the VBO
			* @return VBO's size
			*/
			size_t size() const {
				return _size;
			}
#pragma endregion

#pragma region BINDING
			/*
			* Binds this buffer in openGL
			*/
			void bind() const
			{
				assert(isValid() && "PackedVertexBufferObject::bind called on an invalid packed vertex buffer object");
				glBindBuffer(GL_ARRAY_BUFFER, _id);
			}

			/*
			* Unbinds this buffer
			*/
			void unbind() const
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
#pragma endregion
		};
}



