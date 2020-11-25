#include <Games/Game3/Header/RigidBodyDemo.hpp>

namespace Games::Game3 {
	RigidBodyDemo::RigidBodyDemo() : GameBase() , _gravityAcceleration(-10), _gravity(Forces::BodyGravity(Vector3(0, _gravityAcceleration, 0))), _launch(true),_savePhysicTime(0), _saveTime(0)
	{
	}

	RigidBodyDemo::~RigidBodyDemo() {
		_cube = nullptr;
		ShaderServer::getSingleton()->clear();
		TextureServer::getSingleton()->clear();
		SceneServer::getSingleton()->clear();
	}

	void RigidBodyDemo::initGame()
	{
		glDisable(GL_CULL_FACE);
		// 1 - Init variable
		_registry = *new Forces::BodyForceRegistry();
		Vector3 velocity = Vector3::ZERO;
		Vector3 angularVelocity = Vector3::ZERO;
		Vector3 dim(3, 1, 2);
		Vector3 center(5, dim._y/2, 0);
		std::vector<float> mass = { 0.1f,5,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f };
		PhysicEngine::Quaternion orientation(Quaternion::identity());
		float damping = 0.99f;
		float angularDamping = 0.99f;

		// 0 - Init Camera
		_camera.setPosition(Vector3::toGlm(center+Vector3(0,0, dim._z + 10)));

		// 2 - We load the shaders
		{
			std::cout << "Init 1 - Loading Shader " << std::endl;
			ShaderServer::getSingleton()->init();
		}

		// 3 - Create body
		_cube = std::make_shared<SceneGraph::CIrregularCube>(center, dim, mass, orientation,velocity,angularVelocity,damping,angularDamping);

		// 4 - Add force to registery
		_registry.add((_cube->_abstraction.get()),&_gravity);

		// 5 - Create planes
		_ground = std::make_shared<HorizontalPlane>(Vector3(0.f, 0, 0), 50.f, 50.f, Vector3(0.4f, 0.9f, 0.f), Vector3(0.1f, 0.1f, 0.1f));
	}

	void RigidBodyDemo::handleInput(double p_dt)
	{
		GameBase::handleInput(p_dt);
	}

	void RigidBodyDemo::updatePhysic(double p_dt)
	{
		// from first frame and during 0.5s we add a force to laucnh the cube in the air
		if (_launch) {
			_cube->_abstraction->addForceAtLocalPoint(Vector3(0, 75*(1/p_dt), 0), Vector3(0.3,0,0));
			/*_savePhysicTime += p_dt;
			if (_savePhysicTime > 0.5)*/ _launch = false;
		}
		//Physic Update
		_registry.updatePhysic(p_dt);
		_cube->_abstraction->integrate(p_dt);
	}

	void RigidBodyDemo::updateFrame() {
		GameBase::updateFrame();
		// 0 - Update Camera position
		//cameraFollowMaster();

		if (_saveTime > 0.2) {
			_cube->markOrigin();
			_saveTime = 0;
		}
		_saveTime += getDt();


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
			_cube->draw(shaderUsed);
			ShaderServer::getSingleton()->unuse(currentShader);
		}
	}
	void RigidBodyDemo::cameraFollowMaster()
	{
		Vector3 position = _cube->_abstraction->_position;
		_camera.setPosition(glm::vec3(position._x, position._y, 0.5));
	}
}