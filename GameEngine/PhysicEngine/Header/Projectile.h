#pragma once

#include <PhysicEngine/Header/Particle.h>
#include <iostream>

namespace PhysicEngine {
	class Projectile
	{
	public:
		/* Different types of projectile */
		enum class Types { Bullet, Canonball, Laser, Fireball };

		/* Constructor */
		Projectile();

		/* Returns the position of the projectile */
		Vector3 getPosition();

		/* Change type of projectile */
		void changeType(Types p_type);

		/* Launch projectile */
		void launch();

		/* Move the projectile */
		void move(float p_dt);

		/* Draw the projectile */
		void draw();
	private:
		/* Holds the particle */
		Particle _particle;

		/* Holds the type of projectile */
		Types _type;

		/* Holds the size of the projectile */
		float _size;

		/* Keeps track if the projectile is launched */
		bool _launched;

		/* Sets the particle parameters according to the type of projectile */
		void setParticle();
	};
}
