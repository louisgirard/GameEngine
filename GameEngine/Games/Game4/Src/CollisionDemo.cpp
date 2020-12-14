#include <Games/Game4/Header/CollisionDemo.hpp>

namespace Games::Game4 {
	CollisionDemo::CollisionDemo() : GameBase()
	{

	}

	CollisionDemo::~CollisionDemo()
	{
		ShaderServer::getSingleton()->clear();
		TextureServer::getSingleton()->clear();
		SceneServer::getSingleton()->clear();
	}

	void CollisionDemo::initGame()
	{
		//1 - We load the shaders
		{
			std::cout << "Init 1 - Loading Shader " << std::endl;
			ShaderServer::getSingleton()->init();
		}

		Vector3 cubePos(0, 10, 0);

		// 0 - Init Camera

		Vector3 camera_position = cubePos + Vector3(0,0,10);
		_camera.setPosition(Vector3::toGlm(camera_position));

		//Init 6 walls
		float l = 50;
		float w = 50;
		_tabWall.push_back(SceneGraph::CWall(Vector3(0, 0, 0), Vector3(0, 1, 0), l, w));
		_tabWall.push_back(SceneGraph::CWall(Vector3(0, w, 0), Vector3(0, -1, 0), l, w));
		_tabWall.push_back(SceneGraph::CWall(Vector3(0, 0, -l / 2), Vector3(0, 0, -1), l, w));
		_tabWall.push_back(SceneGraph::CWall(Vector3(0, 0, l / 2), Vector3(0, 0, 1), l, w));
		_tabWall.push_back(SceneGraph::CWall(Vector3(l / 2, 0, 0), Vector3(-1, 0, 0), l, w));
		_tabWall.push_back(SceneGraph::CWall(Vector3(-l / 2, 0, 0), Vector3(1, 0, 0), l, w));

		//Init Cube
		_cube = std::make_shared<SceneGraph::CCube>(cubePos, Vector3(10, 10, 10), 10, 3);

		/*std::vector<PhysicEngine::Collisions::Collider*> colliders;
		for (int i = 0; i < _tabWall.size(); i++)
		{
			colliders.insert(colliders.end(), _tabWall[i].getColliders().begin(), _tabWall[i].getColliders().end());
		}
		colliders.insert(colliders.end(), _cube->getColliders().begin(), _cube->getColliders().end());

		//Octree
		_octree = std::make_shared<PhysicEngine::Collisions::Octree>(20, 20, colliders);*/
	}

	void CollisionDemo::handleInput(double p_dt)
	{
		GameBase::handleInput(p_dt);
	}

	void CollisionDemo::updatePhysic(double p_dt)
	{
		//Update Tree
		//_octree->build()

		//Get possible collisions

		//To NarrowPhaseCollisions
	}

	void CollisionDemo::updateFrame()
	{
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
			for (int i = 0; i < _tabWall.size(); i++)
			{
				_tabWall[i].draw(shaderUsed);
			}
			_cube->draw(shaderUsed);
			ShaderServer::getSingleton()->unuse(currentShader);
		}
	}

	void CollisionDemo::narrowPhaseCollisions(std::vector<std::vector<PhysicEngine::Collisions::Collider*>>& p_possibleCollisions)
	{
		for (int i = 0; i < p_possibleCollisions.size(); i++)
		{
			std::vector<PhysicEngine::Collisions::Collider*> colliders = p_possibleCollisions[i];
			for (int j = 0; j < colliders.size(); j++)
			{
				for (int k = j + 1; k < colliders.size(); k++)
				{
					PhysicEngine::Collisions::CollisionData collisionData;
					// Check if the two colliders are collected and resolve the collision
					bool collided = colliders[j]->resolveCollision(*colliders[k], &collisionData);
					if (collided)
					{
						_collisionsData.push_back(collisionData);
					}
				}
			}
		}
	}
}