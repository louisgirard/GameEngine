#pragma once

#include <vector>
#include <PhysicEngine/Header/MathEnabler.hpp>
#include <SceneGraph/Header/CMeshObject.hpp>
#include <PhysicEngine/Collisions/Header/Collider.hpp>

namespace PhysicEngine::Collisions {

	class Octree
	{
	protected:
		class Node {
		protected:
			//Region defining this node
			GraphicEngine::SceneBase::BoundingBox _region;
			//Primitive contained in this node
			std::vector<std::shared_ptr<Collider>> _primitives;
			// Node childs
			std::vector<Node*> _childs;
			//Node depth in the tree
			int _depth;
			//Node maximum depth
			int _maxDepth;
			//Node maximum primitives
			int _maxPrimitive;

			/// <summary>
			/// Is the node a leaf ?
			/// </summary>
			/// <returns>true if this node is a leaf, else false</returns>
			bool isLeaf();

			/// <summary>
			/// Subdivise the node in subregions
			/// </summary>
			void subdivise();

		public:
			/// <summary>
			/// Constructor
			/// </summary>
			/// <param name="p_depth">Depth of the node in the tree</param>
			/// <param name="p_maxDepth">Maximum depth of a node</param>
			/// <param name="p_maxPrimitive">Maximum number of primitive a node can contain</param>
			/// <param name="p_region">Region defining this node</param>
			Node(int p_depth, int p_maxDepth, int p_maxPrimitive, GraphicEngine::SceneBase::BoundingBox p_region);

			/// <summary>
			/// Browse the node and its child to find possible collisions
			/// </summary>
			/// <param name="p_possibleCollisions">Possible collisions already discovered</param>
			void browse(std::vector<std::vector<std::shared_ptr<Collider>>>&  p_possibleCollisions);

			/// <summary>
			/// Try adding the primitive in this node, will be added only if they are contained in it 
			/// </summary>
			/// <param name="p_primitives">primitive to add</param>
			void tryAddingPrimitive(std::vector<std::shared_ptr<Collider>> p_primitives);

			// Destructor
			~Node();
		};

		//Tree root
		Node* _root;
		//Node maximum depth
		int _maxDepth;
		//Node maximum primitives
		int _maxPrimitive;
		// Size of the region that should contained every primitives
		float _originalRegionSize;
		// Primitive to add to the tree
		std::vector<std::shared_ptr<Collider>> _primitiveMarked;
	public:
		 
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="p_maxDepth">Maximum depth of a node</param>
		/// <param name="p_maxPrimitives">Maximum number of primitive a node can contain</param>
		/// <param name="p_originalRegionSize">Size of the region that should contained every primitives</param>
		/// <param name="p_primitive">Primitive to add to the tree</param>
		Octree(int p_maxDepth, int p_maxPrimitives, float p_originalRegionSize, std::vector<std::shared_ptr<Collider>> p_primitive);

		/// <summary>
		/// Build the tree
		/// </summary>
		void build();

		/// <summary>
		/// Retrieve every possible collisions in the tree
		/// </summary>
		/// <returns> Possible collisison found by the tree</returns>
		std::vector<std::vector<std::shared_ptr<Collider>>> getPossibleCollison();

		/// <summary>
		/// Clear the tree
		/// </summary>
		void clear();

		// Destructor
		~Octree();
	};
}

