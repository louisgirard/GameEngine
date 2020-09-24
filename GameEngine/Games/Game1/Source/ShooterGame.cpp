#include <Games/Game1/Header/ShooterGame.h>

namespace Games {
	namespace Game1 {
		
		ShooterGame::ShooterGame():GameBase() {}

		void ShooterGame::initGame() {
			// 1- Binding Keys
			_keyboard.bindActionToKey(KeyAction::MAINACTION, 's');
			// 2 - We create a sub menu for choosing a weapon
			Games::GameMenu* weaponMenu = new Games::GameMenu("Weapon Pocket");
			weaponMenu->addItem("Pistol", [this]() {_currentType = PhysicEngine::CParticle::Types::Bullet;});
			weaponMenu->addItem("Canon", [this]() {_currentType = PhysicEngine::CParticle::Types::Canonball; });
			weaponMenu->addItem("Laser Gun", [this]() {_currentType = PhysicEngine::CParticle::Types::Laser; });
			weaponMenu->addItem("Fireball Gun", [this]() {_currentType = PhysicEngine::CParticle::Types::Fireball; });
			getMenu()->addSubMenu(weaponMenu);
		}

		void ShooterGame::handleInput() {
			GameBase::handleInput();

			//if the s key is pressed, a particle is launched
			if (_keyboard.isPressed(KeyAction::MAINACTION)) {
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