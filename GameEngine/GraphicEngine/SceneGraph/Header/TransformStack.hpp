#pragma once

#include <stack>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace GraphicEngine::PSceneGraph {
		class TransformStack
		{
		protected:

			/* Stacks of transform */
			std::stack<glm::mat4x4> _stack;

		public:
			/*
			* Default constructor
			*/
			TransformStack();

#pragma region GETTERS
			/*
			* Consultation and modification of the matrix on top of the stack
			* @return the current transform matrix
			*/
			glm::mat4x4& current();

			/*
			* Consultation and modification of the matrix on top of the stack
			* @return the current transform matrix
			*/
			const glm::mat4x4& current() const;
#pragma endregion

#pragma region STACK_OPERATION
			/*
			* Pushes the matrix on top of the stack
			*/
			void push();

			/*
			* Pops the matrix on top of the stack
			*/
			void pop();
#pragma endregion

#pragma region SETTERS
			/*
			* Sets the matrix on top of the stack
			* @param p_matrix : New matrix
			*/
			void set(const glm::mat4x4& p_matrix);
#pragma endregion


#pragma region TRANSFORM_OPERATION
			/*
			* Multiplies the matrix on top of the stack by translation matrix
			* @param p_translation : The translation vector
			*/
			void translate(const glm::vec3& p_translation);

			/*
			* Multiplies the matrix on top of the stack by a rotation matrix
			* @param p_angle : The angle of rotation
			* @param p_axis : The axis to rotate arround
			*/
			void rotate(float p_angle, const glm::vec3& p_axis);

			/*
			* Multiplies the matrix on top of the stack by a scale matrix
			* @param p_factors : The scale factor
			*/
			void scale(const glm::vec3& p_factors);

			/*
			* Multiplies the matrix on top of the stack by the provided matrix
			* @param p_matrix : The matrix to multiply
			*/
			void multiply(const glm::mat4x4& p_matrix);
#pragma endregion
		};
}



