#include <Games/Game2/Header/BlobGame.hpp>

namespace Games {
	namespace Game2 {
		Blob::Blob() : GameBase(), _contactResolver(NUM_PARTICLES*2)
		{
		}

		void Blob::initGame()
		{
			_registry = *new Forces::ParticleForceRegistry();

			// Binding Keys
			_keyboard.bindActionToKey(KeyAction::BREAKBLOB, 98);
			_keyboard.bindActionToKey(KeyAction::FUSEBLOB, 102);

			// Create particles
			Vector3 position(-5, 1, -30);
			Vector3 color(1, 1, 1);
			float radius = 3;
			_particles[0] = std::make_shared<CParticle>(1, position, Vector3::ZERO, Vector3::ZERO, 0.999, Vector3(1,0,0), radius);
			position = Vector3(5, 1, -30);
			_particles[1] = std::make_shared<CParticle>(1, position, Vector3::ZERO, Vector3::ZERO, 0.999, color, radius);
			position = Vector3(0, 4, -30);
			_particles[2] = std::make_shared<CParticle>(1, position, Vector3::ZERO, Vector3::ZERO, 0.999, color, radius);

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
				_particles[0]->setPosition(_particles[0]->getPosition() + Vector3::UP * 0.01);
			}
			if (_keyboard.isPressed(KeyAction::MOVEBACK))
			{
				_particles[0]->setPosition(_particles[0]->getPosition() + Vector3::DOWN * 0.01);
			}
			if (_keyboard.isPressed(KeyAction::MOVELEFT))
			{
				_particles[0]->setPosition(_particles[0]->getPosition() + Vector3::LEFT * 0.01);
			}
			if (_keyboard.isPressed(KeyAction::MOVERIGHT))
			{
				_particles[0]->setPosition(_particles[0]->getPosition() + Vector3::RIGHT * 0.01);
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
			if (!isBroken)
			{
				_registry.add(_particles[0].get(), _springs[1].get());
				_registry.add(_particles[1].get(), _springs[0].get());

				_registry.add(_particles[0].get(), _springs[5].get());
				_registry.add(_particles[2].get(), _springs[4].get());

				_registry.add(_particles[1].get(), _springs[3].get());
				_registry.add(_particles[2].get(), _springs[2].get());
			}

			_registry.updatePhysic(p_dt);
			checkCollisions(p_dt);
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				_particles[i]->updatePhysic(p_dt);
				//the positions of the particles are printed in the console
				std::cout << "index = " << i << ", x = " << _particles[i]->getPosition()._x << ", y = " << _particles[i]->getPosition()._y << ", z = " << _particles[i]->getPosition()._z << std::endl;
			}

			_registry.clear();
		}

		void Blob::updateFrame() {
			GameBase::updateFrame();
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				//Push the view matrix so that the transformation only apply to the particule
				glPushMatrix();
				_particles[i]->updateFrame();
				glPopMatrix();
			}
		}

		void Blob::checkCollisions(float p_dt)
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
						Collisions::ParticleContact* contact = new Collisions::ParticleContact(_particles[i].get(), _particles[j].get(), 0.7, direction, penetration);
						contacts.push_back(contact);
					}
				}
			}

			// Resolve contacts
			_contactResolver.resolveContacts(contacts, p_dt);
		}
	}
}
