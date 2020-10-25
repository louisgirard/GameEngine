#include <GraphicEngine/Servers/Header/SceneServer.hpp>

namespace GraphicEngine {
	namespace Servers {
#pragma region CONVERTION
		glm::vec3 SceneServer::convert(const aiColor3D& p_color)
		{
			return glm::vec3(p_color.r, p_color.g, p_color.b);
		}

		std::string SceneServer::convert(const aiString& p_str)
		{
			return p_str.C_Str();
		}

		glm::vec3 SceneServer::convert(const aiVector3D& p_vector)
		{
			return glm::vec3(p_vector.x, p_vector.y, p_vector.z);
		}

		glm::vec2 SceneServer::convert(const aiVector2D& p_vector)
		{
			return glm::vec2(p_vector.x, p_vector.y);
		}

		Materials::PhongMaterial* SceneServer::convert(const aiMaterial& p_material)
		{

			// Result of the material
			Materials::PhongMaterial* result = new Materials::PhongMaterial;
			
			// Out variable to get assimp property
			aiColor3D color;
			aiString name;

			// Default value
			float value = 1.0;

			// Set material property
			if (p_material.Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
			{
				result->setDiffuse(convert(color));
			}
			if (p_material.Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
				result->setSpecular(convert(color));
			if (p_material.Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
				result->setAmbient(convert(color));
			if (p_material.Get(AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS)
				result->setEmissive(convert(color));
			if (p_material.Get(AI_MATKEY_SHININESS, value) == AI_SUCCESS){
				result->setShininess(value);
			}
			else{
				result->setShininess(1.0f);
			}

			// Set material texture property
			p_material.Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), name);
			if (name.length != 0)
			{
				try
				{
					// If the file has a path, try to load it and set it in the material
					std::filesystem::path path = _texturePaths.findFile(convert(name));
					
					Textures::Texture2D* diffuseTexture = Servers::TextureServer::getSingleton()->loadTexture(path, 4, true);
					result->setDiffuseTexture(diffuseTexture);
				}
				catch (const std::exception& e)
				{
					std::cerr << "SceneServer: problem while loading diffuse texture, setting default white texture" << std::endl;
					std::cerr << "\tError" << e.what() << std::endl;
				}
			}
			p_material.Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), name);
			if (name.length != 0)
			{
				try
				{
					// If the file has a path, try to load it and set it in the material
					std::filesystem::path path = _texturePaths.findFile(convert(name));
					Textures::Texture2D* specularTexture = Servers::TextureServer::getSingleton()->loadTexture(path, 4, true);
					result->setSpecularTexture(specularTexture);
				}
				catch (const std::exception& e)
				{
					std::cerr << "SceneServer : problem while loading specular texture, setting default white texture" << std::endl;
					std::cerr << "\tError" << e.what() << std::endl;
				}
			}
			p_material.Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), name);
			if (name.length != 0)
			{
				try
				{
					// If the file has a path, try to load it and set it in the material
					std::filesystem::path path = _texturePaths.findFile(convert(name));
					Textures::Texture2D* normalTexture = Servers::TextureServer::getSingleton()->loadTexture(path, 4, true);
					result->setNormalTexture(normalTexture);
				}
				catch (const std::exception& e)
				{
					std::cerr << "SceneServer: problem while loading normals texture, setting to default normal texture" << std::endl;
					std::cerr << "\tError" << e.what() << std::endl;
				}
			}
			return result;
		}

		std::pair<PSceneGraph::Mesh*, std::shared_ptr<Materials::PhongMaterial>> SceneServer::convert(const aiMesh& p_mesh, size_t p_materialOffset)
		{
			PSceneGraph::Mesh* result = new PSceneGraph::Mesh;

			// Look for already loaded materials to link to the mesh
			std::shared_ptr<Materials::PhongMaterial> material = _materials[p_materialOffset + p_mesh.mMaterialIndex];

			// Out variable to get assimp property
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec3> tangents;
			std::vector<glm::vec3> bitangents;
			std::vector<glm::vec2> textureCoordinates;

			// Reserve memory 
			vertices.reserve(p_mesh.mNumVertices);
			normals.reserve(p_mesh.mNumVertices);
			tangents.reserve(p_mesh.mNumVertices);
			bitangents.reserve(p_mesh.mNumVertices);
			textureCoordinates.reserve(p_mesh.mNumVertices);

			// Retrieve mesh property
			for (size_t cpt = 0; cpt < p_mesh.mNumVertices; ++cpt)
			{
				vertices.push_back(convert(p_mesh.mVertices[cpt]));
				if (p_mesh.HasNormals()) { normals.push_back(convert(p_mesh.mNormals[cpt])); }
				if (p_mesh.HasTangentsAndBitangents())
				{
					tangents.push_back(convert(p_mesh.mTangents[cpt]));
					bitangents.push_back(convert(p_mesh.mBitangents[cpt]));
				}
				if (p_mesh.HasTextureCoords(0)) { textureCoordinates.push_back(glm::vec2(p_mesh.mTextureCoords[0][cpt][0], p_mesh.mTextureCoords[0][cpt][1])); }
			}

			// Initialize the mesh
			result->setVertices(vertices);
			if (normals.size() > 0) { result->setNormals(normals); }
			if (tangents.size() > 0) { result->setTangents(tangents); }
			if (bitangents.size() > 0) { result->setBitagents(bitangents); }
			if (textureCoordinates.size() > 0) { result->setTextureCoodinates(textureCoordinates); }

			// Retrieve faces 
			std::vector<GLuint> indices;
			indices.reserve(p_mesh.mNumFaces * 3);
			for (unsigned int cpt = 0; cpt < p_mesh.mNumFaces; ++cpt)
			{
				const aiFace& face = p_mesh.mFaces[cpt];
				if (face.mNumIndices != 3) { continue; }
				for (size_t i = 0; i < 3; ++i)
				{
					indices.push_back(face.mIndices[i]);
				}
			}
			// Initialize mesh faces
			if (indices.size() > 0) { result->setIndices(indices); }

			return { result, material };
		}
