#include <GraphicEngine/SceneBase/Header/Camera.hpp>

namespace GraphicEngine::SceneBase {
		Camera::Camera() : _orientation(glm::mat4x4(1.0)), _position(0.0f, 0.0f, 0.0f) {}

#pragma region GETTERS
		const glm::vec3& Camera::getPosition() const
		{
			return _position;
		}

		glm::mat4x4 Camera::getTransform() const
		{
			return glm::translate(_position) * _orientation;
		}

		glm::mat4x4 Camera::getInverseTransform() const
		{
			return glm::inverse(getTransform()); // .inverse();
		}
#pragma endregion

#pragma region SETTERS
		void Camera::setPosition(glm::vec3 const& p_position)
		{
			_position = p_position;
		}
#pragma endregion

#pragma region TRANSLATION
		void Camera::translateLocal(glm::vec3 const& p_translation)
		{
			_position += glm::vec3(_orientation * glm::vec4(p_translation, 1.0));
		}

		void Camera::translateFront(float p_value)
		{
			translateLocal(glm::vec3(0.0f, 0.0f, -p_value));
		}

		void Camera::translateUp(float p_value)
		{
			translateLocal(glm::vec3(0.0f, p_value, 0.0f));
		}

		void Camera::translateRight(float p_value)
		{
			translateLocal(glm::vec3(p_value, 0.0f, 0.0f));
		}
#pragma endregion

#pragma region ROTATION
		void Camera::rotateLocal(const glm::vec3& p_axis, float p_angle)
		{
			_orientation = _orientation * glm::rotate(p_angle, p_axis);
		}

		glm::vec3 Camera::lookingAt() {
			return glm::normalize(_orientation * glm::vec4(0, 0, -1, 1));
		}

		glm::vec3 Camera::up() {
			return glm::normalize(_orientation * glm::vec4(0, 1, 0, 1));
		}
#pragma endregion
}

