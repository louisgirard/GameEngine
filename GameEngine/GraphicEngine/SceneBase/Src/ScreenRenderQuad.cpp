#include <GraphicEngine/SceneBase/Header/ScreenRenderQuad.hpp>

namespace GraphicEngine::SceneBase {

		Buffers::MultipleDataVBO<glm::vec3, glm::vec2>* ScreenRenderQuad::s_VBO = nullptr;

		ScreenRenderQuad* ScreenRenderQuad::getSingleton()
		{
			static ScreenRenderQuad instance;
			return &instance;
		}

		ScreenRenderQuad::~ScreenRenderQuad() {
			delete s_VBO;
		}

		void ScreenRenderQuad::render(GLint position2dAttribute, GLint textureCoordinatesAttribute) const
		{
			getVBO().bind();
			// Set the VBO as attribute 
			getVBO().passAsAttribute<0>(position2dAttribute);
			getVBO().passAsAttribute<1>(textureCoordinatesAttribute);
			// Draw vertices
			glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)getVBO().size());
			getVBO().unbind();
		}

		void ScreenRenderQuad::reset() {
			delete s_VBO;
			s_VBO = nullptr;
		}

#pragma region GETTERS
		const std::vector<std::tuple<glm::vec3, glm::vec2>>& ScreenRenderQuad::getVertices()
		{
			static std::vector<std::tuple<glm::vec3, glm::vec2>> quadVertices =
			{
				// (positions, texCoords)
				{ glm::vec3(-1.0f,  1.0f, 0.1f), glm::vec2(0.0f, 1.0f) },
				{ glm::vec3(-1.0f, -1.0f, 0.1f), glm::vec2(0.0f, 0.0f) },
				{ glm::vec3(1.0f,  1.0f, 0.1f), glm::vec2(1.0f, 1.0f) },
				{ glm::vec3(1.0f, -1.0f, 0.1f), glm::vec2(1.0f, 0.0f) },
			};
			return quadVertices;
		}

		const Buffers::MultipleDataVBO<glm::vec3, glm::vec2>& ScreenRenderQuad::getVBO()
		{
			if (s_VBO == nullptr) s_VBO = new Buffers::MultipleDataVBO<glm::vec3, glm::vec2>(getVertices());
			return *s_VBO;
		}
#pragma endregion
}
