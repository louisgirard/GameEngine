#include <Games/Game1/Header/ShooterGame.hpp>

namespace Games {
	namespace Game1 {

		ShooterGame::ShooterGame() :GameBase() , _weaponMenu(new Games::GameMenu("Weapon Pocket")), _gravityGenerator(*new Gravity(*new PhysicEngine::Vector3(0, -10, 0))) {}

		void ShooterGame::initGame() {
			_registry = *new ForceRegistry();
			// 1- Binding Keys
			_keyboard.bindActionToKey(KeyAction::MAINACTION, 13);
			// 2 - We create a sub menu for choosing a weapon
			_weaponMenu->addItem("Pistol", [this]() {_currentType = Particle::Types::Bullet; });
			_weaponMenu->addItem("Canon", [this]() {_currentType = Particle::Types::Canonball; });
			_weaponMenu->addItem("Laser Gun", [this]() {_currentType = Particle::Types::Laser; });
			_weaponMenu->addItem("Fireball Gun", [this]() {_currentType = Particle::Types::Fireball; });
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
					_projectiles.push_back(std::make_shared<Particle>(_currentType, Vector3::convertGlm(_camera.getPosition()), Vector3::convertGlm(_camera.lookingAt())));
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
			// 1 - Update Camera 
			glMatrixMode(GL_MODELVIEW);
			glMultMatrixf(&(_camera.getInverseTransform()[0][0]));
			// 2 - Display model
			for (int i = 0; i < (int)_projectiles.size(); i++)
			{
				//Push the view matrix so that the transformation only apply to the particule
				glPushMatrix();
				_projectiles[i]->updateFrame();
				glPopMatrix();
			}
		}

		void ShooterGame::mousePassiveMotion(int p_x, int p_y) {
			GameBase::mousePassiveMotion(p_x, p_y);
			glm::vec3 xAxis(1.0, 0.0, 0.0);
			glm::vec3 yAxis(0.0, 1.0, 0.0);

			_camera.rotateLocal(yAxis, -(p_x - _configuration.getWindowWidth() / 2) * _cameraRotationSpeed * (float)getDt());
			_camera.rotateLocal(xAxis, -(p_y - _configuration.getWindowHeight() / 2) * _cameraRotationSpeed * (float)getDt());
			_mouse.setX(p_x);
			_mouse.setY(p_y);
			glutWarpPointer(_configuration.getWindowWidth() / 2, _configuration.getWindowHeight() / 2);
		}

	}
}