#pragma once
#include <PhysicEngine/Header/Vector3.hpp>
#include <PhysicEngine/Header/AParticle.hpp>
#include <GraphicEngine/Header/PParticle.hpp>
#include <memory>

namespace PhysicEngine {

	/*
	Controller class for particles.
	Used for the interactions between the abstraction and the presentation
	and to interact with other classes.
	*/
	class CParticle
	{
	private:
		std::shared_ptr<AParticle> _abstraction;
		std::shared_ptr<GraphicEngine::PParticle> _presentation;

	public:
		/* Different types of projectile */
		enum class Types { Bullet, Canonball, Laser, Fireball };

		/*Construction by giving the explicit properties of the particle
		@param p_mass the mass
		@param p_position the position
		@param p_velocity the velocity
		@param p_acceleration the acceleration
		@param p_damping the damping
		@param p_color the color of the visual representation
		@param p_size the size of the visual representation
		*/
		CParticle(float p_mass, Vector3 p_position, Vector3 p_velocity, Vector3 p_acceleration, 
			float p_damping, Vector3 p_color, float p_size);

		/*Construction by giving a predetermined type of particle
		@param p_type the type of particle to be created
		*/
		CParticle(Types p_type, Vector3 p_position, Vector3 p_launchDirection);

		/*@returns the size of the particle*/
		float getSize() const;

		/*@return the position of the particle */
		Vector3 getPosition() const;

		/* Sets the position of the particle 
		@param p_position the position to which the particle must be set
		*/
		void setPosition(const Vector3& p_position);

		/* Sets the position of the particle
		@param p_x the new x of the particle
		@param p_y the new y of the particle
		@param p_z the new z of the particle
		*/
		void setPosition(const float p_x, const float p_y, const float p_z);

		/*@return the velocity of the particle */
		Vector3 getVelocity() const;

		/* Sets the velocity of the particle
		@param p_velocity the velocity at which the particle must be set
		*/
		void setVelocity(const Vector3& p_velocity);

		/* Sets the velocity of the particle
		@param p_x the new x of the velocity
		@param p_y the new y of the velocity
		@param p_z the new z of the velocity
		*/
		void setVelocity(const float p_x, const float p_y, const float p_z);

		/*@return the acceleration of the particle */
		Vector3 getAcceleration() const;

		/* Sets the acceleration of the particle
		@param p_acceleration the velocity at which the particle must be set
		*/
		void setAcceleration(const Vector3& p_acceleration);

		/* Sets the acceleration of the particle
		@param p_x the new x of the acceleration
		@param p_y the new y of the acceleration
		@param p_z the new z of the acceleration
		*/
		void setAcceleration(const float p_x, const float p_y, const float p_z);

		/*@return the damping */
		float getDamping() const;

		/* Sets the damping 
		@param p_damping the new damping
		*/
		void setDamping(const float p_damping);

		/*@return the inverse of the mass of the particle */
		float getInverseMass() const;

		/* Sets the inverse of the mass of the particle 
		@param p_inverseMass the new inverse mass of the particle
		*/
		void setInverseMass(const float p_inverseMass);

		/*@return the mass of the particle */
		float getMass() const;

		/* Sets the mass of the particle 
		@param p_mass the new mass of the particle
		*/
		void setMass(const float p_mass);

		/* Computes the new velocity and position of the particle
		@param p_time the ellapsed time since the last update
		*/
		void integrate(double p_time);

		/*Updates the visual representation of the particle*/
		void updateFrame();

		/*Update the position of the particle in the abstraction
		@param p_time the ellapsed time since the last update
		*/
		void updatePhysic(double p_dt);

		/*Adds a force to the particle for the next iteration only*/
		void addForce(const Vector3& p_force);
	};
}
