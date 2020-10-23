#pragma once
#include <PhysicEngine/Header/AHorizontalPlane.hpp>
namespace PhysicEngine {
	class CHorizontalPlane
	{
	private:
		std::shared_ptr<AHorizontalPlane> _abstraction;
	public:
		CHorizontalPlane(Vector3 p_bottomLeftCorner, float p_length, float p_width);

		//returns the height of the plane
		float getHeight();

		/*Returns true if the position is vertically above or under the plane
		* @param p_position the position to check
		*/
		bool isAboveOrUnder(Vector3 p_position);
	};
}
