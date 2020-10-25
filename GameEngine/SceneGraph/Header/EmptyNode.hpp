#pragma once

#include <memory>
#include <string>
#include <iostream>

#include <GraphicEngine/SceneBase/Header/BoundingBox.hpp>

namespace SceneGraph {
	class EmptyNode
	{
	protected:
		/* The child of the node*/
		std::vector<std::shared_ptr<EmptyNode>> _sons;

	public:

		/* Default constructor */
		EmptyNode(){}

		/* 
		* Draws this node
		* @param p_shaderName : Name of the shader we are using now to render the node
		*/
		virtual void draw(std::string p_shaderName);

		/*
		* Compute a bounding box for this node and its child
		* @return a bounding box encompassing the scene contained in this node
		*/
		virtual GraphicEngine::SceneBase::BoundingBox computeSceneBoundingBox();

#pragma region SETTERS
		/*
		* Adds the node as a son
		* @param p_node : New son
		*/
		void addSon(std::shared_ptr<EmptyNode> p_node);
#pragma endregion

#pragma region ITERATORS
		/*
		* Gets an iterator to the first son
		* @return an iterator to the first son
		*/
		std::vector<std::shared_ptr<EmptyNode>>::iterator begin();

		/*
		* Gets an iterator to the first son
		* @return an iterator to the first son
		*/
		std::vector<std::shared_ptr<EmptyNode>>::const_iterator begin() const;


		/*
		* Gets an iterator to past the end of the son list
		* @return an iterator  to past the end of the son list
		*/
		std::vector<std::shared_ptr<EmptyNode>>::iterator end();

		/*
		* Gets an iterator to past the end of the son list
		* @return an iterator  to past the end of the son list
		*/
		std::vector<std::shared_ptr<EmptyNode>>::const_iterator end() const;
#pragma endregion

	};
}

