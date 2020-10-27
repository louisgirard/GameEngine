#pragma once
#include <PhysicEngine/Header/CParticle.hpp>

namespace PhysicEngine
{
	namespace Collisions {
		/*
		Class used to detect contacts between a plane and one or multiple particles
		*/
		class ParticleContact
		{
		private:
			/* Holds the two particles involved in the contact (second particle can be NULL)*/
			CParticle* _particles[2];

			/* Holds the restitution coefficient */
			float _restitutionCoef;

			/* Holds the contact normal */
			Vector3 _contactNormal;

			/* Holds the depth of penetration */
			float _penetration;			

		public:
			ParticleContact();
			ParticleContact(CParticle* p_particle1, CParticle* p_particle2, float p_restitutionCoef, Vector3 p_contactNormal, float p_penetration);

			/*Get the contact penetration
			*/
			float getPenetration();

			/* Calculate the separating velocity */
			float calculateSeparatingVelocity() const;

			/*Apply impulsions
			* @param p_dt the elapsed time since the last update
			*/
			void resolveVelocity(float p_dt);

			/*Handles interpenetration
			* @param p_dt the elapsed time since the last update
			*/
			void resolveInterpenetration(float p_dt);

			/*Resolves the contact for velocity and interpenetration
			* @param p_dt the elapsed time since the last update
			*/
			void resolve(float p_dt);
		};
	}
}
