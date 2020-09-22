#pragma once
#include <PhysicEngine\Header\Vector3.h>
#include <PhysicEngine\Header\AParticle.h>
#include <GraphicEngine\Header\PParticle.h>
#include <memory>

namespace PhysicEngine {
	class CParticle
	{
	private:
		std::shared_ptr<AParticle> _abstraction;
		std::shared_ptr<PParticle> _presentation;

	public:
		/* Different types of projectile */
		enum class Types { Bullet, Canonball, Laser, Fireball };

		CParticle(float p_mass, Vector3 p_position, Vector3 p_velocity, Vector3 p_acceleration, float p_damping, Vector3 p_color, float size);
		CParticle(Types p_type);

		/* Returns the position of the particle */
		Vector3 getPosition() const;

		/* Sets the position of the particle */
		void setPosition(const Vector3& p_position);
		void setPosition(const float p_x, const float p_y, const float p_z);

		/* Returns the velocity of the particle */
		Vector3 getVelocity() const;

		/* Sets the velocity of the particle */
		void setVelocity(const Vector3& p_velocity);
		void setVelocity(const float p_x, const float p_y, const float p_z);

		/* Returns the acceleration of the particle */
		Vector3 getAcceleration() const;

		/* Sets the acceleration of the particle */
		void setAcceleration(const Vector3& p_acceleration);
		void setAcceleration(const float p_x, const float p_y, const float p_z);

		/* Returns the damping */
		float getDamping() const;

		/* Sets the damping */
		void setDamping(const float p_damping);

		/* Returns the inverse of the mass of the particle */
		float getInverseMass() const;

		/* Sets the inverse of the mass of the particle */
		void setInverseMass(const float p_inverseMass);

		/* Returns the mass of the particle */
		float getMass() const;

		/* Sets the mass of the particle */
		void setMass(const float p_mass);

		/* Integrate the particle */
		void integrate(float p_time);

		/*Draw the particle*/
		void draw();

		/*Update the position of the particle both in the abstraction and the presentation*/
		void update(double p_dt);
	};
}
