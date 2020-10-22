#include <Games/Game2/Header/BlobGame.hpp>

namespace Games {
	namespace Game2 {
		Blob::Blob() : GameBase(), _contactResolver(NUM_PARTICLES*2)
		{
		}

		void Blob::initGame()
		{
		}

		void Blob::handleInput()
		{
			if (_keyboard.isPressed(KeyAction::QUIT)) {
				quit();
			}

			// Move blob / break blob
		}

		void Blob::updatePhysic(double p_dt)
		{
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
					Vector3 direction = _particles[i].get()->getPosition() - _particles[j].get()->getPosition();
					float distance = direction.magnitude();
					float totalSize = _particles[i].get()->getSize() + _particles[i].get()->getSize();
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
