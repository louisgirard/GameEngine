#include <GraphicEngine/SceneGraph/Header/PIrregularCube.hpp>

namespace GraphicEngine::PSceneGraph {

	PIrregularCube::PIrregularCube(const std::vector<PhysicEngine::Vector3>& p_vertices, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor) {
	
		/*
		* Get shader
		*/
		_shaderName = Servers::ShaderServer::getSingleton()->getDefaultMeshShader();

		const glm::vec3 frontNW = PhysicEngine::Vector3::toGlm(p_vertices[0]);
		const glm::vec3 frontNE = PhysicEngine::Vector3::toGlm(p_vertices[1]);
		const glm::vec3 frontSW = PhysicEngine::Vector3::toGlm(p_vertices[2]);
		const glm::vec3 frontSE = PhysicEngine::Vector3::toGlm(p_vertices[3]);
		const glm::vec3 backNW = PhysicEngine::Vector3::toGlm(p_vertices[4]);
		const glm::vec3 backNE = PhysicEngine::Vector3::toGlm(p_vertices[5]);
		const glm::vec3 backSW = PhysicEngine::Vector3::toGlm(p_vertices[6]);
		const glm::vec3 backSE = PhysicEngine::Vector3::toGlm(p_vertices[7]);


		/*
		* Creating Mesh
		*/
		//Vertices
		std::vector<glm::vec3> quadVertices =
		{
			// (positions)
			frontSW, frontSE, frontNE, frontNW, backSW, backSE, backNE, backNW
		};

		//Normals
		std::vector<glm::vec3> quadNormal =
		{
			// (normals)
			glm::normalize(frontSW - backNE), glm::normalize(frontSE - backNW), glm::normalize(frontNE - backSW), glm::normalize(frontNW - backSE),
			glm::normalize(backSW - frontNE), glm::normalize(backSE - frontNW), glm::normalize(backNE - frontSW), glm::normalize(backNW - frontSE)
		};
		//Indices
		std::vector<GLuint> indices = {
			//Front Face
			0,1,2,2,3,0,
			//Right Face
			1,5,6,6,2,1,
			//Back face
			7,6,5,5,4,7,
			//Left Face
			4,0,3,3,7,4,
			//Bottom Face
			4,5,1,1,0,4,
			//Top Face
			3,2,6,6,7,3
		};


		_mesh->setVertices(quadVertices);
		_mesh->setNormals(quadNormal);
		_mesh->setIndices(indices);
		_mesh->forceTextureCoordinates();

		_VAO = Servers::ShaderServer::getSingleton()->getMeshVAO(_shaderName, *_mesh);


		/*
		* Creating Material
		*/
		_material = std::make_shared<Materials::PhongMaterial>();

		glm::vec3 color = glm::vec3(p_color._x, p_color._y, p_color._z);
		glm::vec3 specular = glm::vec3(p_specularColor._x, p_specularColor._y, p_specularColor._z);

		_material->setDiffuse(color);
		_material->setSpecular(specular);
		_material->setShininess(0.5f);
	}
}