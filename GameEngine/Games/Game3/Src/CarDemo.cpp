#include <Games/Game3/Header/CarDemo.hpp>

namespace Games::Game3 {
	CarDemo::CarDemo() : GameBase(), _gravityAcceleration(-10), _gravity(Vector3(0,_gravityAcceleration,0))
	{

	}

	CarDemo::~CarDemo() {
		_car1 = nullptr;
		_car2 = nullptr;
		ShaderServer::getSingleton()->clear();
		TextureServer::getSingleton()->clear();
	}

	void CarDemo::initGame()
	{
		//1 - We load the shaders
		{
			std::cout << "Init 1 - Loading Shader " << std::endl;
			ShaderServer::getSingleton()->init();
		}
		//Le registery
		_registry = *new Forces::BodyForceRegistry();

		//Point de contact
		_contactPoint = Vector3::ZERO;


		//Creer les deux CCAr
		Vector3 posCar1(-100, 0, 0);
		Vector3 posCar2(0, 0, -100);

		PhysicEngine::Quaternion car1Orientation = Quaternion::identity();
		PhysicEngine::Quaternion car2Orientation = Quaternion(0.f,Vector3(0.7,0,0.7));

		_car1 = std::make_shared<SceneGraph::CCar>(posCar1, 10.f, car1Orientation, Vector3(10, 0, 0), Vector3::ZERO, 0.99f, 0.99f);
		_car2 = std::make_shared<SceneGraph::CCar>(posCar2, 10.f, car2Orientation, Vector3(0, 0, 10), Vector3::ZERO, 0.99f, 0.99f);

		// 4 - Create planes
		_ground = std::make_shared<HorizontalPlane>(Vector3(0.f, -40.f, 0), 100.f, 30.f, Vector3(0.4f, 0.9f, 0.f), Vector3(0.1f, 0.1f, 0.1f));
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
		//Test sur la distance 
		Vector3 car1_dim = _car1->getDim();
		Vector3 car2_dim = _car2->getDim();

		if ((_car1->_abstraction->getPosition() - _contactPoint).magnitude() < car1_dim._x / 2)
		{
			if ((_car2->_abstraction->getPosition() - _contactPoint).magnitude() < car2_dim._z / 2)
			{
				std::cout << "collisiiion !" << std::endl;
			}
		}
		_registry.updatePhysic(p_dt);
		_car1->_abstraction->integrate(p_dt);
		_car2->_abstraction->integrate(p_dt);
		_registry.clear();
	}

	void CarDemo::updateFrame() {
		GameBase::updateFrame();
		/*// 0 - Update Camera position 
		cameraFollowMaster();

		// 1 - Matrices and initialisations
		ShaderProgram* currentShader = nullptr;
		glm::mat4 projectionMatrix = glm::perspective(glm::radians<float>(_configuration.getFOV()), (float)getConfiguration().getWindowWidth() / (float)getConfiguration().getWindowHeight(), _configuration.getNearPlane(), _configuration.getFarPlane());
		glm::mat4 viewMatrix = _camera.getInverseTransform();
		// View matrix that only gets the rotation from the view 
		glm::mat4 noTranslationMatrix = glm::mat4(glm::mat3(viewMatrix));

		glm::vec3 lightDirection = glm::normalize(glm::vec3(0.4f, -0.3f, -1.0f));
		glm::vec3 lightColor = glm::vec3(1, 1, 1);
		GLenum textAttachment = GL_COLOR_ATTACHMENT0;

		// 2 - Bind Frame Buffer to render
		ShaderServer::getSingleton()->bindScreenTo(WATER, FBOAttachment::colorAttachment0);

		// 3 - Draw a skybox
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
			_water->draw(shaderUsed);
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				_particles[i]->updateFrame();
			}
			ShaderServer::getSingleton()->unuse(currentShader);
		}

		// 6 - Binding original Frame Buffer
		ShaderServer::getSingleton()->unbindsScreen();

		// 7 - Gaussian Filter
		{
			ShaderServer::getSingleton()->use(WATER, currentShader);

			//Compute camera frustum
			//float fov = std::atan(1.f / projectionMatrix[1][1]) * 2.f * (180 / PI);
			float fov = _configuration.getFOV();
			float aspect = projectionMatrix[1][1] / projectionMatrix[0][0];

			// Depth of the nearer limit of the water is : abs(zAxis - (30/2))
			float depth = 66.f;
			float heightScreenAtDepth = 2.f * depth * std::tan(glm::radians<float>(fov * 0.5f));

			float waterHeight = (_camera.getPosition().y - _water->getHeight()) / (heightScreenAtDepth / 2);
			if (_water->getHeight() < 0) waterHeight *= -1;
			waterHeight = std::max(std::min(waterHeight, 1.f), -1.f);

			float ScreenNearWidth = heightScreenAtDepth * aspect;
			float waterNearLeftLimit = (_camera.getPosition().x + 250) / ScreenNearWidth;
			float waterNearRightLimit = (_camera.getPosition().x - 250) / ScreenNearWidth;

			depth = 95.f;
			float heightScreenAtFarDepth = 2.f * depth * std::tan(glm::radians<float>(fov * 0.5f));
			float ScreenFarWidth = heightScreenAtFarDepth * aspect;
			float waterFarLeftLimit = (_camera.getPosition().x + 250) / ScreenFarWidth;
			float waterFarRightLimit = (_camera.getPosition().x - 250) / ScreenFarWidth;


			float waterLeftLimit = 0;
			if (waterNearLeftLimit > waterFarLeftLimit) waterLeftLimit = std::max(std::min(waterFarLeftLimit, 1.f), -1.f) * -1.f;
			else waterLeftLimit = std::max(std::min(waterNearLeftLimit, 1.f), -1.f) * -1.f;
			float waterRightLimit = 0;
			if (waterNearRightLimit > waterFarRightLimit) waterRightLimit = std::max(std::min(waterNearRightLimit, 1.f), -1.f) * -1.f;
			else waterRightLimit = std::max(std::min(waterFarRightLimit, 1.f), -1.f) * -1.f;

			currentShader->trySetUniform("uni_waterRightLimit", waterRightLimit);
			currentShader->trySetUniform("uni_waterLeftLimit", waterLeftLimit);
			currentShader->trySetUniform("uni_waterHeight", waterHeight);
			currentShader->trySetUniform("uni_waterColor", glm::vec3(0.32f, 0.76f, 0.78f));
			currentShader->trySetUniform("uni_blendCoefficient", 0.8f);
			((VFXShader*)currentShader)->renderScreen();

			ShaderServer::getSingleton()->unuse(currentShader);
		}*/
	}
}