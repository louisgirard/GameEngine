#pragma once

#include <string>

#include <glm/common.hpp>
#include <glm/matrix.hpp>

#include <Games/Header/GameBase.hpp>

namespace Games {
	class Demo : public GameBase
	{
	protected:

		// Shaders
		static const std::string FILTER;
		static const std::string GAUSSIAN;

		// Scene graph
		EmptyNode* _sceneRoot;

		// Clipping distance
		float _clippingDistance;

#pragma region INITIALIZATION
		/* Initializes the game */
		virtual void initGame();
#pragma endregion

		/**
		* Function called when the user reshapes the game window
		* @param p_width : new window's width
		* @param p_height : new window's height
		**/
		virtual void reshape(GLint p_width, GLint p_height);

		/* Handles user inputs 
		* @param p_dt the time ellapsed since the last update*/
		virtual void handleInput(double p_dt);

#pragma region UPDATE
		/*
		* Updates the positions of the particles
		* @param p_dt the time ellapsed since the last update
		*/
		virtual void updatePhysic(double p_dt) {}

		/*
		Updates the visual representations of the particles
		*/
		virtual void updateFrame();
#pragma endregion

	public:
#pragma region INITIALIZATION
		Demo();
#pragma endregion

		~Demo();
	};
}


