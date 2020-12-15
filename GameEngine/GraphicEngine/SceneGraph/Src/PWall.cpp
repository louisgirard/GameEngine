#include <GraphicEngine/SceneGraph/Header/PWall.hpp>
#include <glm/gtc/matrix_access.hpp>
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

namespace GraphicEngine::PSceneGraph {
	PWall::PWall(Vector3 p_center, Vector3 p_normal, float p_length, float p_width, const Vector3& p_color, const Vector3& p_specularColor) :PSceneGraph::PMeshObject()
	{
		/*
		* Get shader
		*/
		_shaderName = Servers::ShaderServer::getSingleton()->getDefaultMeshShader();


		//New Up direction
		vec3 direction = Vector3::toGlm(p_normal); 
		mat3 rotation = glm::identity<glm::mat3>();
		mat4 transform = mat4(rotation);
		//If up is inverse direction then rotate 180 degree
		if (direction.x == 0 && direction.z == 0)
		{
			if (direction.y < 0) {
				transform = glm::rotate(transform, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			
		}
		else {
			vec3 new_y = direction;
			//Normalize cause these are direction
			vec3 new_z = glm::normalize(glm::cross(new_y, vec3(0, 1, 0)));
			vec3 new_x = glm::normalize(glm::cross(new_y, new_z));
			rotation = mat3(new_x, new_y, new_z);
		    transform = mat4(rotation);
		}
		vec4 center = vec4(Vector3::toGlm(p_center),1);
		transform = glm::column(transform, 3, center);
		

		/*
		* Creating Mesh
		*/
		//Vertices
		std::vector<glm::vec3> quadVertices =
		{
			// (positions)
			transform*glm::vec4(- (p_length / 2), 0, - (p_width / 2),1),
			transform*glm::vec4(- (p_length / 2), 0, (p_width / 2),1),
			transform*glm::vec4((p_length / 2),  0, -(p_width / 2),1),
			transform*glm::vec4((p_length / 2), 0,  (p_width / 2),1)
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