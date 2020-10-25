#ifndef _GRAPHIC_ENGINE_BOUNDING_BOX_HPP_
#define _GRAPHIC_ENGINE_BOUNDING_BOX_HPP_

#include <limits>
#include <vector>
#include <iterator>

#include <glm/vec3.hpp>
#include <glm/common.hpp>

namespace GraphicEngine::SceneBase {
		class BoundingBox
		{
		protected:

			/* Min and max bounds */
			glm::vec3 _bounds[2];

		public:

#pragma region Constructor
			/*
			* Default constructor, initializes an empty box
			*/
			BoundingBox();

			/*
			* Constructor
			* Initializes box with provided bounds
			* 
			* @param p_initBound : The initialization bounds (index 0, the minimum values, index 1, the maximum values)
			*/
			BoundingBox(const glm::vec3 p_initBound[2]);

			/*
			* Consructor
			* Initializes a box with the provided bounds
			*	
			* @param p_min : Minimum bound
			* @param p_max : Maximum bound
			*/
			BoundingBox(const glm::vec3& min, const glm::vec3& max);

			/*
			* Constructor 
			* Creates a bounding box containing all vecotrs contained int he provided data structure
			* 
			* @param p_dataStructure : An iterable data structure
			*/
			template <typename iterable>
			BoundingBox(const iterable& dataStructure) : BoundingBox()
			{
				update(dataStructure);
			}

			/*
			* Constructor
			* Creates a bounding box containing all vector in the range [begin;end[
			*
			* @param p_begin : Range's start
			* @param p_end : Range's end
			*/
			template <typename iterator>
			BoundingBox(const iterator& begin, const iterator& end)
			{
				update(begin, end);
			}
#pragma endregion

#pragma region UPDATE
			/*
			* Updates the box such as it contains provided vector
			* @param p_vector : Vector to add to the box
			*/
			void update(const glm::vec3& p_vector);

			/*
			* Updates the bounding box such as it contains all vectors in the range [begin;end[.
			* 
			* @param p_begin : Range's start
			* @param p_end : Range's end
			*/
			template <typename iterator>
			void update(const iterator& p_begin, const iterator& p_end)
			{
				for (auto it = p_begin; it != p_end; ++it)
				{
					update(*it);
				}
			}

			/*
			* Updates the box such as it contains all vectors of the provided data structure
			* @param p_dataStructure : An iterable data structure
			*/
			template <typename iterable>
			void update(const iterable& p_dataStructure)
			{
				update(p_dataStructure.begin(), p_dataStructure.end());
			}
#pragma endregion

#pragma region GETTERS
			/*
			* Determines whether this bounding box is empty
			* @return true if the box is empty, else false
			*/
			bool isEmpty() const;

			/*
			* Gets the minimum vertex 
			* @return minimum vertex
			*/
			const glm::vec3& min() const;

			/*
			* Gets the maximum vertex
			* @return maximum vertex
			*/
			const glm::vec3& max() const;

			/*
			* Gets bounding box's center
			* @return the center of the bounding box
			*/
			glm::vec3 center() const;

			/*
			* Gets the extent of the bounding box
			* @return bounding box's extent
			*/
			glm::vec3 extent() const;

			/*
			* Gets the vertices of the bounding box
			* @param p_writeIt (out) : The iterator to write vertices into
			*/
			template <class iterator>
			void getVertices(iterator p_writeIt) const
			{
				// Gets every corner of the box
				for (int x = 0; x <= 1; x++)
				{
					for (int y = 0; y <= 1; y++)
					{
						for (int z = 0; z <= 1; z++)
						{
							glm::vec3 maskMin(x, y, z);
							glm::vec3 maskMax = glm::vec3(1, 1, 1) - maskMin;
							(*p_writeIt) = maskMin * _bounds[0] + maskMax * _bounds[1];
							++p_writeIt;
						}
					}
				}
			}

			/*
			* Gets the vertices of the bounding box
			* @return A vector of the box's corner
			*/
			std::vector<glm::vec3> getVertices() const;
#pragma endregion

#pragma region OPERATORS
			/*
			* Computes the union of two bounding boxes
			* @param p_other : The other bounding box
			*/
			BoundingBox operator+ (const BoundingBox& p_other) const;

			/*
			* Computes the intersection of two bounding boxes
			* @param p_other : The other bounding box
			*/
			BoundingBox operator* (const BoundingBox& p_other) const;
#pragma endregion
		};
}

#endif // !_GRAPHIC_ENGINE_BOUNDING_BOX_HPP_



