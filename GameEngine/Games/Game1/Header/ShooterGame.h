#ifndef _GAME1_SHOOTER_H
#define _GAME1_SHOOTER_H

#include <Games/Header/GameBase.h>
#include <PhysicEngine/Header/CParticle.h>

namespace Games {
	namespace Game1 {
		class ShooterGame : public GameBase
		{
		protected :
			/*
			Vector containing the particles currently in game
			*/
			std::vector<std::shared_ptr<PhysicEngine::CParticle>> _projectiles;

			/*
			Determines if the shooting button is currently pressed (a new particle is only
			created once per key press)
			*/
			bool _shootingButtonPressed = false;

			PhysicEngine::CParticle::Types _currentType = PhysicEngine::CParticle::Types::Bullet;

			virtual void initGame();

			virtual void handleInput();

			/*
			Updates the positions of the particles
			@param p_dt the time ellapsed since the last update
			*/
			virtual void update(double p_dt);

		public :
			ShooterGame();
		};

	}
}
#endif // !_GAME1_SHOOTER_H



