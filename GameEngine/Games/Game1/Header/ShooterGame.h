#ifndef _GAME1_SHOOTER_H
#define _GAME1_SHOOTER_H

#include <Games/Header/GameBase.h>
#include <PhysicEngine/Header/CParticle.h>

namespace Games {
	namespace Game1 {
		class ShooterGame : public GameBase
		{
		protected :
			std::vector<std::shared_ptr<PhysicEngine::CParticle>> _projectiles;

			PhysicEngine::CParticle::Types _currentType = PhysicEngine::CParticle::Types::Bullet;

			virtual void initGame();

			virtual void handleInput();

			virtual void updatePhysic(double p_dt);

			void virtual updateFrame(double p_dt);

			bool _shootingButtonPressed = false;

		public :
			ShooterGame();
		};

	}
}
#endif // !_GAME1_SHOOTER_H