#pragma endregion


		SceneServer* SceneServer::getSingleton()
		{
			static SceneServer server;
			return &server;
		}

		void SceneServer::clear() {
			_materials.clear();
			_scenesRootNode.clear();
		}

		std::shared_ptr <SceneGraph::EmptyNode> SceneServer::load(std::filesystem::path p_fileName, bool p_forcesTexture) {

			// 1- Find a node already generated
			auto found = _scenesRootNode.find(p_fileName);
			if (found != _scenesRootNode.end()) {
				std::cout << "Scene " << p_fileName << " was registered" << std::endl;
				return found->second; }

			// 2 - Try to find the file 
			{
				p_fileName = _geometryPaths.findFile(p_fileName);

				// If we found it had root to the path else we can't load the mesh there is an error
				if (!std::filesystem::exists(p_fileName))
				{
					std::cerr << "SceneServer: could not find file " << p_fileName.string() << std::endl;
					throw std::ios_base::failure(std::string("SceneServer: could not find file ") + p_fileName.string());
				}
				{
					std::filesystem::path tmp = p_fileName;
					tmp.remove_filename();
					_texturePaths.registerPath(tmp);
				}
			}

			// 3 - Load the mesh from the file with assimp librairie
			std::cout << "SceneServer: loading file " << p_fileName.string() << "..." << std::flush;
			Assimp::Importer importer;
			const aiScene* scene;
			{
				scene = importer.ReadFile(p_fileName.string(),
					aiProcess_JoinIdenticalVertices |
					aiProcess_Triangulate |
					aiProcess_GenSmoothNormals |
					aiProcess_PreTransformVertices |
					aiProcess_ImproveCacheLocality |
					aiProcess_RemoveRedundantMaterials |
					aiProcess_FindDegenerates |
					aiProcess_FindInvalidData |
					aiProcess_TransformUVCoords |
					aiProcess_CalcTangentSpace |
					aiProcess_OptimizeMeshes |
					aiProcess_OptimizeGraph
				);

				// If we could not load the file throw an error
				if (!scene)
				{
					std::cout << "NOT OK" << std::endl << "SceneServer: Assimp could not load the scene " << p_fileName.string() << std::endl;
					_texturePaths.pop();
					throw std::ios_base::failure("Loader: Assimp could not load file " + p_fileName.string());
				}
				std::cout << "OK" << std::endl;
			}

			// 4 - Register found materials and meshs 

			// We save the starting points of the materials associated with this file
			size_t materialOffset = _materials.size();
			size_t meshOffset = _scenesRootNode.size();
			std::shared_ptr<SceneGraph::EmptyNode> rootNode = std::make_shared<SceneGraph::EmptyNode>();
			{
				// We process the materials
				for (size_t cpt = 0; cpt < scene->mNumMaterials; ++cpt)
				{
					_materials.push_back(std::make_shared<Materials::PhongMaterial>(std::move(*convert(*scene->mMaterials[cpt]))));
				}
				// We process the geometries
				for (size_t cpt = 0; cpt < scene->mNumMeshes; ++cpt)
				{
					std::pair<PSceneGraph::Mesh*, std::shared_ptr<Materials::PhongMaterial>> pairTmp = convert(*scene->mMeshes[cpt], materialOffset);
					std::shared_ptr<SceneGraph::CMeshObject> newNode =std::make_shared<SceneGraph::CMeshObject>(pairTmp.first, pairTmp.second, ShaderServer::getSingleton()->getDefaultMeshShader(), p_forcesTexture);
					rootNode->addSon(newNode);
				}
				_texturePaths.pop();
			}
			_scenesRootNode[p_fileName] = rootNode;

			return _scenesRootNode.find(p_fileName)->second;
		}
		

#pragma region PATHS
		void SceneServer::addGeometryPath(const std::filesystem::path& p_path)
		{
			_geometryPaths.registerPath(p_path);
		}

		void SceneServer::addTexturePath(const std::filesystem::path& p_path)
		{
			_texturePaths.registerPath(p_path);
		}
#pragma endregion

#pragma region ITERATORS
		std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>>::iterator SceneServer::begin() {
			return _scenesRootNode.begin();
		}

		std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>>::const_iterator SceneServer::begin() const {
			return _scenesRootNode.begin();
		}

		std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>>::iterator SceneServer::end() {
			return _scenesRootNode.end();
		}

		std::map<std::filesystem::path, std::shared_ptr<SceneGraph::EmptyNode>>::const_iterator SceneServer::end() const {
			return _scenesRootNode.end();
		}
#pragma endregion
	}
}