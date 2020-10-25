#include <SceneGraph/Header/EmptyNode.hpp>

namespace SceneGraph {

	void EmptyNode::draw(std::string p_shaderName) {
		for (std::vector<std::shared_ptr<EmptyNode>>::iterator it = _sons.begin(); it != _sons.end(); ++it) {
			(*it)->draw(p_shaderName);
		}
	}

	GraphicEngine::SceneBase::BoundingBox EmptyNode::computeSceneBoundingBox()
	{
		GraphicEngine::SceneBase::BoundingBox result;

		for (std::vector<std::shared_ptr<EmptyNode>>::iterator it = _sons.begin(); it != _sons.end(); ++it) {
			if ((*it) == nullptr) std::cout << "A son is null " << std::endl;
			result = result + (*it)->computeSceneBoundingBox();
		}

		return result;
	}

#pragma region SETTERS
	void EmptyNode::addSon(std::shared_ptr<EmptyNode> p_node) {
		p_node->computeSceneBoundingBox();
		_sons.push_back(p_node);
	}
#pragma endregion

#pragma region ITERATORS
	std::vector<std::shared_ptr<EmptyNode>>::iterator EmptyNode::begin() {
		return _sons.begin();
	}

	std::vector<std::shared_ptr<EmptyNode>>::const_iterator EmptyNode::begin() const {
		return _sons.begin();
	}

	std::vector<std::shared_ptr<EmptyNode>>::iterator EmptyNode::end() {
		return _sons.end();
	}

	std::vector<std::shared_ptr<EmptyNode>>::const_iterator EmptyNode::end() const {
		return _sons.end();
	}
#pragma endregion
}