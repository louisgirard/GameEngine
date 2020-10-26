#include <GraphicEngine/SceneBase/Header/BoundingBox.hpp>

namespace GraphicEngine::SceneBase {
#pragma region Constructor
		BoundingBox::BoundingBox()
		{
			_bounds[0] = glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
			_bounds[1] = glm::vec3(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());
		}

		BoundingBox::BoundingBox(const glm::vec3 p_initBound[2])
		{
			_bounds[0] = p_initBound[0];
			_bounds[1] = p_initBound[1];
		}

		BoundingBox::BoundingBox(const glm::vec3& min, const glm::vec3& max)
		{
			_bounds[0] = min;
			_bounds[1] = max;
		}
#pragma endregion

#pragma region UPDATE
		void BoundingBox::update(const glm::vec3& p_vector)
		{
			_bounds[0] = glm::min(_bounds[0], p_vector);
			_bounds[1] = glm::max(_bounds[1], p_vector);
		}
#pragma endregion

#pragma region GETTERS
		bool BoundingBox::isEmpty() const
		{
			return !glm::all(glm::lessThan(_bounds[0], _bounds[1]));
		}

		const glm::vec3& BoundingBox::min() const { 
			return _bounds[0]; 
		}

		const glm::vec3& BoundingBox::max() const { 
			return _bounds[1]; 
		}

		glm::vec3 BoundingBox::center() const
		{
			assert(!isEmpty() && "Calling BoundingBox::center with an empty bounding box");

			return (_bounds[0] + _bounds[1]) * 0.5f;
		}

		glm::vec3 BoundingBox::extent() const
		{
			assert(!isEmpty() && "Calling BoundingBox::extent with an empty bounding box");

			return _bounds[1] - _bounds[0];
		}

		std::vector<glm::vec3> BoundingBox::getVertices() const
		{
			std::vector<glm::vec3> result;

			// There will be 8 corner
			result.reserve(8);
			// Retrieve corner
			getVertices(std::back_inserter(result));

			return std::move(result);
		}
#pragma endregion

#pragma region OPERATORS
		BoundingBox BoundingBox::operator+ (const BoundingBox& p_other) const
		{
			return BoundingBox(glm::min(_bounds[0], p_other._bounds[0]), glm::max(_bounds[1], p_other._bounds[1]));
		}

		BoundingBox BoundingBox::operator* (const BoundingBox& p_other) const
		{
			return BoundingBox(glm::max(_bounds[0], p_other._bounds[0]), glm::min(_bounds[1], p_other._bounds[1]));
		}
#pragma endregion
}
