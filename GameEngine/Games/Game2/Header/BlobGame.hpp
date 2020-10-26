#ifndef _GAME2_BLOB_HPP_
#define _GAME2_BLOB_HPP_

#include <Games/Header/GameBase.hpp>
#include <PhysicEngine/Header/CParticle.hpp>
#include <PhysicEngine/Header/CHorizontalPlane.hpp>

#include <PhysicEngine/Forces/Header/ParticleForceRegistry.hpp>
#include <PhysicEngine/Forces/Header/ParticleGravity.hpp>
#include <PhysicEngine/SpringForces/Header/ParticleSpring.hpp>

#include <PhysicEngine/Collisions/Header/ParticleContactResolver.hpp>

#define NUM_PARTICLES 3
using namespace PhysicEngine;

namespace Games {
	namespace Game2 {
		class Blob : public GameBase
		{
		private:
			/* Holds all the particles in the scene */
			std::shared_ptr<CParticle> _particles[NUM_PARTICLES];

			/* Holds all the springs in the scene */
			std::vector<std::shared_ptr<SpringForces::ParticleSpring>> _springs;

			/* Holds the contact resolver to resolve contacts between particles */
			Collisions::ParticleContactResolver _contactResolver;

			/* Holds the ground plane */
			std::shared_ptr<CHorizontalPlane> _ground;

			/* Holds all the forces and the particle they're associated with */
			Forces::ParticleForceRegistry _registry;

			/* The force generator for gravity in the game */
			Forces::ParticleGravity _gravity;

			/* Check if blob is broken or not */
			bool isBroken = false;

			/* Initializes the game */
			virtual void initGame();

			/* Handles user inputs 
			@param p_dt the time ellapsed since the last update*/
			virtual void handleInput(double p_dt);

			/*
			Updates the positions of the particles
			@param p_dt the time ellapsed since the last update
			*/
			virtual void updatePhysic(double p_dt);

			/*Updates the visual representations of the particles*/
			virtual void updateFrame();

			/*
			Check if there are collisions between particles and add them to the contact resolver
			@param p_dt the time ellapsed since the last update
			*/
			void checkParticleCollisions(float p_dt);

			/*
			Check if there are collisions between particles and the ground
			@param p_dt the time ellapsed since the last update
			*/
			void checkGroundCollisions(float p_dt);
		public:
			/* Default constructor */
			Blob();
		
		};
	}
}



#endif // !_GAME2_BLOB_HPP_


