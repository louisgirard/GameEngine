#pragma once

#include <Games/Header/GameBase.hpp>

namespace Games::Game3 {
	class TestMath : public GameBase
	{

		/* Initializes the game */
		virtual void initGame();

		/*
		Updates the positions of the particles
		@param p_dt the time ellapsed since the last update
		*/
		virtual void updatePhysic(double p_dt);


	public:
		/* Default constructor */
		TestMath();

	};

}



