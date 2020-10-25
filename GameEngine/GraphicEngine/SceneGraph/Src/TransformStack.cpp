#include <GraphicEngine/SceneGraph/Header/TransformStack.hpp>

namespace GraphicEngine::PSceneGraph {

		TransformStack::TransformStack()
		{
			_stack.push(glm::mat4x4(1.0));
		}

#pragma region GETTERS
		glm::mat4x4& TransformStack::current() {
			return _stack.top();
		}

		const glm::mat4x4& TransformStack::current() const {
			return _stack.top();
		}
#pragma endregion

#pragma region STACK_OPERATION
		void TransformStack::push() {
			_stack.push(_stack.top());
		}

		void TransformStack::pop() {
			assert(!_stack.empty());
			_stack.pop();
		}
#pragma endregion

#pragma region SETTERS
		void TransformStack::set(const glm::mat4x4& p_matrix) {
			current() = p_matrix;
		}
#pragma endregion

#pragma region TRANSFORM_OPERATION
		void TransformStack::translate(const glm::vec3& p_translation) {
			current() *= glm::translate(p_translation);
		}

		void TransformStack::rotate(float p_angle, const glm::vec3& p_axis) {
			current() *= glm::rotate(glm::degrees(p_angle), p_axis);
		}

		void TransformStack::scale(const glm::vec3& p_factors) {
			current() *= glm::scale(p_factors);
		}

		void TransformStack::multiply(const glm::mat4x4& p_matrix) {
			current() *= p_matrix;
		}
#pragma endregion
}