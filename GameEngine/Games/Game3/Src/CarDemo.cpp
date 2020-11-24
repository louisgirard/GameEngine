#include <Games/Game3/Header/CarDemo.hpp>

namespace Games::Game3 {
	CarDemo::CarDemo() : GameBase(), _collision(false){

	}

	CarDemo::~CarDemo() {

		_car1 = nullptr;
		_car2 = nullptr;
		ShaderServer::getSingleton()->clear();
		TextureServer::getSingleton()->clear();
		SceneServer::getSingleton()->clear();
	}

	void CarDemo::initGame()
	{
		//1 - We load the shaders
		{
			std::cout << "Init 1 - Loading Shader " << std::endl;
			ShaderServer::getSingleton()->init();
		}

		// 2 - Init Camera
		_camera.setPosition(Vector3::toGlm(Vector3(0, 50,0)));
		_camera.rotateLocal(Vector3::toGlm((Vector3(1, 0, 0))),-PI/2);

		// 3 - Init contact point
		_contactPoint = Vector3::ZERO;

		// 4 - Init Car
		Vector3 center1 = Vector3(1.9593, 1.34115, -50);
		Vector3 center2 = Vector3(-50, 1.34115, 0);

		PhysicEngine::Quaternion car1Orientation = Quaternion::identity();
		// Rotate from 90 in Y axis
		PhysicEngine::Quaternion car2Orientation = Quaternion(0.7071068,Vector3(0, 0.7071068,0));

		float speed = 30;
		_car1 = std::make_shared<SceneGraph::CCar>(center1, 10.f, car1Orientation, Vector3(0, 0, speed), Vector3::ZERO, 0.99f, 0.99f);
		_car2 = std::make_shared<SceneGraph::CCar>(center2, 10.f, car2Orientation, Vector3(speed, 0, 0), Vector3::ZERO, 0.99f, 0.99f);

		// 4 - Create planes
		_ground = std::make_shared<HorizontalPlane>(Vector3(0.f, 0.f, 0), 100.f, 100.f, Vector3(0.4f, 0.4f, 0.4f), Vector3(0.1f, 0.1f, 0.1f));
	}

	void CarDemo::handleInput(double p_dt)
	{
		GameBase::handleInput(p_dt);
	}

	void CarDemo::reshape(GLint p_width, GLint p_height) {
		GameBase::reshape(p_width, p_height);
		/*ShaderServer::getSingleton()->resizeScreen(p_width, p_height);*/
	}

	void CarDemo::updatePhysic(double p_dt)
	{
		/*If there is a collision we apply a force at the point of the collision*/
		if (!_collision) {
			if (_car1->_abstraction->getPosition()._z >= _contactPoint._z)
			{
				if (_car2->_abstraction->getPosition()._x >= _contactPoint._x)
				{
					float force = 400*(1/p_dt);
					_car1->_abstraction->addForceAtPoint(Vector3(force, 0, 0), _contactPoint + Vector3(0, 1.34115, 0));
					_car2->_abstraction->addForceAtPoint(Vector3(-force, 0, 0), _contactPoint + Vector3(0, 1.34115, 0));
					_collision = true;
				}
			}
		}
		
		//Update car physic
		_car1->_abstraction->integrate(p_dt);
		_car2->_abstraction->integrate(p_dt);
		

		/*std::cout << "Position 1 : " << _car1->_abstraction->_position << std::endl;
		std::cout << "Velocity 1 : " << _car1->_abstraction->_velocity << std::endl;
		std::cout << "Position 2 : " << _car2->_abstraction->_position << std::endl;
		std::cout << "Velocity 2 : " << _car2->_abstraction->_velocity << std::endl;*/
	}

	void CarDemo::updateFrame() {
		GameBase::updateFrame();

		// 1 - Matrices and initialisations
		ShaderProgram* currentShader = nullptr;
		glm::mat4 projectionMatrix = glm::perspective(glm::radians<float>(_configuration.getFOV()), (float)getConfiguration().getWindowWidth() / (float)getConfiguration().getWindowHeight(), _configuration.getNearPlane(), _configuration.getFarPlane());
		glm::mat4 viewMatrix = _camera.getInverseTransform();
		// View matrix that only gets the rotation from the view
		glm::mat4 noTranslationMatrix = glm::mat4(glm::mat3(viewMatrix));

		glm::vec3 lightDirection = glm::normalize(glm::vec3(0.4f, -0.3f, -1.0f));
		glm::vec3 lightColor = glm::vec3(1, 1, 1);
		GLenum textAttachment = GL_COLOR_ATTACHMENT0;

		// 2 - Draw a skybox
		ShaderServer::getSingleton()->renderSkybox(noTranslationMatrix, projectionMatrix);

		// 4 - Display object that use phong shader
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
			_ground->draw(shaderUsed);
			_car1->draw(shaderUsed);
			_car2->draw(shaderUsed);
			ShaderServer::getSingleton()->unuse(currentShader);
		}
	}
}