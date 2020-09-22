#include <Games/Game1/Header/ShooterGame.h>

namespace Games {
	namespace Game1 {
		
		ShooterGame::ShooterGame():GameBase() {}

		void ShooterGame::initGame() {}

		void ShooterGame::handleInput() {
			GameBase::handleInput();
			//if one the keys 1 through 4 is pressed, the type of launched particle is changed
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

			//if the s key is pressed, a particle is launched
			if (_keyboard.isPressed('s')) {
				//check to see if it's the first frame where the key is pressed
				//this avoids sending multiple particles per key press
				if (!_shootingButtonPressed) {
					//adding a new particle to the scene
					_projectiles.push_back(std::make_shared<PhysicEngine::CParticle>(_currentType));
					_shootingButtonPressed = true;
				}
			}

			//in that case, the shooting button is no longer pressed
			else if (_shootingButtonPressed) {
				_shootingButtonPressed = false;
			}
		}

		void ShooterGame::updatePhysic(double p_dt) {

			//going through every particle in the scene and updating their positions
			for(int i = 0; i<_projectiles.size(); i++)
			{
				_projectiles[i]->updatePhysic(p_dt);
				//the positions of the particles are printed in the console
				std::cout<< "index = "<< i << ", x = " << _projectiles[i]->getPosition()._x << ", y = " << _projectiles[i]->getPosition()._y << ", z = " << _projectiles[i]->getPosition()._z << std::endl;
			}
		}

		void ShooterGame::updateFrame() {
			for (int i = 0; i < _projectiles.size(); i++)
			{
				_projectiles[i]->updateFrame();
			}
		}
		
	}
}