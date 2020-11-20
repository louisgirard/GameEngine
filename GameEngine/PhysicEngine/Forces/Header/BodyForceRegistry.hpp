#pragma once

#include <vector>
#include <iostream>

#include <PhysicEngine/Header/ARigidBody.hpp>
#include <PhysicEngine/Forces/Header/BodyForceGenerator.hpp>


namespace PhysicEngine {
	namespace Forces {
		class BodyForceRegistry
		{
		protected:

			/*
			* Stores a force generator and a particle it is applied to
			*/
			struct ParticleForceRegistration {
				ARigidBody* _body;
				BodyForceGenerator* _forceGenerator;
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
			void add(ARigidBody* p_body, BodyForceGenerator* p_forceGenerator);

			/*Remove a pair particle-force from the registry. No effect if the pair isn't registered
			* @param p_particle the particle to remove
			* @param p_forceGenerator the force to remove
			*/
			void remove(ARigidBody* p_body, BodyForceGenerator* p_forceGenerator);

			/*Remove all pairs particle-force from the registry (without deleting the forces nor the particles*/
			void clear();

			/*Call the force generators to update the forces of their particles
			* @param p_dt the elapsed time since the last update
			*/
			void updatePhysic(double p_dt);
		};

	}
}

