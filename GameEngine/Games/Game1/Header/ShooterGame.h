#ifndef _GAME1_SHOOTER_H
#define _GAME1_SHOOTER_H

#include <Games/Header/GameBase.h>
#include <PhysicEngine/Header/Particle.h>

namespace Games {
	namespace Game1 {
		class ShooterGame : public GameBase
		{
		protected :
			PhysicEngine::Particle _particle;

			virtual void initGame();

			virtual void  update(double p_dt);

		public :
			ShooterGame();
		};

	}
}
#endif // !_GAME1_SHOOTER_H



