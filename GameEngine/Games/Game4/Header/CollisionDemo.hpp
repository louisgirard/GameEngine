#pragma once

#include <Games/Header/GameBase.hpp>
#include <PhysicEngine/Collisions/Header/Octree.hpp>
#include <SceneGraph/Header/CCube.hpp>
#include <SceneGraph/Header/CWall.hpp>
#include <PhysicEngine/Forces/Header/BodyForceRegistry.hpp>
#include <PhysicEngine/Forces/Header/BodyGravity.hpp>

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

		std::vector<SceneGraph::CWall> _tabWall;

		std::shared_ptr<SceneGraph::CCube> _cube;

		std::shared_ptr<PhysicEngine::Collisions::Octree> _octree;

		/* Holds all the forces and the Rigidbody they're associated with */
		Forces::BodyForceRegistry _registry;

		/*Gravity acceleration*/
		float _gravityAcceleration;

		/* The force generator for gravity in the game */
		Forces::BodyGravity _gravity;

	public:
		/* Default constructor */
		CollisionDemo();

		/* Destructor */
		~CollisionDemo();
	};
}



