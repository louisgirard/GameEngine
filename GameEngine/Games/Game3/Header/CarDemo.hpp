#pragma once

#include <Games/Header/GameBase.hpp>
#include <SceneGraph/Header/CCar.hpp>
#include <PhysicEngine/Forces/Header/BodyGravity.hpp>
#include <PhysicEngine/Forces/Header/BodyForceRegistry.hpp>

namespace Games::Game3 {
	class CarDemo : public GameBase
	{
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

		/*Gravity acceleration*/
		float _gravityAcceleration;

		/* The force generator for gravity in the game */
		Forces::BodyGravity _gravity;

		/* Holds all the forces and the Rigidbody they're associated with */
		Forces::BodyForceRegistry _registry;

		std::shared_ptr<SceneGraph::CCar> _car1;
		std::shared_ptr<SceneGraph::CCar> _car2;
		/* Holds the ground plane */
		std::shared_ptr<HorizontalPlane> _ground;

		Vector3 _contactPoint;

	public:
		/* Default constructor */
		CarDemo();

		~CarDemo();
	};
}


