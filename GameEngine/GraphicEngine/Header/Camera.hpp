#ifndef _GraphicEngine_Camera_H
#define _GraphicEngine_Camera_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace GraphicEngine {
	class Camera
	{
	protected:
		/** Camera orientation matrix **/
		glm::mat4x4 _orientation;
		/** Camera position **/
		glm::vec3 _position;

	public:
		/** Default constructor **/
		Camera();
			
#pragma region GETTERS
		/**
		* Get camera position
		* @return camera position
		**/
		const glm::vec3& getPosition() const;

		/**
		* Get camera transformation
		* @return camera transformation
		**/
		glm::mat4x4 getTransform() const;

		/**
		* Get camera inverse transformation
		* @return camera inverse transformation
		**/
		glm::mat4x4 getInverseTransform() const;
#pragma endregion

#pragma region SETTERS
		/**
		* Set camera position
		* @param p_position : camera new position
		**/
		void setPosition(glm::vec3 const& p_position);
#pragma endregion

#pragma region TRANSLATION
		/**
		* Translate camera
		* @param p_translation : the translation vector
		**/
		void translateLocal(glm::vec3 const& p_translation);

		/**
		* Translate camera from scene front vector
		* @param p_value : the value to translate to
		**/
		void translateFront(float p_value);

		/**
		* Translate camera from scene up vector
		* @param p_value : the value to translate to
		**/
		void translateUp(float p_value);

		/**
		* Translate camera from scene right vector
		* @param p_value : the value to translate to
		**/
		void translateRight(float p_value);
#pragma endregion

#pragma region ROTATION
		/**
		* Camera up vector
		* @return camera up vector
		**/
		glm::vec3 up();

		/**
		* Direction the camera is looking at
		* @return direction the camera is looking at
		**/
		glm::vec3 lookingAt();

		/**
		* Rotate the camera arround the axis
		* @param p_axis : axis to rotate arround
		* @param p_angle : angle value for the rotation
		**/
		void rotateLocal(const glm::vec3& p_axis, float p_angle);
#pragma endregion
	};
}

#endif // !_GraphicEngine_Camera_H



