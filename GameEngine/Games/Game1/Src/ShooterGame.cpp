#include <Games/Game1/Header/ShooterGame.hpp>

namespace Games {
	namespace Game1 {

		ShooterGame::ShooterGame() :GameBase() , _weaponMenu(new Games::GameMenu("Weapon Pocket")), _gravityGenerator(*new Gravity(*new PhysicEngine::Vector3(0, -10, 0))) {}

		ShooterGame::~ShooterGame() {
			ShaderServer::getSingleton()->clear();
			TextureServer::getSingleton()->clear();
		}

		void ShooterGame::initGame() {

			_registry = *new ForceRegistry();

			// 1 - We load the shaders
			{
				std::cout << "Init 1 - Loading Shader " << std::endl;
				ShaderServer::getSingleton()->init();
			}
			
			// 2- Binding Keys
			_keyboard.bindActionToKey(KeyAction::MAINACTION, 13);

			// 3 - We create a sub menu for choosing a weapon
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

		void ShooterGame::handleInput(double p_dt) {
			GameBase::handleInput(p_dt);

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
			// 0 - Matrices and initialisations
			ShaderProgram* currentShader = nullptr;
			glm::mat4 projectionMatrix = glm::perspective(glm::radians<float>(_configuration.getFOV()), (float)getConfiguration().getWindowWidth() / (float)getConfiguration().getWindowHeight(), _configuration.getNearPlane(), _configuration.getFarPlane());
			glm::mat4 viewMatrix = _camera.getInverseTransform();

			glm::vec3 lightDirection = glm::normalize(glm::vec3(0.4f, 0.3f, 1.0f));
			glm::vec3 lightColor = glm::vec3(1, 1, 1);

			// 1 - Display object that use phong shader
			{
				std::string shaderUsed = ShaderServer::getSingleton()->getDefaultMeshShader();
				ShaderServer::getSingleton()->use(shaderUsed, currentShader);
				// We initialize the uniforms shared by every mesh
				((MeshShader*)currentShader)->setProjectionTransform(projectionMatrix);
				((MeshShader*)currentShader)->setViewTransform(viewMatrix);
				((MeshShader*)currentShader)->setViewPosition(_camera.getPosition());
				((MeshShader*)currentShader)->setLights(lightDirection, lightColor);
				((MeshShader*)currentShader)->setClippingDistance(_configuration.getFarPlane());
				((MeshShader*)currentShader)->setEnvTexture(ShaderServer::getSingleton()->getSkyboxTexture());
				// We draw the mesh related to this shader 
				for (int i = 0; i < (int)_projectiles.size(); i++)
				{
					_projectiles[i]->updateFrame();
				}
				ShaderServer::getSingleton()->unuse(currentShader);
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