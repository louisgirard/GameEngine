#pragma once
#include <PhysicEngine/Header/CHorizontalPlane.hpp>
#include <PhysicEngine/Collisions/Header/ParticleContactGenerator.hpp>
#include <vector>
namespace PhysicEngine {
	namespace Collisions {
		class PlaneContactGenerator:ParticleContactGenerator
		{
		private:
			//The plane with which the particles are colliding
			std::shared_ptr<PhysicEngine::CHorizontalPlane> _plane;
			//The particles colliding with the plane
			std::vector<std::shared_ptr<PhysicEngine::CParticle>> _particles;

		public:
			PlaneContactGenerator(PhysicEngine::CHorizontalPlane* p_plane, PhysicEngine::CParticle* p_particles, unsigned arraySize);

			/*Adds a new particle to collide with the plane
			* @param p_particle the new colliding particle
			*/
			void addParticle(CParticle* p_particle);

			/*
			* Removes a particle from those colliding with the plane
			* @param p_particle the particle that does not collide with the plane anymore
			*/
			void removeParticle(CParticle* p_particle);

			/*Generate the contact, if necesssary*/
			virtual unsigned AddContact(ParticleContact* p_contact, unsigned p_limit) override;
		};
	}
}
