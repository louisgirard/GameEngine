#pragma once
#include <PhysicEngine/Collisions/Header/ParticleContact.hpp>
#include <vector>

namespace PhysicEngine {
	namespace Collisions {
		class ParticleContactResolver
		{
		protected:
			/*Number of iterations*/
			int _iterations;

		public:
			//Constructor
			ParticleContactResolver(int p_iterations);

			/*** Sets the number of iterations that can be used.
			* @param p_iterations the new number of iterations
			*/
			void setIterations(unsigned p_iterations);

			/*
			* Resolves contacts for both velocity and interpenetration
			* @param p_contactArray array of the contacts to be resolved
			* @param p_dt ellapsed time since the last contact resolution
			*/
			void resolveContacts(std::vector<ParticleContact*> p_contactArray, double p_dt);
		};
	}
}

