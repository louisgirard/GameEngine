#include <GraphicEngine/SceneGraph/Header/PIrregularCube.hpp>

namespace GraphicEngine::PSceneGraph {

	PIrregularCube::PIrregularCube(const std::vector<PhysicEngine::Vector3>& p_vertices, const PhysicEngine::Vector3& p_color, const PhysicEngine::Vector3& p_specularColor) {
	
		/*
		* Get shader
		*/
		_shaderName = Servers::ShaderServer::getSingleton()->getDefaultMeshShader();

		const glm::vec3 frontNW = PhysicEngine::Vector3::toGlm(p_vertices[0]);
		const glm::vec3 frontNE = PhysicEngine::Vector3::toGlm(p_vertices[0]);
		const glm::vec3 frontSW = PhysicEngine::Vector3::toGlm(p_vertices[0]);
		const glm::vec3 frontSE = PhysicEngine::Vector3::toGlm(p_vertices[0]);
		const glm::vec3 backNW = PhysicEngine::Vector3::toGlm(p_vertices[0]);
		const glm::vec3 backNE = PhysicEngine::Vector3::toGlm(p_vertices[0]);
		const glm::vec3 backSW = PhysicEngine::Vector3::toGlm(p_vertices[0]);
		const glm::vec3 backSE = PhysicEngine::Vector3::toGlm(p_vertices[0]);


		/*
		* Creating Mesh
		*/
		//Vertices
		std::vector<glm::vec3> quadVertices =
		{
			// (positions)
			frontNW, backNW, frontNE, backNE, frontSW, backSW, frontNE, backSE
		};
		//Normals
		std::vector<glm::vec3> quadNormal =
		{
			// (normals)
			glm::normalize(frontNW - backSE), glm::normalize(backNW - frontSE), glm::normalize(frontNE - backSW), glm::normalize(backNE - frontSW),
			glm::normalize(frontSW - backNE), glm::normalize(backSW - frontNE), glm::normalize(frontSE - backNW), glm::normalize(backSE - frontNW)
		};
		//Indices
		std::vector<GLuint> indices = {
			//Up Face
			0,1,2,2,1,3,
			//Down Face
			4,6,5,5,6,7,
			//Right face
			3,2,7,7,2,6,
			//Left Face
			0,1,5,5,4,0,
			//Front Face
			2,0,6,0,4,6,
			//Back Face
			1,3,7,7,5,1
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