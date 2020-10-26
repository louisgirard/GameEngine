#pragma once

#include <string>

#include <glm/common.hpp>
#include <glm/matrix.hpp>

#include <Games/Header/GameBase.hpp>

namespace Games {
	class SimpleTestGraphic : public GameBase
	{
		GLuint m_programId, m_VBOvertices, m_VBOcolors, m_EBOindexes, m_VAO;
		std::vector<glm::vec3> m_vertices;
		std::vector<glm::vec3> m_colors;
		std::vector<GLuint> m_indexes;


	public:
		SimpleTestGraphic()
		{}

		virtual ~SimpleTestGraphic()
		{}

	protected:

		virtual void updatePhysic(double p_dt) {}

		/// <summary>
		/// Method called when the size of the window changes.
		/// </summary>
		/// <param name="width">The new width.</param>
		/// <param name="height">The new height.</param>
		virtual void reshape(GLint width, GLint height) {
			GameBase::reshape(width, height);
		}

		virtual void handleInput(double p_dt) {
			GameBase::handleInput(p_dt);
		}

		/// <summary>
		/// Loads a text file into a string.
		/// </summary>
		/// <param name="file">The file to load.</param>
		/// <returns></returns>
		static std::string loadTextFile(const std::filesystem::path& file)
		{
			if (!std::filesystem::exists(file))
			{
				std::cerr << "File " << file.string() << " does not exists" << std::endl;
				throw std::ios_base::failure(file.string() + " does not exists");
			}
			std::stringstream result;
			std::ifstream input(file);
			while (!input.eof())
			{
				std::string tmp;
				std::getline(input, tmp);
				result << tmp << std::endl;
			}
			return result.str();
		}

		//Créé un shader avec des tableau de caractère se finissant par 0 
		GLuint getNewShaderID(GLenum p_shaderType, const char* p_source) {

			GLuint shaderId;
			shaderId = glCreateShader(p_shaderType);
			glShaderSource(shaderId, 1, &p_source, 0);
			glCompileShader(shaderId);

			// We check the compilation status and report any errors
			GLint shaderStatus;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderStatus);
			// If the shader failed to compile, display the info log
			if (shaderStatus == GL_FALSE)
			{
				GLint infoLogLength;
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar* strInfoLog = new GLchar[infoLogLength + 1];
				glGetShaderInfoLog(shaderId, infoLogLength, NULL, strInfoLog);
				std::cerr << "Shader: shader compilation failed. " << std::endl << strInfoLog << std::endl;
			}
			return shaderId;
		}

		//Créé un shader programme qui attache deux shader 
		GLuint getProgramID(GLuint p_vshaderId, GLuint p_fshaderId) {

			GLuint programId = glCreateProgram();
			glAttachShader(programId, p_vshaderId);
			glAttachShader(programId, p_fshaderId);
			glLinkProgram(programId);

			// Check the status
			GLint linkStatus;
			glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
			// If the link failed, we output the error
			if (linkStatus == GL_FALSE)
			{
				GLint infoLogLength = 4096;
				glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar* strInfoLog = new GLchar[infoLogLength + 1];
				glGetProgramInfoLog(programId, infoLogLength, NULL, strInfoLog);
				std::cerr << "ShaderProgram: Failed to link shader program." << std::endl
					<< strInfoLog << std::endl;
			}

			return programId;
		}

		void attachShdr(GLuint p_programId, GLuint p_shaderId) {

			glAttachShader(p_programId, p_shaderId);
			glLinkProgram(p_programId);

			// Check the status
			GLint linkStatus;
			glGetProgramiv(p_programId, GL_LINK_STATUS, &linkStatus);
			// If the link failed, we output the error
			if (linkStatus == GL_FALSE)
			{
				GLint infoLogLength = 4096;
				glGetProgramiv(p_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
				GLchar* strInfoLog = new GLchar[infoLogLength + 1];
				glGetProgramInfoLog(p_programId, infoLogLength, NULL, strInfoLog);
				std::cerr << "ShaderProgram: Failed to link shader program." << std::endl
					<< strInfoLog << std::endl;
			}
		}

		virtual void initGame()
		{
			// 0 - Camera setup
			_camera.setPosition(glm::vec3(0.0f, 0.0f, 0.5f));
			_cameraSpeed = 1.0f;
			_cameraRotationSpeed = (float)(3.14 / 5.0);

			// Vertices positions
			m_vertices = {
				glm::vec3(-0.5f, -0.5f, 0.0f),
				glm::vec3(0.5f, -0.5f, 0.0f),
				glm::vec3(0.0f,  0.5f, 0.0f)
			};
			// Vertices colors
			m_colors = {
				glm::vec3(1.0, 0.0, 0.0),
				glm::vec3(0.0, 1.0, 0.0),
				glm::vec3(0.0, 0.0, 1.0)
			};
			// Indexes for the EBO
			m_indexes = { 0, 1, 2 };

			// The base path of the shader files
			std::filesystem::path shaderPath = dataPath() / "Shaders";

			glGenBuffers(1, &m_EBOindexes);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOindexes);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * m_indexes.size(), m_indexes.data(), GL_STATIC_DRAW);


