#include <Games/Game2/Header/BlobGame.hpp>

namespace Games {
	namespace Game2 {

		const std::string Blob::WATER = "Water";

		Blob::Blob() : GameBase(), _contactResolver(NUM_PARTICLES*2), _gravityAcceleration(-10), _gravity(Forces::ParticleGravity(Vector3(0, _gravityAcceleration, 0)))
		{
		}

		Blob::~Blob() {
			ShaderServer::getSingleton()->clear();
			SceneServer::getSingleton()->clear();
		}

		void Blob::initGame()
		{
			// 0 - Init variable 
			_registry = *new Forces::ParticleForceRegistry();
			float zAxis = -80;

			// 1 - We load the shaders
			{
				std::cout << "Init 1 - Loading Shader " << std::endl;
				ShaderServer::getSingleton()->init();
				ShaderServer::getSingleton()->loadAndRegisterShader(GraphicEngine::ShaderProgramType::VFX, WATER, "water.vert", "water.frag");
			}

			// 2 - We initialize multi-pass rendering
			std::vector<std::tuple<FBOAttachment, FBOAttachmentType, TextureInternalFormat>> configuration;
			configuration.push_back(std::tuple(FBOAttachment::colorAttachment0, FBOAttachmentType::texture, TextureInternalFormat::rgba));
			ShaderServer::getSingleton()->initVFX(WATER, configuration, getConfiguration().getWindowWidth(), getConfiguration().getWindowHeight());

			// 3 - Binding Keys
			_keyboard.bindActionToKey(KeyAction::BREAKBLOB, 98);
			_keyboard.bindActionToKey(KeyAction::FUSEBLOB, 102);

			// 4 - Create planes
			_ground = std::make_shared<HorizontalPlane>(Vector3(0, -40, zAxis), 60, 30);
			_water = std::make_shared<HorizontalPlane>(Vector3(0, -50, zAxis), 500, 30, Vector3(0.32f, 0.76f, 0.78f), Vector3(0.8f, 0.8f, 0.8f));

			// 5 -  Create particles
			float mass = 60000;
			Vector3 position(-5, -38, zAxis);
			Vector3 color(1, 1, 1);
			float radius = 3;
			_particles[0] = std::make_shared<CParticle>(mass, position, Vector3::ZERO, Vector3::ZERO, 0.999f, Vector3(1.f,0.f,0.f), radius);
			position = Vector3(5, -38, zAxis);
			_particles[1] = std::make_shared<CParticle>(mass, position, Vector3::ZERO, Vector3::ZERO, 0.999f, color, radius);
			position = Vector3(0, -35, zAxis);
			_particles[2] = std::make_shared<CParticle>(mass, position, Vector3::ZERO, Vector3::ZERO, 0.999f, color, radius);

			// 6 - Add springs
			auto spring1 = std::make_shared<SpringForces::ParticleSpring>(_particles[0].get(), 2, 10);
			auto spring2 = std::make_shared<SpringForces::ParticleSpring>(_particles[1].get(), 2, 10);
			_springs.push_back(spring1);
			_springs.push_back(spring2);

			auto spring3 = std::make_shared<SpringForces::ParticleSpring>(_particles[1].get(), 2, 10);
			auto spring4 = std::make_shared<SpringForces::ParticleSpring>(_particles[2].get(), 2, 10);
			_springs.push_back(spring3);
			_springs.push_back(spring4);

			auto spring5 = std::make_shared<SpringForces::ParticleSpring>(_particles[0].get(), 2, 10);
			auto spring6 = std::make_shared<SpringForces::ParticleSpring>(_particles[2].get(), 2, 10);
			_springs.push_back(spring5);
			_springs.push_back(spring6);
		}

		void Blob::handleInput(double p_dt)
		{
			if (_keyboard.isPressed(KeyAction::QUIT)) {
				quit();
			}

			// Move blob
			if (_keyboard.isPressed(KeyAction::MOVEFRONT))
			{
				_registry.add(_particles[0].get(), new Forces::ParticleGravity(Vector3(0, 50, 0)));
			}
			if (_keyboard.isPressed(KeyAction::MOVEBACK))
			{
				_registry.add(_particles[0].get(), new Forces::ParticleGravity(Vector3(0, -10, 0)));
			}
			if (_keyboard.isPressed(KeyAction::MOVELEFT))
			{
				_registry.add(_particles[0].get(), new Forces::ParticleGravity(Vector3(-10, 0, 0)));
			}
			if (_keyboard.isPressed(KeyAction::MOVERIGHT))
			{
				_registry.add(_particles[0].get(), new Forces::ParticleGravity(Vector3(10, 0, 0)));
			}

			// Break blob
			if (_keyboard.isPressed(KeyAction::BREAKBLOB))
			{
				isBroken = true;
			}
			if (_keyboard.isPressed(KeyAction::FUSEBLOB))
			{
				isBroken = false;
			}
		}

