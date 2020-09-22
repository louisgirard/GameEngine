#include <Games/Game1/Header/ShooterGame.h>

namespace Games {
	namespace Game1 {
		
		ShooterGame::ShooterGame():GameBase() {}

		void ShooterGame::initGame() {}

		void ShooterGame::handleInput() {
			GameBase::handleInput();
			if (_keyboard.isPressed('1')) {
				_projectile.changeType(PhysicEngine::Projectile::Types::Bullet);
			}
			else if (_keyboard.isPressed('2')) {
				_projectile.changeType(PhysicEngine::Projectile::Types::Canonball);
			}
			else if (_keyboard.isPressed('3')) {
				_projectile.changeType(PhysicEngine::Projectile::Types::Laser);
			}
			else if (_keyboard.isPressed('4')) {
				_projectile.changeType(PhysicEngine::Projectile::Types::Fireball);
			}
			else if (_keyboard.isPressed('s')) {
				_projectile.launch();
			}
		}

		void ShooterGame::updatePhysic(double p_dt) {
			_projectile.move((float)p_dt);
			std::cout << "x = " << _projectile.getPosition()._x << ", y = " << _projectile.getPosition()._y << ", z = " << _projectile.getPosition()._z << std::endl;
		}

		void ShooterGame::updateFrame(double p_dt) {
			_projectile.draw();
		}
		
	}
}