#ifndef _GRAPHIC_ENGINE_TEXTURE_BUFFER_OBJECT_HPP_
#define _GRAPHIC_ENGINE_TEXTURE_BUFFER_OBJECT_HPP_

#include <vector>

#include<GraphicEngine/TypeSpec/Header/GLMTypesSpec.hpp>

namespace GraphicEngine::Buffers {
		template <class Type>
		class TextureBufferObject
		{
		protected :

			// Verify type
			static_assert(GLMTypesSpec<Type>::isCompatible() && (GLMTypesSpec<Type>::isVector() || GLMTypesSpec<Type>::isScalar()), "You provided a data type incompatible with the plateform, should be float, glm::vec2; glm::vec3 or glm::vec4");

			/* Identifier of the TBO in openGL*/
			GLuint _TBOID;
			/* Identifier of the texture in openGL*/
			GLuint _textureID;
			/* Buffer size */
			size_t _size;

		public:

			/*
			* Default constructor
			* Warning this buffer is invalid
			*/
			TextureBufferObject():_TBOID(0), _textureID(0), _size(0){}

			/*
			* Constructor
			* @param p_values : Content to pass to the buffer
			* @param p_updates : Frequency at which the buffer will be update, default is static draw
			*/
			TextureBufferObject(const std::vector<Type>& p_values, BufferUpdate p_update = BufferUpdate::staticDraw)
			{
				// 1 - Create, Bind and Fill the buffer
				glGenBuffers(1, &_TBOID);
				glBindBuffer(GL_TEXTURE_BUFFER, _TBOID);
				glBufferData(GL_TEXTURE_BUFFER, p_values.size() * sizeof(Type), p_values.data(), p_update);
				// 2 - Create, Bind and fill the texure
				glGenTextures(1, &_textureID);
				glBindTexture(GL_TEXTURE_BUFFER, _textureID);
				glTexBuffer(GL_TEXTURE_BUFFER_EXT, GLMTypesSpec<Type>::glTextureFormat(), _TBOID);
				// 3 - Unbinds buffer
				glBindBuffer(GL_TEXTURE_BUFFER, 0);
				glBindTexture(GL_TEXTURE_BUFFER, 0);
				// We store the size
				_size = p_values.size();
			}

			/* Destructor */
			~TextureBufferObject() {
				// Release memory
				if (_textureID != 0) { glDeleteTextures(1, &_textureID); }
				if (_TBOID != 0) { glDeleteBuffers(1, &_TBOID); }
			}

			/*
			* Updates the content of the texture buffer
			* @param p_values : The values to transfer to the texture buffer object
			* @param p_offset : The offset at which the writing in the targeted buffer will begin
			*/
			void update(const std::vector<Type>& p_values, size_t p_offset = 0)
			{
				assert(isValid());
				assert(p_values.size() + p_offset <= _size);

				glBindBuffer(GL_TEXTURE_BUFFER, _TBOID);
				glBufferSubData(GL_TEXTURE_BUFFER, sizeof(Type) * p_offset, p_values.size(), p_values.data());
			}

			/*
			* Associates this texture buffer object with the provided texture unit
			* @param p_unitNumber : The unit number
			*/
			void associateWithTextureUnit(GLuint p_unitNumber) {
				glActiveTexture(GL_TEXTURE0 + p_unitNumber);
				bind();
			}

#pragma region COPY
			/*Disallow copying from simple reference*/
			TextureBufferObject(const TextureBufferObject&) = delete;
			TextureBufferObject& operator = (const TextureBufferObject&) = delete;

			/*
			* Move constructor
			* @param p_other : TBO to move
			*/
			TextureBufferObject(TextureBufferObject&& p_other) : _TBOID(p_other._TBOID), _textureID(p_other._textureID), _size(p_other._size)
			{
				p_other._TBOID = 0; p_other._textureID = 0;
			}

			/*
			*  Move assignment
			*  @param p_other : TBO to move
			*/
			TextureBufferObject& operator= (TextureBufferObject&& p_other) {
				if (_textureID != 0) { glDeleteTextures(1, &_textureID); }
				if (_TBOID != 0) { glDeleteBuffers(1, &_TBOID); }

				_TBOID = p_other._TBOID;
				_textureID = p_other._textureID;
				_size = p_other._size;
				p_other._TBOID = 0;
				p_other._textureID = 0;

				return *this;
			}
#pragma endregion

#pragma region GETTERS
			/*
			* Determines whether this instance is valid
			* @return true if this buffer is valid, else false
			*/
			bool isValid() const {
				return _textureID != 0;
			}

			/*
			* Gets the size of the TBO
			* @return TBO's size
			*/
			size_t size() const {
				return _size;
			}
#pragma endregion

#pragma region BINDING
			/*
			* Binds this TBO in openGL
			*/
			void bind() {
				assert(isValid());
				glBindTexture(GL_TEXTURE_BUFFER, _textureID);
			}

			/*
			* unbinds buffer in openGL
			*/
			void unbind() {
				assert(isValid());
				glBindTexture(GL_TEXTURE_BUFFER, 0);
			}
#pragma endregion

		};
}
#endif // !_GRAPHIC_ENGINE_TEXTURE_BUFFER_OBJECT_HPP_


