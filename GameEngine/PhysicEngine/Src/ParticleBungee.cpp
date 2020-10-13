#include <PhysicEngine/Header/ParticleBungee.hpp>

namespace PhysicEngine {

	ParticleBungee::ParticleBungee(CParticle* p_particle, float p_k, float p_l)
	{
		this->_opposite_particle = p_particle;
		this->_k = p_k;
		this->_l0 = p_l;
	}

	void ParticleBungee::updateForce(CParticle* p_particle, double p_dt)
	{
		//Calculate the vector d
		Vector3 d;
		Vector3 x_a = p_patircle.getPosition();
		Vector3 x_b = this->_opposite_particle.getPosition();
		d = x_a - x_b;

		//Get magnitude and normalize d
		float d_magnitude = d.magnitude();
		if (d_magnitude <= this->_l0)
		{
			return;
		}
		Vector3 d_normalized = d.normalize();

		// Calculate force
		Vector3 force = -(this->_k) * (d_magnitude - this->_l0) * d_normalized;

		p_particle->addForce(force);
	}



}