			glGenBuffers(1, &m_VBOvertices);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBOvertices);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &m_VBOcolors);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBOcolors);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_colors.size(), m_colors.data(), GL_STATIC_DRAW);

			GLuint vrtxID;
			std::string vshaderString = loadTextFile(shaderPath / "tp1.vert");
			const char* vshaderPath = vshaderString.c_str();
			vrtxID = getNewShaderID(GL_VERTEX_SHADER, vshaderPath);

			GLuint fragID;
			std::string fshaderString = loadTextFile(shaderPath / "tp1.frag");
			const char* fshaderPath = fshaderString.c_str();
			fragID = getNewShaderID(GL_FRAGMENT_SHADER, fshaderPath);

			m_programId = getProgramID(vrtxID, fragID);

			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);
			// Enregistrement de la connexion du VBO au shader program
			glBindBuffer(GL_ARRAY_BUFFER, m_VBOvertices);
			GLint posAttrib = glGetAttribLocation(m_programId, "in_position");
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, (GLsizei)m_indexes.size(), GL_FLOAT, false, 0, nullptr);
			// Enregistrement de la connexion du 2eme VBO au shader program
			glBindBuffer(GL_ARRAY_BUFFER, m_VBOcolors);
			posAttrib = glGetAttribLocation(m_programId, "in_colors");
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, (GLsizei)m_colors.size(), GL_FLOAT, false, 0, nullptr);
			// Enregistrmenet de l'attachement de l'EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOindexes);
			// Terminaison de l'enregistrement
			glBindVertexArray(0);

		}

		virtual void updateFrame()
		{

			glUseProgram(m_programId);
			// Connexion du VBO au shader program
			/*glBindBuffer(GL_ARRAY_BUFFER, m_VBOvertices);
			GLint posAttrib = glGetAttribLocation(m_programId, "in_position");
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, 3, GL_FLOAT, false, 0, nullptr);
			// Affichage de la géométrie sous forme de triangles
			//glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
			// Attachement de l'EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBOindexes);*/

			// Initialisation des uniform
			GLint uniCam = glGetUniformLocation(m_programId, "uni_mat_view");
			glUniformMatrix4fv(uniCam, 1, GL_FALSE, &(_camera.getInverseTransform()[0][0]));
			GLint uniModel = glGetUniformLocation(m_programId, "uni_mat_model");
			GLint uniProj = glGetUniformLocation(m_programId, "uni_mat_projection");
			glUniformMatrix4fv(uniProj, 1, GL_FALSE, &(glm::perspective(glm::pi<float>() / 2.0f, (float)(getConfiguration().getWindowWidth() / getConfiguration().getWindowHeight()), 0.001f, 1000.0f)[0][0]));

			// Affichage avec le VAO 
			glBindVertexArray(m_VAO);

			// Affichage de deux géometry sur deux endroit différents
			glUniformMatrix4fv(uniModel, 1, GL_FALSE, &(glm::translate(glm::vec3(-0.5, 0, 0))[0][0]));
			glDrawElements(GL_TRIANGLES, m_indexes.size(), GL_UNSIGNED_INT, 0);
			glUniformMatrix4fv(uniModel, 1, GL_FALSE, &(glm::translate(glm::vec3(0.5, 0, 0))[0][0]));
			glDrawElements(GL_TRIANGLES, m_indexes.size(), GL_UNSIGNED_INT, 0);


		}

	};
}



