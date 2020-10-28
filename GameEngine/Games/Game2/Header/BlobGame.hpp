#ifndef _GAME2_BLOB_HPP_
#define _GAME2_BLOB_HPP_

#include <Games/Header/GameBase.hpp>
#include <PhysicEngine/Header/CParticle.hpp>

#include <glm/matrix.hpp>

#include <PhysicEngine/Forces/Header/ParticleForceRegistry.hpp>
#include <PhysicEngine/Forces/Header/ParticleGravity.hpp>
#include <PhysicEngine/SpringForces/Header/ParticleSpring.hpp>
#include <PhysicEngine/SpringForces/Header/ParticleBuoyancy.hpp>

#include <PhysicEngine/Collisions/Header/ParticleContactResolver.hpp>

#include <PhysicEngine/Collisions/Header/PlaneContactGenerator.hpp>
#include <PhysicEngine/Collisions/Header/ParticleCable.hpp>

#define NUM_PARTICLES 10
using namespace PhysicEngine;

namespace Games {
	namespace Game2 {
		class Blob : public GameBase
		{
		private:
			// Shaders
			static const std::string WATER;

			/* Holds all the particles in the scene */
			std::shared_ptr<CParticle> _particles[NUM_PARTICLES];

			/* Holds all the springs in the scene */
			std::vector<std::shared_ptr<SpringForces::ParticleSpring>> _springs;

			/* Holds all the cables in the scene */
			std::vector<std::shared_ptr<Collisions::ParticleCable>> _cables;

			/* Holds the contact resolver to resolve contacts between particles */
			Collisions::ParticleContactResolver _contactResolver;

			/* Holds the ground plane */
			std::shared_ptr<HorizontalPlane> _ground;

			/* Holds the water plane */
			std::shared_ptr<HorizontalPlane> _water;

			/* Holds all the forces and the particle they're associated with */
			Forces::ParticleForceRegistry _registry;

			/*Gravity acceleration*/
			float _gravityAcceleration;

			/* The force generator for gravity in the game */
			Forces::ParticleGravity _gravity;

			/* Check if blob is broken or not */
			bool _isBroken = false;

			/* Initializes the game */
			virtual void initGame();

			/* Handles user inputs 
			@param p_dt the time ellapsed since the last update*/
			virtual void handleInput(double p_dt);

			/**
			* Function called when the user reshapes the game window
			* @param p_width : new window's width
			* @param p_height : new window's height
			**/
			virtual void reshape(GLint p_width, GLint p_height);

			/*
			Updates the positions of the particles
			@param p_dt the time ellapsed since the last update
			*/
			virtual void updatePhysic(double p_dt);

			/*Updates the visual representations of the particles*/
			virtual void updateFrame();

			/* Update the position of the camera to follow master particle */
			void cameraFollowMaster();

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

			/*
			Check if there are interactions between particles and the water
			@param p_dt the time ellapsed since the last update
			*/
			void checkWaterInteraction(float p_dt);

			/* Generates particle and its force associated */
			void generateParticles(float p_zAxis);
		public:
			/* Default constructor */
			Blob();
		
			~Blob();
		};
	}
}



#endif // !_GAME2_BLOB_HPP_


