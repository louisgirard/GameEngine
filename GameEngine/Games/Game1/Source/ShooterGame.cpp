#include <Games/Game1/Header/ShooterGame.h>

namespace Games {
	namespace Game1 {
		
		ShooterGame::ShooterGame():GameBase() {}

		void ShooterGame::initGame() {}

		void ShooterGame::handleInput() {
			GameBase::handleInput();
			if (_keyboard.isPressed('1')) {
				_currentType = PhysicEngine::CParticle::Types::Bullet;
			}
			else if (_keyboard.isPressed('2')) {
				_currentType = PhysicEngine::CParticle::Types::Canonball;
			}
			else if (_keyboard.isPressed('3')) {
				_currentType = PhysicEngine::CParticle::Types::Laser;
			}
			else if (_keyboard.isPressed('4')) {
				_currentType = PhysicEngine::CParticle::Types::Fireball;
			}
			else if (_keyboard.isPressed('s')) {
				if (!_shootingButtonPressed) {
					_projectiles.push_back(std::make_shared<PhysicEngine::CParticle>(_currentType));
					_shootingButtonPressed = true;
				}
			}
			else if (_shootingButtonPressed) {
				_shootingButtonPressed = false;
			}
		}

		void ShooterGame::updatePhysic(double p_dt) {
			for(int i = 0; i<_projectiles.size(); i++)
			{
				_projectiles[i]->update(p_dt);
				std::cout << "x = " << _projectiles[i]->getPosition()._x << ", y = " << _projectiles[i]->getPosition()._y << ", z = " << _projectiles[i]->getPosition()._z << std::endl;
			}
		}

		void ShooterGame::updateFrame(double p_dt) {
			//_projectile.draw();
		}
		
	}
}