#include <Games/Game1/Header/ShooterGame.h>

namespace Games {
	namespace Game1 {
		
		ShooterGame::ShooterGame():GameBase() {}

		void ShooterGame::initGame() {
			_particle.setMass(10);
			_particle.setPosition(100, 10, 50);
			_particle.setVelocity(0, 0, 0);
			_particle.setDamping(0.999f);
			_particle.setAcceleration(0, -10, 0);
		}

		void ShooterGame::updatePhysic(double p_dt) {
			_particle.integrate((float)p_dt);
			std::cout << "x = " << _particle.getPosition()._x << ", y = " << _particle.getPosition()._y << ", z = " << _particle.getPosition()._z << std::endl;
		}

		void ShooterGame::updateFrame(double p_dt) {}
		
	}
}