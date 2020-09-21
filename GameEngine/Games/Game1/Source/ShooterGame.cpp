#include <Games/Game1/Header/ShooterGame.h>

namespace Games {
	namespace Game1 {
		
		ShooterGame::ShooterGame():GameBase() {}

		void ShooterGame::initGame() {
			_projectile.changeType(PhysicEngine::Projectile::Types::Laser);
			_projectile.launch();
		}

		void ShooterGame::handleInput() {
			GameBase::handleInput();
		}

		void ShooterGame::updatePhysic(double p_dt) {
			_projectile.integrate((float)p_dt);
			std::cout << "x = " << _projectile.getPosition()._x << ", y = " << _projectile.getPosition()._y << ", z = " << _projectile.getPosition()._z << std::endl;
		}

		void ShooterGame::updateFrame(double p_dt) {
			_projectile.draw();
		}
		
	}
}