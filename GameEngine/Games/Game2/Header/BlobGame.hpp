#ifndef _GAME2_BLOB_HPP_
#define _GAME2_BLOB_HPP_

#include <Games/Header/GameBase.hpp>
#include <PhysicEngine/Header/CParticle.hpp>
#include <PhysicEngine/Collisions/Header/ParticleContactResolver.hpp>

#define NUM_PARTICLES 4
using namespace PhysicEngine;

namespace Games {
	namespace Game2 {
		class Blob : public GameBase
		{
		private:
			/* Holds all the particles in the scene */
			std::shared_ptr<CParticle> _particles[NUM_PARTICLES];

			/* Holds the contact resolver to resolve contacts between particles */
			Collisions::ParticleContactResolver _contactResolver;
			
			/*
			Updates the positions of the particles
			@param p_dt the time ellapsed since the last update
			*/
			virtual void updatePhysic(double p_dt);

			/*
			Check if there are collisions and add them to the contact resolver
			@param p_dt the time ellapsed since the last update
			*/
			void checkCollisions(float p_dt);
		public:
			/* Default constructor */
			Blob();
		
		};
	}
}



#endif // !_GAME2_BLOB_HPP_


