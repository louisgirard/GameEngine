#pragma once

#include <iostream>

#include <glm/glm.hpp>

#include <GraphicEngine/Buffers/Header/VertexBufferObject.hpp>

namespace GraphicEngine::SceneBase {
		class SkyboxGeometry
		{
			static Buffers::VertexBufferObject* s_VBO;

#pragma region GETTERS
			/*
			* Gets a cube with faces oriented toward the inside
			* @return the skybox geometry
			*/
			static const std::vector<glm::vec3>& getVertices();

			/*
			* The vertex buffer object associated to this geometry
			* @return VBO associated to this geometry
			*/
			static const Buffers::VertexBufferObject& getVBO();
#pragma endregion

			/* Default constructor */
			SkyboxGeometry(){}

			/* Destructor */
			~SkyboxGeometry();

		public:
			/*
			* Gets the unique instance of SkyboxGeometry
			* @return an unique instance of this class
			*/
			static SkyboxGeometry* getSingleton();

			/*
			* Resets this instance.
			* Call this function when GLUT is reseted
			*/
			void reset();

			/*
			* Renders the skybox using the provided attribute to attach to the VBO
			* @param p_positionAttribute : The position attribute of the vertex shader
			*/
			void render(GLint p_positionAttribute);
		};
}



