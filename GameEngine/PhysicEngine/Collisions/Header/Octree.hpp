#pragma once

#include <PhysicEngine/Header/MathEnabler.hpp>

namespace PhysicEngine::Collisions {

	class Octree
	{
	protected:
		class Node {
		protected:
			Vector3 _center;
			Vector3 _dimension;
			Node* child;


		public:
			Node(Vector3 p_center, Vector3 p_dimension) {

			}

		};
	public:

	};
}

