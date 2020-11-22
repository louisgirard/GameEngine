#include <Games/Game3/Header/RigidBodyDemo.hpp>

namespace Games::Game3 {
	RigidBodyDemo::RigidBodyDemo() : GameBase() , _gravityAcceleration(-10), _gravity(Forces::BodyGravity(Vector3(0, _gravityAcceleration, 0)))
	{
	}

	RigidBodyDemo::~RigidBodyDemo() {
		/*ShaderServer::getSingleton()->clear();
		TextureServer::getSingleton()->clear();*/
	}

	void RigidBodyDemo::initGame()
	{
		// 0 - Init variable
		_registry = *new Forces::BodyForceRegistry();
		Vector3 velocity = *new Vector3(0,1,0);
		Vector3 angularVelocity = *new Vector3(0,0,0);
		Vector3 center(0, 0, 0);
		Vector3 dim(3, 1, 2);
		std::vector<float> mass = {1.0f,2.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f};
		PhysicEngine::Quaternion orientation(Quaternion::identity());
		float damping = 0.99f;
		float angularDamping = 0.99f;

		// 2 - Create body
		_cube = std::make_shared<SceneGraph::CIrregularCube>(center, dim, mass, orientation,velocity,angularVelocity,damping,angularDamping);

		// 3 - Add force to registery
		_registry.add((_cube->_abstraction.get()),&_gravity);

		// 1 - We load the shaders
		{
			std::cout << "Init 1 - Loading Shader " << std::endl;
			ShaderServer::getSingleton()->init();
		}

		// 4 - Create planes
		_ground = std::make_shared<HorizontalPlane>(Vector3(0.f, -40.f, 100.f), 100.f, 30.f, Vector3(0.4f, 0.9f, 0.f), Vector3(0.1f, 0.1f, 0.1f));
	}

	void RigidBodyDemo::handleInput(double p_dt)
	{
		GameBase::handleInput(p_dt);
	}

	void RigidBodyDemo::updatePhysic(double p_dt)
	{
		_registry.updatePhysic(p_dt);
	}

	void RigidBodyDemo::updateFrame() {
		GameBase::updateFrame();
		// 0 - Update Camera position
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