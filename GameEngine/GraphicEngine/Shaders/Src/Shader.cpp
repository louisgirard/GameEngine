#include <GraphicEngine/Shaders/Header/Shader.hpp>

namespace GraphicEngine {
	namespace Shaders {

		Shader::Shader(const ShaderSource p_source, ShaderType p_type) {

			_type = p_type;
			// Create a new shader in openGl and save it's id
			_shaderID = glCreateShader(static_cast<GLenum>(_type));
			// Retrieve the source code for this shader
			std::string sourceCode = p_source.toString();
			const char* charSourceCode = sourceCode.c_str();

			// Load the code in openGl
			// Second and fourth parameter help to specify there is only one string in the tab
			glShaderSource(_shaderID, 1, &charSourceCode, 0);
			// Activate openGl compilation for this shader
			glCompileShader(_shaderID);

			// Check compilation status and report any errors
			GLint shaderStatus; // out param, resulting status
			glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &shaderStatus); // Function that get specific param for a shader in openGL

			// If the shader failed to compile, display the info log and throw a runtime_error exception
			if (shaderStatus == GL_FALSE)
			{
				GLint infoLogLength;
				glGetShaderiv(_shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

				GLchar* strInfoLog = new GLchar[(int)infoLogLength + 1];
				glGetShaderInfoLog(_shaderID, infoLogLength, NULL, strInfoLog);

				std::cerr << "Shader: shader compilation failed. " << std::endl << strInfoLog << std::endl;

				//Don't forget to release memory
				delete[] strInfoLog;
				glDeleteShader(_shaderID);
				_shaderID = 0;

				throw std::runtime_error("Shader: failed to compile source code.");
			}

		}

		Shader::~Shader() {
			// Release memory in openGl
			if (_shaderID != 0) { glDeleteShader(_shaderID); }
		}

#pragma region GETTERS
		bool Shader::isValid() const {
			return _shaderID != 0;
		}

		ShaderType Shader::getType() const {
			assert(isValid() && "Shader::getType called on an invalid Shader");
			return _type;
		}

		GLuint Shader::getId() const {
			assert(isValid() && "Shader::getId called on an invalid Shader");
			return _shaderID;
		}
#pragma endregion

#pragma region COPY	
		Shader::Shader(Shader&& p_other)
		{
			_type = p_other._type;
			_shaderID = p_other._shaderID;
			p_other._shaderID = 0;
		}

		Shader& Shader::operator= (Shader&& p_other)
		{
			//Release memory if necessary
			if (_shaderID != 0) { glDeleteShader(_shaderID); }

			_type = p_other._type;
			_shaderID = p_other._shaderID;
			p_other._shaderID = 0;

			return (*this);
		}

#pragma endregion
	}
}
