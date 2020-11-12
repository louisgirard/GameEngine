#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>
#include <PhysicEngine/Collisions/Header/ParticleContact.hpp>

namespace PhysicEngine {
	class AHorizontalPlane
	{
	private:
		//The center of the plane (gives the height of the plane)
		Vector3 _center;
		
		//The length of the plane (along the x axis)
		float _length;

		//The width of the plane (along the z axis)
		float _width;

	public:
		AHorizontalPlane(Vector3 p_center, float p_length, float p_width);

		//Returns the height of the plane
		float getHeight();
		
		/*Returns true if the position is vertically above or under the plane
		* @param p_position the position to check
		*/
		bool isAboveOrUnder(Vector3 p_position);
	};
}
