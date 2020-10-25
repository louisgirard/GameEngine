#pragma once

#include <map>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <System/Header/Paths.hpp>

#include <SceneGraph/Header/EmptyNode.hpp>
#include <SceneGraph/Header/CMeshObject.hpp>

namespace GraphicEngine {
	namespace Servers {
		class SceneServer
		{
		protected:
			
			/* Paths to necessary files */
			System::Paths _geometryPaths;
			System::Paths _texturePaths;
			/* Loaded materials*/
			std::vector<std::shared_ptr<Materials::PhongMaterial>> _materials;
			/* Loaded meshes linked to a material */
			std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>> _scenesRootNode;

#pragma region COPY
			/*Disallow copying */
			SceneServer(const SceneServer&) = delete;
			SceneServer& operator= (const SceneServer&) = delete;
#pragma endregion

		private:
#pragma region CONVERTION
			/*
			* Convert a color from assimp lib to a glm vec3
			* @param p_color : Color to convert
			* @return an equivalent glm vec3 
			*/
			static glm::vec3 convert(const aiColor3D& p_color);
			
			/*
			* Convert a string from assimp lib to string
			* @param p_str : Color to convert
			* @return converted string
			*/
			static std::string convert(const aiString& p_str);
			
			/*
			* Convert a vector3 from assimp lib to a glm vec3
			* @param p_vector : Vector to convert
			* @return an equivalent glm vec3
			*/
			static glm::vec3 convert(const aiVector3D& p_vector);

			/*
			* Convert a vector2 from assimp lib to a glm vec2
			* @param p_vector : Vector to convert
			* @return an equivalent glm vec2
			*/
			static glm::vec2 convert(const aiVector2D& p_vector);

			/*
			* Convert a material from assimp lib to a phongMaterial
			* @param p_material : Material to convert
			* @return an equivalent phongMaterial
			*/
			Materials::PhongMaterial* convert(const aiMaterial& p_material);

			/*
			* Convert a mesh and a material from assimp lib to a custom mesh and a phongMaterial
			* @param p_mesh : Mesh to convert
			* @param p_materialOffset : Offset of the assimp index regarding our registry of the loaded material
			* @return a pair of the equivalent mesh and the material linked to it
			*/
			std::pair<PSceneGraph::Mesh*, std::shared_ptr<Materials::PhongMaterial>> convert(const aiMesh& p_mesh, size_t p_materialOffset);
#pragma endregion

			/*Default constructor*/
			SceneServer() {}

		public:
			/*
			* Gets the singleton
			* @return a single instance of this class
			*/
			static SceneServer* getSingleton();

			/*
			* Resets this instance
			* Call this when before reloading GLUT
			*/
			void clear();

			/*
			* Loads a specified file into a scene
			* 
			* @param p_fileName : Name of the file
			* @param p_forcesTexture : true if the mesh attached to this object needs to have texture coordinates
			* @return root node containing the meshes
			*/
			std::shared_ptr<SceneGraph::EmptyNode> load(std::filesystem::path p_fileName, bool p_forcesTexture = false);

#pragma region PATHS
			/*
			* Adds a search path for the geometries
			* @param p_path : New path
			*/
			void addGeometryPath(const std::filesystem::path& p_path);

			/*
			* Adds a search path for the textures
			* @param p_path : New path
			*/
			void addTexturePath(const std::filesystem::path& p_path);
#pragma endregion

#pragma region ITERATORS
			/*
			* Gets an iterator to the first mesh
			* @return an iterator to the first mesh
			*/
			std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>>::iterator begin();

			/*
			* Gets an iterator to the first mesh
			* @return an iterator to the first mesh
			*/
			std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>>::const_iterator begin() const;


			/*
			* Gets an iterator to past the end of the mesh list
			* @return an iterator  to past the end of the mesh list
			*/
			std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>>::iterator end();

			/*
			* Gets an iterator to past the end of the mesh list
			* @return an iterator  to past the end of the mesh list
			*/
			std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>>::const_iterator end() const;
#pragma endregion
		};
	}
}



