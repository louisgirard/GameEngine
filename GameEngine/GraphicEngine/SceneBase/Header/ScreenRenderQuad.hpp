#pragma once

#include <GraphicEngine/Buffers/Header/MultipleDataVBO.hpp>

namespace GraphicEngine::SceneBase {
		class ScreenRenderQuad
		{
		protected:

			static Buffers::MultipleDataVBO<glm::vec3, glm::vec2>* s_VBO;

#pragma region GETTERS
			/*
			* Gets quad geometry
			* @return the vertices of the quad
			*/
			static const std::vector<std::tuple<glm::vec3, glm::vec2>>& getVertices();

			/*
			* Gets the VBO linked to this mesh
			* @return the VBO linked to this mesh
			*/
			static const Buffers::MultipleDataVBO<glm::vec3, glm::vec2>& getVBO();
#pragma endregion

			/* Default constructor */
			ScreenRenderQuad(){}

		public:

			/*
			* Gets the singleton of the ScreenRenderQuad
			* @return The unique instance of this class
			*/
			static ScreenRenderQuad* getSingleton();

			/* Destructor */
			~ScreenRenderQuad();

			/*
			* Reset this instance 
			* Call this when GLUT is reseted
			*/
			void reset();

			/*
			* Renders the quad
			* @p_position2DAttribute : Index to the position2D attribute
			* @p_textureCoordinateAttribute : Index to the texture coordinates attribute
			*/
			void render(GLint position2dAttribute, GLint textureCoordinatesAttribute) const;
		};
}



