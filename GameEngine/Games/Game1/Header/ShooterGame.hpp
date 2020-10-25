#ifndef _GAME1_SHOOTER_H
#define _GAME1_SHOOTER_H

#include <Games/Header/GameBase.hpp>


namespace Games {
	namespace Game1 {
		class ShooterGame : public GameBase
		{
		protected :
			/*
			Vector containing the particles currently in game
			*/
			std::vector<std::shared_ptr<Particle>> _projectiles;

			/*
			Determines if the shooting button is currently pressed (a new particle is only
			created once per key press)
			*/
			bool _shootingButtonPressed = false;

			/* Holds the type of particle selected */
			Particle::Types _currentType = Particle::Types::Bullet;

			/* Menu used to choose a weapon */
			Games::GameMenu* _weaponMenu;

			/* Initializes the game */
			virtual void initGame();

			/* Handles user inputs */
			virtual void handleInput();

			/*
			Updates the positions of the particles
			@param p_dt the time ellapsed since the last update
			*/
			virtual void updatePhysic(double p_dt);

			/*
			Updates the visual representations of the particles
			*/
			virtual void updateFrame();

			/*
			* Contains all the forces and the particle they're associated with
			*/
			ForceRegistry _registry;

			/*
			* The force generator for gravity in the game
			*/
			Gravity _gravityGenerator;

			/**
			* Function called to deal with mouse's motion when no mouse's button is pressed
			* @param p_x : position of the cursor in the window on the x axis
			* @param p_y : position of the cursor in the window on the y axis
			**/
			virtual void mousePassiveMotion(int p_x, int p_y);

		public :
			/* Default constructor */
			ShooterGame();
		};

	}
}
#endif // !_GAME1_SHOOTER_H



