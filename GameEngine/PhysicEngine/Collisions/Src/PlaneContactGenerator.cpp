#include <PhysicEngine/Collisions/Header/PlaneContactGenerator.hpp>
namespace PhysicEngine {
	namespace Collisions {

		PlaneContactGenerator::PlaneContactGenerator(SceneGraph::CHorizontalPlane* p_plane, PhysicEngine::CParticle* p_particles, unsigned arraySize)
		{
			_plane = std::make_shared<SceneGraph::CHorizontalPlane>(*p_plane);
			for (unsigned i = 0; i < arraySize; i++) {
				_particles.push_back(std::make_shared<PhysicEngine::CParticle>(p_particles[i]));
			}
		}

		void PlaneContactGenerator::addParticle(CParticle* p_particle)
		{
			_particles.push_back(std::shared_ptr<PhysicEngine::CParticle>(p_particle));
		}

		void PlaneContactGenerator::removeParticle(CParticle* p_particle)
		{
			for (unsigned i = 0; i < _particles.size(); i++) {
				if (_particles[i].get() == p_particle) {
					_particles.erase(_particles.begin()+i);
				}
			}
		}

		unsigned PlaneContactGenerator::AddContact(ParticleContact* p_contact, unsigned p_limit)
		{
			unsigned numContacts = 0;
			unsigned i = 0;

			//we stop looking for contacts once the vector has been completely tested or once the limit of contacts is reached
			while(i<_particles.size() && numContacts<=p_limit) {
				std::shared_ptr<PhysicEngine::CParticle> particle = _particles[i];
				float radius = particle->getSize();
				float penetration = particle->getPosition()._y - _plane->getHeight();
				float distance = particle->getPosition()._y - _plane->getHeight();

				//checking if the particle is intersecting with the plane
				if (std::abs(distance) <= radius && _plane->isAboveOrUnder(particle->getPosition()))
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
					Collisions::ParticleContact* contact = new Collisions::ParticleContact(particle.get(), NULL, 1.f, normal, penetration);
					p_contact[numContacts] = ParticleContact(particle.get(), NULL, 1, normal, penetration);
					numContacts += 1;
				}
				i++;
			}
			return numContacts;
		}
	}
}
