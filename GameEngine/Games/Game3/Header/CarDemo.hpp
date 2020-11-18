#pragma once

#include <Games/Header/GameBase.hpp>


namespace Games::Game3 {
	class CarDemo : public GameBase
	{
		/* Initializes the game */
		virtual void initGame();

		/* Handles user inputs
		@param p_dt the time ellapsed since the last update*/
		virtual void handleInput(double p_dt);

		/**
		* Function called when the user reshapes the game window
		* @param p_width : new window's width
		* @param p_height : new window's height
		**/
		virtual void reshape(GLint p_width, GLint p_height);

		/*
		Updates the positions of the particles
		@param p_dt the time ellapsed since the last update
		*/
		virtual void updatePhysic(double p_dt);

		/*Updates the visual representations of the particles*/
		virtual void updateFrame();
	public:
		/* Default constructor */
		CarDemo();

		~CarDemo();
	};
}


