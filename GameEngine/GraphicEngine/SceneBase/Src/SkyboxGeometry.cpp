#include <GraphicEngine/SceneBase/Header/SkyboxGeometry.hpp>

namespace GraphicEngine::SceneBase {

		Buffers::VertexBufferObject* SkyboxGeometry::s_VBO = nullptr;

		SkyboxGeometry* SkyboxGeometry::getSingleton()
		{
			static SkyboxGeometry skybox;
			return &skybox;
		}

		void SkyboxGeometry::render(GLint p_positionAttribute)
		{
			getVBO().bind();
			getVBO().passAsAttribute(p_positionAttribute);
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)getVBO().bufferSize());
			getVBO().unbind();
		}

		SkyboxGeometry::~SkyboxGeometry() {
			delete s_VBO;
		}

		void SkyboxGeometry::reset() {
			delete s_VBO;
			s_VBO = nullptr;
		}

#pragma region GETTERS
		const std::vector<glm::vec3>& SkyboxGeometry::getVertices()
		{
			static std::vector<glm::vec3> vertices =
			{
				glm::vec3(-1.0f,  1.0f, -1.0f),
				glm::vec3(-1.0f, -1.0f, -1.0f),
				glm::vec3(1.0f, -1.0f, -1.0f),
				glm::vec3(1.0f, -1.0f, -1.0f),
				glm::vec3(1.0f,  1.0f, -1.0f),
				glm::vec3(-1.0f,  1.0f, -1.0f),

				glm::vec3(-1.0f, -1.0f,  1.0f),
				glm::vec3(-1.0f, -1.0f, -1.0f),
				glm::vec3(-1.0f,  1.0f, -1.0f),
				glm::vec3(-1.0f,  1.0f, -1.0f),
				glm::vec3(-1.0f,  1.0f,  1.0f),
				glm::vec3(-1.0f, -1.0f,  1.0f),

				glm::vec3(1.0f, -1.0f, -1.0f),
				glm::vec3(1.0f, -1.0f,  1.0f),
				glm::vec3(1.0f,  1.0f,  1.0f),
				glm::vec3(1.0f,  1.0f,  1.0f),
				glm::vec3(1.0f,  1.0f, -1.0f),
				glm::vec3(1.0f, -1.0f, -1.0f),

				glm::vec3(-1.0f, -1.0f,  1.0f),
				glm::vec3(-1.0f,  1.0f,  1.0f),
				glm::vec3(1.0f,  1.0f,  1.0f),
				glm::vec3(1.0f,  1.0f,  1.0f),
				glm::vec3(1.0f, -1.0f,  1.0f),
				glm::vec3(-1.0f, -1.0f,  1.0f),

				glm::vec3(-1.0f,  1.0f, -1.0f),
				glm::vec3(1.0f,  1.0f, -1.0f),
				glm::vec3(1.0f,  1.0f,  1.0f),
				glm::vec3(1.0f,  1.0f,  1.0f),
				glm::vec3(-1.0f,  1.0f,  1.0f),
				glm::vec3(-1.0f,  1.0f, -1.0f),

				glm::vec3(-1.0f, -1.0f, -1.0f),
				glm::vec3(-1.0f, -1.0f,  1.0f),
				glm::vec3(1.0f, -1.0f, -1.0f),
				glm::vec3(1.0f, -1.0f, -1.0f),
				glm::vec3(-1.0f, -1.0f,  1.0f),
				glm::vec3(1.0f, -1.0f,  1.0f)
			};
			return vertices;
		}

		const Buffers::VertexBufferObject& SkyboxGeometry::getVBO()
		{
			if(s_VBO == nullptr)s_VBO = new Buffers::VertexBufferObject (getVertices());
			return *s_VBO;
		}
#pragma endregion
}