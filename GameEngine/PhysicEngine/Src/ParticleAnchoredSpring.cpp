#include <PhysicEngine/Header/ParticleAnchoredSpring.hpp>

namespace PhysicEngine {

	ParticleAnchoredSpring::ParticleAnchoredSpring(Vector3 p_anchor, float p_k, float p_l)
	{
		this->_anchor = p_anchor;
		this->_k = p_k;
		this->_l0 = p_l;
	}

	void ParticleAnchoredSpring::updateForce(CParticle* p_particle, double p_dt)
	{
		//Calculate the vector d
		Vector3 d;
		Vector3 x_a = p_patircle.getPosition();
		Vector3 x_b = this->_anchor;
		d = x_a - x_b;

		//Get magnitude and normalize d
		float d_magnitude = d.magnitude();
		Vector3 d_normalized = d.normalize();

		// Calculate force
		Vector3 force = -(this->_k) * (d_magnitude - this->_l0) * d_normalized;

		p_particle->addForce(force);
	}

}