		void Blob::reshape(GLint p_width, GLint p_height) {
			GameBase::reshape(p_width, p_height);
			ShaderServer::getSingleton()->resizeScreen(p_width, p_height);
		}

		void Blob::updatePhysic(double p_dt)
		{
			// Add forces
			if (!isBroken)
			{
				_registry.add(_particles[0].get(), _springs[1].get());
				_registry.add(_particles[1].get(), _springs[0].get());

				_registry.add(_particles[0].get(), _springs[5].get());
				_registry.add(_particles[2].get(), _springs[4].get());

				_registry.add(_particles[1].get(), _springs[3].get());
				_registry.add(_particles[2].get(), _springs[2].get());
			}

			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				_registry.add(_particles[i].get(), &_gravity);
			}

			checkWaterInteraction(p_dt);

			_registry.updatePhysic(p_dt);

			// Check for collisions
			checkParticleCollisions(p_dt);
			checkGroundCollisions(p_dt);

			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				_particles[i]->updatePhysic((float)p_dt);
				//the positions of the particles are printed in the console
				//std::cout << "index = " << i << ", x = " << _particles[i]->getPosition()._x << ", y = " << _particles[i]->getPosition()._y << ", z = " << _particles[i]->getPosition()._z << std::endl;
			}

			_registry.clear();
		}

		void Blob::updateFrame() {
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

				// Depth of the nearer limit of the water is : abs(zAxis - (30/2))
				float depth = 66.f;
				float heightScreenAtDepth = 2.f * depth * std::tan(glm::radians<float>(fov * 0.5f));

				float waterHeight = (_camera.getPosition().y - _water->getHeight()) / (heightScreenAtDepth /2);
				if (_water->getHeight() < 0) waterHeight *= -1;
				waterHeight = std::max(std::min(waterHeight, 1.f), -1.f);

				currentShader->trySetUniform("uni_waterHeight", waterHeight);
				currentShader->trySetUniform("uni_waterColor", glm::vec3(0.32f, 0.76f, 0.78f));
				currentShader->trySetUniform("uni_blendCoefficient", 0.8f);
				((VFXShader*)currentShader)->renderScreen();

				ShaderServer::getSingleton()->unuse(currentShader);
			}
		}

		void Blob::cameraFollowMaster()
		{
			Vector3 position = _particles[0]->getPosition();
			_camera.setPosition(glm::vec3(position._x, position._y, 0.5));

			
		}

		void Blob::checkParticleCollisions(float p_dt)
		{
			std::vector<Collisions::ParticleContact*> contacts;
			// For all particles, check if in collision with other particles
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				for (int j = i + 1; j < NUM_PARTICLES; j++)
				{
					Vector3 direction = _particles[i]->getPosition() - _particles[j]->getPosition();
					float distance = direction.magnitude();
					float totalSize = _particles[i]->getSize() + _particles[i]->getSize();
					// If distance < radius1 + radius2 -> collision
					if (distance < totalSize)
					{
						float penetration = totalSize - distance;
						direction.normalize();
						// Create contact
						Collisions::ParticleContact* contact = new Collisions::ParticleContact(_particles[i].get(), _particles[j].get(), 0.7f, direction, penetration);
						contacts.push_back(contact);
					}
				}
			}

			// Resolve contacts
			_contactResolver.resolveContacts(contacts, p_dt);
		}

		void Blob::checkGroundCollisions(float p_dt)
		{
			std::vector<Collisions::ParticleContact*> contacts;
			// For all particles, check if in collision with the ground
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				float radius = _particles[i]->getSize();

				float distance = _particles[i]->getPosition()._y - _ground->getHeight();

				// checking if the particle is intersecting with the plane
				if (std::abs(distance) <= radius && _ground->isAboveOrUnder(_particles[i]->getPosition()))
				{
					float penetration = distance - radius;
					Vector3 normal;
					//checking if the contact is happening from above or under
					if (distance > 0) {
						normal = PhysicEngine::Vector3::UP;
					}
					else {
						normal = PhysicEngine::Vector3::UP * -1;
					}
					Collisions::ParticleContact* contact = new Collisions::ParticleContact(_particles[i].get(), NULL, 1.f, normal, penetration);
					contacts.push_back(contact);
				}
			}

			// Resolve contacts
			_contactResolver.resolveContacts(contacts, p_dt);
		}

		void Blob::checkWaterInteraction(float p_dt)
		{
			// For all particles, check if in collision with the water
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				if (_water->isAboveOrUnder(_particles[i]->getPosition()))
				{
					SpringForces::ParticleBuoyancy* buoyancy = new SpringForces::ParticleBuoyancy(_particles[i]->getSize(), 4/3*PI*std::pow(_particles[i]->getSize(),3), _water->getHeight(), _gravityAcceleration);
					_registry.add(_particles[i].get(), buoyancy);
				}
			}
		}
	}
}
