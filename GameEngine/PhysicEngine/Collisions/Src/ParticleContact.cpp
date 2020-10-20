#include <PhysicEngine/Collisions/Header/ParticleContact.hpp>

namespace PhysicEngine
{
	namespace Collisions {
		ParticleContact::ParticleContact(CParticle* p_particle1, CParticle* p_particle2, float p_restitutionCoef, Vector3 p_contactNormal, float p_penetration)
		{
			_particles[0] = p_particle1;
			_particles[1] = p_particle2;
			_restitutionCoef = p_restitutionCoef;
			_contactNormal = p_contactNormal;
			_penetration = p_penetration;
		}

		void ParticleContact::resolve(float p_dt)
		{
			resolveVelocity(p_dt);
		}

		float ParticleContact::calculateSeparatingVelocity() const
		{
			if (_particles[1] == nullptr)
			{
				return _particles[0]->getVelocity().scalarProduct(_contactNormal);
			}
			else
			{
				return (_particles[0]->getVelocity() - _particles[1]->getVelocity()).scalarProduct(_contactNormal);
			}
		}

		void ParticleContact::resolveVelocity(float p_dt)
		{
			// Vs
			float separatingVelocity = calculateSeparatingVelocity();
			if (separatingVelocity > 0) return;

			// -cVs
			float newSeparatingVelocity = -separatingVelocity * _restitutionCoef;

			// Check the velocity build-up due to acceleration only
			Vector3 accCausedVelocity = _particles[0]->getAcceleration();
			if (_particles[1] != nullptr) accCausedVelocity -= _particles[1]->getAcceleration();
			float accCausedSeparatingVelocity = accCausedVelocity.scalarProduct(_contactNormal) * p_dt;

			if (accCausedSeparatingVelocity < 0)
			{
				newSeparatingVelocity += _restitutionCoef * accCausedSeparatingVelocity;

				if (newSeparatingVelocity < 0) newSeparatingVelocity = 0;
			}

			// dV
			float deltaVelocity = newSeparatingVelocity - separatingVelocity;

			// Calculate total impulse
			float totalInverseMass = _particles[0]->getInverseMass();
			if (_particles[1] != nullptr) totalInverseMass += _particles[1]->getInverseMass();

			Vector3 totalImpulse = _contactNormal * (deltaVelocity / totalInverseMass);

			// Apply impulse
			_particles[0]->setVelocity(_particles[0]->getVelocity() + totalImpulse * _particles[0]->getInverseMass());
			if (_particles[1] != nullptr)
			{
				_particles[1]->setVelocity(_particles[1]->getVelocity() - totalImpulse * _particles[1]->getInverseMass());
			}
		}

		void ParticleContact::resolveInterpenetration(float p_dt)
		{
			if (_penetration <= 0) return;

			float totalInverseMass = _particles[0]->getInverseMass();
			if (_particles[1] != nullptr) totalInverseMass += _particles[1]->getInverseMass();

			// Movement = n*d*mA*mB / mA + mB
			Vector3 movement = _contactNormal * (_penetration / totalInverseMass);

			_particles[0]->setPosition(_particles[0]->getPosition() + movement * _particles[0]->getInverseMass());
			if (_particles[1] != nullptr)
			{
				_particles[1]->setVelocity(_particles[1]->getPosition() - movement * _particles[1]->getInverseMass());
			}
		}
	}
}