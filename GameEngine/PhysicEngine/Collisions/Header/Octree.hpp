#pragma once

#include <vector>
#include <PhysicEngine/Header/MathEnabler.hpp>
#include <SceneGraph/Header/CMeshObject.hpp>

namespace PhysicEngine::Collisions {

	class Octree
	{
	protected:
		class Node {
		protected:
			GraphicEngine::SceneBase::BoundingBox _region;
			std::vector<Collider*> _primitives;
			std::vector<Node*> _childs;
			int _depth;
			int _maxDepth;
			int _maxPrimitive;

			bool isLeaf();

			void subdivise();

		public:
			Node(int p_depth, int p_maxDepth, int p_maxPrimitive, GraphicEngine::SceneBase::BoundingBox p_region);

			void browse(std::vector<std::vector<Collider*>>& const p_possibleCollisions);

			void tryAddingPrimitive(std::vector<Collider*> p_primitives);

			~Node();
		};

		Node* _root;
		int _maxDepth;
		int _maxPrimitive;
		std::vector<Collider*> _primitiveMarked;
	public:
		 
		Octree(int p_maxDepth, int p_maxPrimitives, std::vector<Collider*> p_primitive);

		void build(GraphicEngine::SceneBase::BoundingBox p_baseRegion);

		std::vector<std::vector<Collider*>> getPossibleCollison();

		void clear();

		~Octree();
	};
}
