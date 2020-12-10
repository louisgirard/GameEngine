#include <GraphicEngine/SceneGraph/Header/PWall.hpp>

namespace GraphicEngine::PSceneGraph {
	PWall::PWall(Vector3 p_center, Vector3 p_normal, float p_length, float p_width, const Vector3& p_color, const Vector3& p_specularColor) :PSceneGraph::PMeshObject()
	{
		/*
		* Get shader
		*/
		_shaderName = Servers::ShaderServer::getSingleton()->getDefaultMeshShader();


		// Compute rotation looking at normal from up direction
		//IF THERE IS AN ISSUE LOOK AT UP VECTOR
		glm::mat4 transform = glm::lookAt(Vector3::toGlm(p_center), Vector3::toGlm(p_center+p_normal), -Vector3::toGlm(Vector3::FRONT));

		
		/*
		* Creating Mesh
		*/
		//Vertices
		std::vector<glm::vec3> quadVertices =
		{
			// (positions)
			transform*glm::vec4(p_center._x - (p_length / 2), p_center._y, p_center._z - (p_width / 2),1),
			transform*glm::vec4(p_center._x - (p_length / 2), p_center._y, p_center._z + (p_width / 2),1),
			transform*glm::vec4(p_center._x + (p_length / 2),  p_center._y, p_center._z - (p_width / 2),1),
			transform*glm::vec4(p_center._x + (p_length / 2), p_center._y, p_center._z + (p_width / 2),1)
		};
		//Normals
		glm::vec3 normal = Vector3::toGlm(p_normal);
		std::vector<glm::vec3> quadNormal =
		{
			// (positions)
			normal,
			normal,
			normal,
			normal
		};
		//Indices
		std::vector<GLuint> indices = {
			0,1,2,2,1,3
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