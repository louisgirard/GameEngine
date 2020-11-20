#include <GraphicEngine/SceneGraph/Header/PParticle.hpp>

#include <GL/freeglut_std.h>

namespace GraphicEngine::PSceneGraph {
	PParticle::PParticle(Vector3 p_color, float p_size)
	{

		_size = p_size;

		/*
		* Get shader
		*/
		_shaderName = Servers::ShaderServer::getSingleton()->getDefaultMeshShader();

		/*
		* Creating Mesh
		*/
		std::vector<glm::vec3> sphereVertices;
		std::vector<glm::vec3> sphereNormal;
		std::vector<glm::vec2> sphereTexCoords;

		float x, y, z, xy;                              // vertex position
		float nx, ny, nz, lengthInv = 1.0f / p_size;    // vertex normal
		float s, t;                                     // vertex texCoord

		int sectorCount = 100;
		int stackCount = 100;

		float sectorStep = 2.f * (float)PI / sectorCount;
		float stackStep = (float)PI / stackCount;
		float sectorAngle, stackAngle;

		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = (float)PI / 2.f - (float)i * stackStep;        // starting from pi/2 to -pi/2
			xy = p_size * cosf(stackAngle);             // r * cos(u)
			z = p_size * sinf(stackAngle);              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position (x, y, z)
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
				sphereVertices.push_back(glm::vec3(x, y, z));

				// normalized vertex normal (nx, ny, nz)
				nx = -x * lengthInv;
				ny = -y * lengthInv;
				nz = -z * lengthInv;
				sphereNormal.push_back(glm::vec3(nx, ny, nz));

				// vertex tex coord (s, t) range between [0, 1]
				s = (float)j / sectorCount;
				t = (float)i / stackCount;
				sphereTexCoords.push_back(glm::vec2(s, t));
			}
		}
		std::vector<GLuint> indices;
		int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);     // beginning of current stack
			k2 = k1 + sectorCount + 1;      // beginning of next stack

			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding first and last stacks
				// k1 => k2 => k1+1
				if (i != 0)
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}

				// k1+1 => k2 => k2+1
				if (i != (stackCount - 1))
				{
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}
			}
		}

		_mesh->setVertices(sphereVertices);
		_mesh->setNormals(sphereNormal);
		_mesh->setTextureCoodinates(sphereTexCoords);
		_mesh->setIndices(indices);
		_mesh->forceTextureCoordinates();

		_VAO = Servers::ShaderServer::getSingleton()->getMeshVAO(_shaderName, *_mesh);


		/*
		* Creating Material
		*/

		_material = std::make_shared<Materials::PhongMaterial>();

		glm::vec3 color = glm::vec3(p_color._x, p_color._y, p_color._z);
		glm::vec3 specular = glm::vec3(0.0f, 0.0f,0.0f);

		_material->setDiffuse(color);
		_material->setSpecular(specular);
		_material->setShininess(0.5f);
	}

	float PParticle::getSize() const {
		return _size;
	}

	void PParticle::draw(Vector3 p_position) {
		PMeshObject::draw(_shaderName, glm::vec3(p_position._x, p_position._y, p_position._z));
	}
}