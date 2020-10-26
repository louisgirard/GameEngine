#ifndef _GRAPHIC_ENGINE_VERTEX_ARRAY_OBJECT_HPP_
#define _GRAPHIC_ENGINE_VERTEX_ARRAY_OBJECT_HPP_

#include <GraphicEngine/Shaders/Header/ShaderProgram.hpp>
#include <GraphicEngine/Buffers/Header/ElementBufferObject.hpp>

namespace GraphicEngine::Buffers {
		class VertexArrayObject
		{
		protected :
			/* identifier of the VAO in openGL */
			GLuint _id;
			/* Size of the EBO */
			size_t _eboSize;

			/*
			* Find every openGL attribute's identifier corresponding to a string 
			* @param p_program : Shader program to look into
			* @param p_vbos : Buffer of attribute to find 
			*/
			template <typename Type>
			static std::vector<std::pair<GLint, Type>> convert(const Shaders::ShaderProgram& p_program, 
				const std::vector<std::pair<std::string, Type>>& p_vbos)
			{

				std::vector<std::pair<GLint, Type>> result;
				// Init vector size 
				result.reserve(p_vbos.size());

				// For each string find the index associated in openGL
				for (auto it = p_vbos.begin(), end = p_vbos.end(); it != end; ++it)
				{
					GLint location = p_program.getAttributeLocation(it->first);
					assert(location != -1);
					result.push_back({ location, it->second });
				}

				// Help to move more efficiently the result
				return std::move(result);
			}

		public:

			VertexArrayObject():_id(0), _eboSize(0){}

			/*
			* Constructor
			* @param p_vbos : Buffer of VBO associated with a shader program
			* @param p_ebo : EBO corresponding to the VBO buffer, can be null
			*/
			VertexArrayObject(const std::vector<std::pair<GLint, const VertexBufferObject*>>& p_vbos, const ElementBufferObject* ebo = nullptr);

			/*
			* Constructor
			* @param p_program : The shader program 
			* @param p_vbos :  Buffer of VBO associated with a shader program
			* @param p_ebo : EBO corresponding to the VBO buffer, can be null
			*/
			VertexArrayObject(const Shaders::ShaderProgram& p_program, const std::vector<std::pair<std::string, const VertexBufferObject*>>& p_vbos, const ElementBufferObject* p_ebo = nullptr);


			/* Destructor */
			~VertexArrayObject();

#pragma region COPY
			/*Disallow copying from simple reference*/
			VertexArrayObject(const VertexArrayObject&) = delete;
			VertexArrayObject operator = (const VertexArrayObject&) = delete;

			/*
			* Move constructor
			* @param p_other : VAO to move
			*/
			VertexArrayObject(VertexArrayObject&& p_other);

			/*
			*  Move assignment
			*  @param p_other : VAO to move
			*/
			VertexArrayObject& operator= (VertexArrayObject&& p_other);
#pragma endregion

#pragma region GETTERS
			/*
			* Determines whether this VAO is valid
			* @return true if the VAO is valid, else false
			*/
			bool isValid() const; 

			/*
			* Gets the size of the attached EBO
			* @return the size of the EBO attached
			*/
			size_t eboSize() const;
#pragma endregion

#pragma region BINDING
			/*
			* Binds this VAO in openGL
			*/
			void bind() const;

			/*
			* Unbinds this VAO in openGL
			*/
			void unbind() const;
#pragma endregion	
		};
}

#endif // !_GRAPHIC_ENGINE_VERTEX_ARRAY_OBJECT_HPP_



