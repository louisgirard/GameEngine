#include <GraphicEngine/Shaders/Header/ShaderProgram.hpp>

namespace GraphicEngine::Shaders {

		ShaderProgram::ShaderProgram(const Shader& p_vertex, const Shader& p_fragment)
		{
			// Verify shaders type
			assert(p_vertex.getType() == ShaderType::vertexShader && "ShaderProgram::ShaderProgram invalid shader type as first parameter, should be a vertex shader");
			assert(p_fragment.getType() == ShaderType::fragmentShader && "ShaderProgram::ShaderProgram invalid shader type as second parameter, should be a fragment shader");
			
			// Create a new shader program in openGL
			_programID = glCreateProgram();
			
			// Attach shaders to the program in openGL
			glAttachShader(_programID, p_vertex.getId());
			glAttachShader(_programID, p_fragment.getId());

			// Link the program in openGL
			link();
		}

		ShaderProgram::ShaderProgram(const std::filesystem::path& p_vertexPath, const std::filesystem::path& p_fragmentPath)
			: ShaderProgram(Shader(ShaderSource(p_vertexPath), ShaderType::vertexShader),
				Shader(ShaderSource(p_fragmentPath), ShaderType::fragmentShader))
		{}

		void ShaderProgram::link()
		{
			// We link the program
			glLinkProgram(_programID);

			// Check the status
			GLint linkStatus;// out param, resulting status
			glGetProgramiv(_programID, GL_LINK_STATUS, &linkStatus);// Function that get specific param for a shader program in openGL

			if (linkStatus == GL_FALSE) 
			{
				GLint infoLogLength = 4096;

				GLchar* strInfoLog = new GLchar[infoLogLength + 1];
				glGetProgramInfoLog(_programID, infoLogLength, NULL, strInfoLog);
				std::cerr << "ShaderProgram: Failed to link shader program." << std::endl << strInfoLog << std::endl;
				
				//Don't forget to release memory if failed
				delete[] strInfoLog;
				_programID = 0;

				throw std::runtime_error("ShaderProgram: failed to link program");
			}
		}

		ShaderProgram::~ShaderProgram()
		{
			// Release memory in openGL
			if (_programID != 0) { glDeleteProgram(_programID); }
		}

#pragma region GETTERS
		bool ShaderProgram::isValid() const { 
			return _programID != 0; 
		}

		GLuint ShaderProgram::getId() const { 
			assert(isValid() && "ShaderProgram::getId called on an invalid shader program"); 
			return _programID; 
		}

		bool ShaderProgram::isActive() const { 
			return getActive() == _programID; 
		}

		GLint ShaderProgram::getActive()
		{
			GLint id;
			glGetIntegerv(GL_CURRENT_PROGRAM, &id);
			return id;
		}
#pragma endregion

#pragma region COPY
		ShaderProgram::ShaderProgram(ShaderProgram&& p_other)
		{
			_programID = p_other._programID;
			p_other._programID = 0;
		}

		ShaderProgram& ShaderProgram::operator= (ShaderProgram&& p_other)
		{
			//Release memory in openGL if necessary
			if (_programID != 0) { glDeleteProgram(_programID);}

			_programID = p_other._programID;
			p_other._programID = 0;

			return (*this);
		}
#pragma endregion

#pragma region BINDING
		void ShaderProgram::use() const 
		{ 
			assert(isValid() && "ShaderProgram::use called on an invalid shader program"); 
			glUseProgram(_programID); 
		}

		void ShaderProgram::unuse() const { 
			assert(isValid() && "ShaderProgram::unuse called on an invalid shader program"); 
			glUseProgram(0); 
		}
#pragma endregion

#pragma region UNIFORMS
		GLint ShaderProgram::getUniformLocation(const std::string& p_name) const
		{
			assert(isValid() && "ShaderProgram::getUniformLocation called on an invalid shader program");
			return glGetUniformLocation(_programID, p_name.c_str());
		}

		void ShaderProgram::setUniform(GLint p_id, const GLint& p_value, size_t p_size) const
		{
			assert(p_id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
			assert(isValid() && isActive());

			glUniform1iv(p_id, (GLsizei)p_size, &p_value);
		}

		void ShaderProgram::setUniform(GLint p_id, const GLfloat& p_value, size_t p_size) const
		{
			assert(p_id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
			assert(isValid() && isActive());

			glUniform1fv(p_id, (GLsizei)p_size, &p_value);
		}

		void ShaderProgram::setUniform(GLint p_id, const glm::vec2& p_value, size_t p_size) const
		{
			assert(p_id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
			assert(isValid() && isActive());

			glUniform2fv(p_id, (GLsizei)p_size, glm::value_ptr(p_value));
		}

		void ShaderProgram::setUniform(GLint p_id, const glm::vec3& p_value, size_t p_size) const
		{
			assert(p_id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
			assert(isValid() && isActive());

			glUniform3fv(p_id, (GLsizei)p_size, glm::value_ptr(p_value));
		}

		void ShaderProgram::setUniform(GLint p_id, const glm::vec4& p_value, size_t p_size) const
		{
			assert(p_id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
			assert(isValid() && isActive());

			glUniform4fv(p_id, (GLsizei)p_size, glm::value_ptr(p_value));
		}

		void ShaderProgram::setUniform(GLint p_id, const glm::mat2x2& p_value, size_t p_size) const
		{
			assert(p_id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
			assert(isValid() && isActive());

			glUniformMatrix2fv(p_id, (GLsizei)p_size, GL_FALSE, glm::value_ptr(p_value));
		}

		void ShaderProgram::setUniform(GLint p_id, const glm::mat3x3& p_value, size_t p_size) const
		{
			assert(p_id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
			assert(isValid() && isActive());

			glUniformMatrix3fv(p_id, (GLsizei)p_size, GL_FALSE, glm::value_ptr(p_value));
		}

		void ShaderProgram::setUniform(GLint p_id, const glm::mat4x4& p_value, size_t p_size) const
		{
			assert(p_id >= 0 && "ShaderProgram::setUniform called with an invalid uniform index");
			assert(isValid() && isActive());

			glUniformMatrix4fv(p_id, (GLsizei)p_size, GL_FALSE, glm::value_ptr(p_value));
		}
#pragma endregion

#pragma region ATTRIBUTES
		GLint ShaderProgram::getAttributeLocation(const std::string& p_name) const
		{
			assert(isValid());
			return glGetAttribLocation(_programID, p_name.c_str());
		}

		void ShaderProgram::setAttribute(const std::string& p_name, const Buffers::VertexBufferObject* p_buffer, GLuint p_nbInstances)
		{
			assert(isValid());
			assert(isActive());

			GLint location = getAttributeLocation(p_name);
			p_buffer->passAsAttribute(location, p_nbInstances);
		}
#pragma endregion
}