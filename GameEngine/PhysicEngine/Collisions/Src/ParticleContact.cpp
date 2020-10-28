#include <PhysicEngine/Collisions/Header/ParticleContact.hpp>

namespace PhysicEngine
{
	namespace Collisions {
		ParticleContact::ParticleContact()
		{
		}
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
			resolveInterpenetration(p_dt);
		}

		float ParticleContact::getPenetration()
		{
			return _penetration;
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
			// Computation of separating velocities
			float separatingVelocity = calculateSeparatingVelocity();
			//if the separating velocity is positive, there's no need for an impulsion
			if (separatingVelocity > 0) return;

			// Apply restitution coefficient
			float newSeparatingVelocity = -separatingVelocity * _restitutionCoef;

			// Check the velocity build-up due to acceleration only
			Vector3 accCausedVelocity = _particles[0]->getAcceleration();
			if (_particles[1] != nullptr) accCausedVelocity -= _particles[1]->getAcceleration();
			float accCausedSeparatingVelocity = accCausedVelocity.scalarProduct(_contactNormal) * p_dt;

			//Check if the objects are getting closer due to acceleration build up
			//If so, remove the closing velocity
			if (accCausedSeparatingVelocity < 0)
			{
				newSeparatingVelocity += _restitutionCoef * accCausedSeparatingVelocity;

				//check that we do not remove more than there is
				if (newSeparatingVelocity < 0) newSeparatingVelocity = 0;
			}

			// separating velocity delta between before and after the contact
			float deltaVelocity = newSeparatingVelocity - separatingVelocity;

			// Computation of the sum of inverse masses
			float totalInverseMass = _particles[0]->getInverseMass();
			if (_particles[1] != nullptr) totalInverseMass += _particles[1]->getInverseMass();

			//both masses are infinite, no need for resolution
			if (totalInverseMass <= 0) return;

			//the total impulse is dV*(mA*mB/(mA+mB))
			Vector3 totalImpulse = _contactNormal * (deltaVelocity / totalInverseMass);

			// Apply impulse proportionnaly to the inverse mass of the particle
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

			//both masses are infinite, no need for resolution
			if (totalInverseMass <= 0) return;

			// Movement = n*d*mA*mB / (mA + mB)
			Vector3 movement = _contactNormal * (_penetration / totalInverseMass);

			// the movement is distributed between the two particles proportionnaly to their inverse masses
			_particles[0]->setPosition(_particles[0]->getPosition() + movement * _particles[0]->getInverseMass());
			if (_particles[1] != nullptr)
			{
				_particles[1]->setPosition(_particles[1]->getPosition() - movement * _particles[1]->getInverseMass());
			}
			
		}
	}
}