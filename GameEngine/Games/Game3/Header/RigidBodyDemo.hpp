#pragma once

#include <Games/Header/GameBase.hpp>
#include <PhysicEngine/Forces/Header/BodyForceRegistry.hpp>
#include <PhysicEngine/Header/ARigidBody.hpp>
#include <SceneGraph/Header/CIrregularCube.hpp>
#include <PhysicEngine/Forces/Header/BodyGravity.hpp>
namespace Games::Game3 {
	class RigidBodyDemo : public GameBase
	{
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

		void cameraFollowMaster();

		/* Holds all the forces and the Rigidbody they're associated with */
		Forces::BodyForceRegistry _registry;

		/*Gravity acceleration*/
		float _gravityAcceleration;

		/* The force generator for gravity in the game */
		Forces::BodyGravity _gravity;

		std::shared_ptr<SceneGraph::CIrregularCube> _cube;

		bool _launch;
		float _saveTime;
		float _savePhysicTime;

		/* Holds the ground plane */
		std::shared_ptr<HorizontalPlane> _ground;

	public:
		/* Default constructor */
		RigidBodyDemo();

		~RigidBodyDemo();

	};
}


