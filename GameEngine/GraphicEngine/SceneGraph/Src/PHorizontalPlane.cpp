#include <GraphicEngine/SceneGraph/Header/PHorizontalPlane.hpp>

namespace GraphicEngine::PSceneGraph {
	PHorizontalPlane::PHorizontalPlane(Vector3 p_center, float p_length, float p_width,const Vector3& p_color,const Vector3& p_specularColor):PSceneGraph::PMeshObject()
	{
		/*
		* Get shader
		*/
		_shaderName = Servers::ShaderServer::getSingleton()->getDefaultMeshShader();

		/*
		* Creating Mesh
		*/
		//Vertices
		std::vector<glm::vec3> quadVertices =
		{
			// (positions)
			glm::vec3(p_center._x - (p_length/2), p_center._y, p_center._z - (p_width/2)),
			glm::vec3(p_center._x - (p_length / 2), p_center._y, p_center._z + (p_width / 2)),
			glm::vec3(p_center._x + (p_length / 2),  p_center._y, p_center._z - (p_width / 2)),
			glm::vec3(p_center._x + (p_length / 2), p_center._y, p_center._z + (p_width / 2))
		};
		//Normals
		std::vector<glm::vec3> quadNormal =
		{
			// (positions)
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
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