#include <Games/Game1/Header/ShooterGame.hpp>

namespace Games {
	namespace Game1 {

		ShooterGame::ShooterGame() :GameBase() , _weaponMenu(new Games::GameMenu("Weapon Pocket")), _gravityGenerator(*new PhysicEngine::ParticleGravity(*new PhysicEngine::Vector3(0, -10, 0))) {}

		void ShooterGame::initGame() {
			_registry = *new PhysicEngine::ParticleForceRegistry();
			// 1- Binding Keys
			_keyboard.bindActionToKey(KeyAction::MAINACTION, 13);
			// 2 - We create a sub menu for choosing a weapon
			_weaponMenu->addItem("Pistol", [this]() {_currentType = PhysicEngine::CParticle::Types::Bullet; });
			_weaponMenu->addItem("Canon", [this]() {_currentType = PhysicEngine::CParticle::Types::Canonball; });
			_weaponMenu->addItem("Laser Gun", [this]() {_currentType = PhysicEngine::CParticle::Types::Laser; });
			_weaponMenu->addItem("Fireball Gun", [this]() {_currentType = PhysicEngine::CParticle::Types::Fireball; });
			getMenu()->addSubMenu(_weaponMenu);
			// 3 - Add close function
			onClose([this]() {
				// We destroy the menus
				delete _weaponMenu;
			});
		}

		void ShooterGame::handleInput() {
			GameBase::handleInput();

			//if the s key is pressed, a particle is launched
			if (_keyboard.isPressed(KeyAction::MAINACTION)) {
				//check to see if it's the first frame where the key is pressed
				//this avoids sending multiple particles per key press
				if (!_shootingButtonPressed) {
					//adding a new particle to the scene
					_projectiles.push_back(std::make_shared<PhysicEngine::CParticle>(_currentType, PhysicEngine::Vector3::convertGlm(_camera.getPosition()), PhysicEngine::Vector3::convertGlm(_camera.lookingAt())));
					_registry.add((_projectiles.end()-1)->get(), &_gravityGenerator);
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
			_registry.updatePhysic(p_dt);
			for (int i = 0; i < (int)_projectiles.size(); i++)
			{
				_projectiles[i]->updatePhysic(p_dt);
				//the positions of the particles are printed in the console
				std::cout << "index = " << i << ", x = " << _projectiles[i]->getPosition()._x << ", y = " << _projectiles[i]->getPosition()._y << ", z = " << _projectiles[i]->getPosition()._z << std::endl;
			}
		}

		void ShooterGame::updateFrame() {
			GameBase::updateFrame();
			for (int i = 0; i < (int)_projectiles.size(); i++)
			{
				//Push the view matrix so that the transformation only apply to the particule
				glPushMatrix();
				_projectiles[i]->updateFrame();
				glPopMatrix();
			}
		}

	}
}