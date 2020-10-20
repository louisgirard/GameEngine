#pragma once

#include <vector>
#include <iostream>

#include <PhysicEngine/Header/CParticle.hpp>
#include <PhysicEngine/Forces/Header/ParticleForceGenerator.hpp>


namespace PhysicEngine {
	namespace Forces {
		class ParticleForceRegistry
		{
		protected:

			/*
			* Stores a force generator and a particle it is applied to
			*/
			struct ParticleForceRegistration {
				CParticle* _particle;
				ParticleForceGenerator* _forceGenerator;
			};

			typedef std::vector<ParticleForceRegistration> Registry;
			/*
			* Holds the list of registrations
			*/
			Registry _registrations;

		public:

			/*Adds a force to apply to a particle
			* @param p_particle the particle to apply the force on
			* @param p_forceGenerator the force to apply
			*/
			void add(CParticle* p_particle, ParticleForceGenerator* p_forceGenerator);

			/*Remove a pair particle-force from the registry. No effect if the pair isn't registered
			* @param p_particle the particle to remove
			* @param p_forceGenerator the force to remove
			*/
			void remove(CParticle* p_particle, ParticleForceGenerator* p_forceGenerator);

			/*Remove all pairs particle-force from the registry (without deleting the forces nor the particles*/
			void clear();

			/*Call the force generators to update the forces of their particles
			* @param p_dt the elapsed time since the last update
			*/
			void updatePhysic(double p_dt);
		};

	}
}

