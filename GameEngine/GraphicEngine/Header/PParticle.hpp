#pragma once
#include <PhysicEngine/Header/Vector3.hpp>

namespace PhysicEngine {
	class PParticle
	{
	private:
		Vector3 _color;
		float _size;
	public:
		/*Constructor
		@param p_color the color of the particle
		@param p_size the size of the particle
		*/
		PParticle(Vector3 p_color, float p_size);

		/*Sets the color of the particle
		* @param p_color the new color of the particle (RGB between 0 and 1)
		*/
		void setColor(const Vector3& p_color);

		/*@returns the size of the particle*/
		float getSize() const;

		/*Sets the size of the particle
		* @param p_size the new size of the particle
		*/
		void setSize(float p_size);

		/*
		* Sets the position of the particle
		* @param p_position the new position of the particle
		*/
		void draw(Vector3 p_position);
	};
}

