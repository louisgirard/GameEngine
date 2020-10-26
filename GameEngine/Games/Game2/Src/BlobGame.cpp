#include <Games/Game2/Header/BlobGame.hpp>

namespace Games {
	namespace Game2 {
		Blob::Blob() : GameBase(), _contactResolver(NUM_PARTICLES*2), _gravity(Forces::ParticleGravity(Vector3(0, -10, 0)))
		{
		}

		void Blob::initGame()
		{
			_registry = *new Forces::ParticleForceRegistry();

			// Binding Keys
			_keyboard.bindActionToKey(KeyAction::BREAKBLOB, 98);
			_keyboard.bindActionToKey(KeyAction::FUSEBLOB, 102);

			// Create planes
			_ground = std::make_shared<CHorizontalPlane>(Vector3(0, -10, -30), 30, 30);

			// Create particles
			Vector3 position(-5, 1, -30);
			Vector3 color(1, 1, 1);
			float radius = 3;
			_particles[0] = std::make_shared<CParticle>(1.f, position, Vector3::ZERO, Vector3::ZERO, 0.999f, Vector3(1.f,0.f,0.f), radius);
			position = Vector3(5, 1, -30);
			_particles[1] = std::make_shared<CParticle>(1.f, position, Vector3::ZERO, Vector3::ZERO, 0.999f, color, radius);
			position = Vector3(0, 4, -30);
			_particles[2] = std::make_shared<CParticle>(1.f, position, Vector3::ZERO, Vector3::ZERO, 0.999f, color, radius);

			// Add springs
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

		void Blob::handleInput()
		{
			if (_keyboard.isPressed(KeyAction::QUIT)) {
				quit();
			}

			// Move blob
			if (_keyboard.isPressed(KeyAction::MOVEFRONT))
			{
				_particles[0]->setPosition(_particles[0]->getPosition() + Vector3::UP * 0.01f);
			}
			if (_keyboard.isPressed(KeyAction::MOVEBACK))
			{
				_particles[0]->setPosition(_particles[0]->getPosition() + Vector3::DOWN * 0.01f);
			}
			if (_keyboard.isPressed(KeyAction::MOVELEFT))
			{
				_particles[0]->setPosition(_particles[0]->getPosition() + Vector3::LEFT * 0.01f);
			}
			if (_keyboard.isPressed(KeyAction::MOVERIGHT))
			{
				_particles[0]->setPosition(_particles[0]->getPosition() + Vector3::RIGHT * 0.01f);
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

<<<<<<< HEAD
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				_registry.add(_particles[i].get(), &_gravity);
			}

			_registry.updatePhysic(p_dt);

			// Check for collisions
			checkParticleCollisions(p_dt);
			checkGroundCollisions(p_dt);
=======
			_registry.updatePhysic((float)p_dt);
			checkParticleCollisions((float)p_dt);
			checkGroundCollisions((float)p_dt);
>>>>>>> f2de7413d2c15b91877c00b26442a9ffff6e9dbf

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

			// Display Ground
			glPushMatrix();
			_ground->updateFrame();
			glPopMatrix();

			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				//Push the view matrix so that the transformation only apply to the particule
				glPushMatrix();
				_particles[i]->updateFrame();
				glPopMatrix();
			}
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
				float penetration = _particles[i]->getPosition()._y - _ground->getHeight();

				// checking if the particle is intersecting with the plane
				if (std::abs(penetration) <= radius && _ground->isAboveOrUnder(_particles[i]->getPosition()))
				{
					Vector3 normal;
					//checking if the contact is happening from above or under
					if (penetration > 0) {
						normal = PhysicEngine::Vector3::UP;
					}
					else {
						normal = PhysicEngine::Vector3::UP * -1;
						penetration *= -1;
					}
					Collisions::ParticleContact* contact = new Collisions::ParticleContact(_particles[i].get(), NULL, 1.f, normal * 0.01f, penetration);
					contacts.push_back(contact);
				}
			}

			// Resolve contacts
			_contactResolver.resolveContacts(contacts, p_dt);
		}
	}
}
