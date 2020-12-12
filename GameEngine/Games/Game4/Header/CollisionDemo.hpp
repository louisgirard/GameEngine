#pragma once

#include <Games/Header/GameBase.hpp>
#include <PhysicEngine/Collisions/Header/Octree.hpp>

namespace Games::Game4 {
	class CollisionDemo : public GameBase
	{
	private:

		/* Initializes the game */
		virtual void initGame();

		/* Handles user inputs
		* @param p_dt the time ellapsed since the last update*/
		virtual void handleInput(double p_dt);

		/*
		Updates the positions of the particles
		@param p_dt the time ellapsed since the last update
		*/
		virtual void updatePhysic(double p_dt);

		/*
		Updates the visual representations of the particles
		*/
		virtual void updateFrame();

		/* Holds all the collisions data that need to passed to the collision resolver*/
		std::vector<PhysicEngine::Collisions::CollisionData> _collisionsData;

		/*
		* Detect the real collision among the possible ones, and resolve them
		* @param p_possibleCollisions the possible collisions detected by the broad phase
		*/
		void narrowPhaseCollisions(std::vector<std::vector<PhysicEngine::Collisions::Collider*>>& p_possibleCollisions);

	public:
		/* Default constructor */
		CollisionDemo();

		/* Destructor */
		~CollisionDemo();
	};
}



