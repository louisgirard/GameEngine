#include <PhysicEngine/Collisions/Header/Octree.hpp>

namespace PhysicEngine::Collisions {

	Octree::Octree(int p_maxDepth, int p_maxPrimitives, float p_originalRegionSize, std::vector<Collider*> p_primitive)
		: _maxDepth(p_maxDepth), _maxPrimitive(p_maxPrimitives), _originalRegionSize(p_originalRegionSize),_primitiveMarked(p_primitive), _root(nullptr){}

	void Octree::build() {
		float halfSize = _originalRegionSize / 2;
		GraphicEngine::SceneBase::BoundingBox baseRegion(glm::vec3(-halfSize,-halfSize,-halfSize), glm::vec3(halfSize, halfSize, halfSize));
		_root = new Node(0, _maxDepth, _maxPrimitive, baseRegion);
		_root->tryAddingPrimitive(_primitiveMarked);
	}

	std::vector<std::vector<Collider*>> Octree::getPossibleCollison() {
		std::vector<std::vector<Collider*>> result;
		_root->browse(result);
		return result;
	}

	void Octree::clear() {
		if (_root != nullptr) delete _root;
	}

	Octree::~Octree() {
		clear();
	}

	Octree::Node::Node(int p_depth, int p_maxDepth, int p_maxPrimitive, GraphicEngine::SceneBase::BoundingBox p_region) :
		_depth(p_depth), _maxDepth(p_maxDepth), _maxPrimitive(p_maxPrimitive),
		_region(p_region) {}

	bool Octree::Node::isLeaf() {
		return _childs.size() == 0;
	}

	void Octree::Node::browse(std::vector<std::vector<Collider*>>& const p_possibleCollisions) {
		if (isLeaf()) {
			if (_primitives.size() >1) {
				p_possibleCollisions.push_back(_primitives);
			}
			return;
		}
		for (std::vector<Node*>::iterator it = _childs.begin(); it != _childs.end(); it++) {
			(*it)->browse(p_possibleCollisions);
		}
	}

	void Octree::Node::subdivise() {
		if (_depth >= _maxDepth || _primitives.size() <= _maxPrimitive) return;

		// Subdivide along the 3 Axis
		GraphicEngine::SceneBase::BoundingBox region;
		glm::vec3 max = glm::vec3(0);
		glm::vec3 min = glm::vec3(0);

		glm::vec3 regionCenter = _region.center();
		glm::vec3 regionHalfDim = _region.extent()/2.0f;
		// Subdivide along x
		for (int x = -1; x < 2; x = x + 2) {
			float xBorder = regionCenter.r + x * regionHalfDim.r;
			max.r = std::max(regionCenter.r, xBorder);
			min.r = std::min(regionCenter.r, xBorder);
			// Subdivide along y
			for (int y = -1; y < 2; y = y + 2) {
				float yBorder = regionCenter.g + y * regionHalfDim.g;
				max.g = std::max(regionCenter.g, yBorder);
				min.g = std::min(regionCenter.g, yBorder);
				// Subdivide along z
				for (int z = -1; z < 2; z = z + 2) {
					float zBorder = regionCenter.b + z * regionHalfDim.b;
					max.z = std::max(regionCenter.b, zBorder);
					min.z = std::min(regionCenter.b, zBorder);
					region = GraphicEngine::SceneBase::BoundingBox(min, max);
					Node* newChild = new Node(_depth + 1, _maxDepth, _maxPrimitive, region);
					newChild->tryAddingPrimitive(_primitives);
					_childs.push_back(newChild);
				}
			}
		}
	}

	void Octree::Node::tryAddingPrimitive(std::vector<Collider*> p_primitives) {
		for (std::vector<Collider*>::iterator it = p_primitives.begin(); it != p_primitives.end(); it++) {
			if ((*it)->insideRegion(_region)) {
				_primitives.push_back(*it);
			}
		}
		subdivise();
	}

	Octree::Node::~Node() {
		for (std::vector<Node*>::iterator it = _childs.begin(); it != _childs.end(); it++) {
			delete (*it);
		}
	}
}