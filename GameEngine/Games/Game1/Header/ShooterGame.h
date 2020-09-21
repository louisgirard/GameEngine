#ifndef _GAME1_SHOOTER_H
#define _GAME1_SHOOTER_H

#include <Games/Header/GameBase.h>
#include <PhysicEngine/Header/Projectile.h>

namespace Games {
	namespace Game1 {
		class ShooterGame : public GameBase
		{
		protected :
			PhysicEngine::Projectile _projectile;

			virtual void initGame();

			virtual void updatePhysic(double p_dt);

			void virtual updateFrame(double p_dt);

		public :
			ShooterGame();
		};

	}
}
#endif // !_GAME1_SHOOTER_H



