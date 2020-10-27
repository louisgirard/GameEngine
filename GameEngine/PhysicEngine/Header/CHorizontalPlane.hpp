#pragma once
#include <PhysicEngine/Header/AHorizontalPlane.hpp>
#include <GraphicEngine/Header/PHorizontalPlane.hpp>

namespace PhysicEngine {
	class CHorizontalPlane
	{
	private:
		std::shared_ptr<AHorizontalPlane> _abstraction;
		std::shared_ptr<GraphicEngine::PHorizontalPlane> _presentation;

	public:
		CHorizontalPlane(Vector3 p_center, float p_length, float p_width, Vector3 p_color);

		//returns the height of the plane
		float getHeight();

		/*Returns true if the position is vertically above or under the plane
		* @param p_position the position to check
		*/
		bool isAboveOrUnder(Vector3 p_position);

		/*Updates the visual representation of the plane*/
		void updateFrame();
	};
}
