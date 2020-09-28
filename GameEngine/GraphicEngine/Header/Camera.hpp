#ifndef _GraphicEngine_Camera_H
#define _GraphicEngine_Camera_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
namespace GraphicEngine {
	class Camera
	{
	protected:
		/// \brief	The camera orientation matrix.
		glm::mat4x4 _orientation;
		/// \brief	The camera position.
		glm::vec3 _position;

	public :
	public:

		Camera();
			
		void setPosition(glm::vec3 const& p_position);

		const glm::vec3& getPosition() const;

		void translateLocal(glm::vec3 const& p_translation);

		void translateFront(float p_value);

		void translateUp(float p_value);

		void translateRight(float p_value);

		void rotateLocal(const glm::vec3& p_axis, float p_angle);

		glm::vec3 lookingAt();

		glm::vec3 up();

		glm::mat4x4 getTransform() const;

		glm::mat4x4 getInverseTransform() const;

	};
}

#endif // !_GraphicEngine_Camera_H



