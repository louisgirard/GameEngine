#include <Games/Game2/Header/BlobGame.hpp>

namespace Games {
	namespace Game2 {
		Blob::Blob() : GameBase(), _contactResolver(NUM_PARTICLES*2)
		{
		}

		void Blob::initGame()
		{
			_registry = *new Forces::ParticleForceRegistry();

			// Create particles
			Vector3 position(-5, 1, -30);
			Vector3 color(1, 1, 1);
			float radius = 3;
			_particles[0] = std::make_shared<CParticle>(1, position, Vector3::ZERO, Vector3::ZERO, 0.999, color, radius);
			position = Vector3(5, 1, -30);
			_particles[1] = std::make_shared<CParticle>(1, position, Vector3::ZERO, Vector3::ZERO, 0.999, color, radius);

			// Add springs
			SpringForces::ParticleSpring* spring1 = new SpringForces::ParticleSpring(_particles[0].get(), 2, 10);
			SpringForces::ParticleSpring* spring2 = new SpringForces::ParticleSpring(_particles[1].get(), 2, 10);
			_registry.add(_particles[0].get(), spring2);
			_registry.add(_particles[1].get(), spring1);
		}

		void Blob::handleInput()
		{
			if (_keyboard.isPressed(KeyAction::QUIT)) {
				quit();
			}

			// Move blob / break blob
			_particles[0]->setAcceleration(Vector3::ZERO);
			_registry.add(_particles[0].get(), new Forces::ParticleGravity(*new Vector3(-0.001, 0, 0)));
			_registry.add(_particles[1].get(), new Forces::ParticleGravity(*new Vector3(0, -0.001, 0)));
		}

		void Blob::updatePhysic(double p_dt)
		{
			_registry.updatePhysic(p_dt);
			for (int i = 0; i < NUM_PARTICLES; i++)
			{
				_particles[i]->updatePhysic(p_dt);
				//the positions of the particles are printed in the console
				std::cout << "index = " << i << ", x = " << _particles[i]->getPosition()._x << ", y = " << _particles[i]->getPosition()._y << ", z = " << _particles[i]->getPosition()._z << std::endl;
			}
			checkCollisions(p_dt);
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
