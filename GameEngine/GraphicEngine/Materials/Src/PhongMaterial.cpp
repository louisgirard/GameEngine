#include <GraphicEngine/Materials/Header/PhongMaterial.hpp>

namespace GraphicEngine::Materials {
		PhongMaterial::PhongMaterial(bool p_useDefaultTextures)
			: _emissive(0), _ambient(0), _diffuse(0), _specular(0), _shininess(1.0), _diffuseTexture(nullptr), _specularTexture(nullptr), _normalTexture(nullptr)
		{
			if (p_useDefaultTextures)
			{
				_diffuseTexture = Servers::TextureServer::getSingleton()->loadTexture(GraphicEngine::defaultWhiteTexture());
				_specularTexture = Servers::TextureServer::getSingleton()->loadTexture(GraphicEngine::defaultWhiteTexture());
				_normalTexture = Servers::TextureServer::getSingleton()->loadTexture(GraphicEngine::defaultNormalMap());
			}
		}

#pragma region GETTERS
		const glm::vec3& PhongMaterial::getEmissive() const {
			return _emissive;
		}

		const glm::vec3& PhongMaterial::getAmbient() const {
			return _ambient;
		}

		const glm::vec3& PhongMaterial::getDiffuse() const {
			return _diffuse;
		}

		const glm::vec3& PhongMaterial::getSpecular() const {
			return _specular;
		}

		GLfloat PhongMaterial::getShininess() const {
			return _shininess;
		}

		Textures::Texture2D* PhongMaterial::getDiffuseTexture() const {
			return _diffuseTexture;
		}

		Textures::Texture2D* PhongMaterial::getSpecularTexture() const {
			return _specularTexture;
		}

		Textures::Texture2D* PhongMaterial::getNormalTexture() const {
			return _normalTexture;
		}
#pragma endregion


#pragma region SETTERS
		void PhongMaterial::setEmissive(const glm::vec3& p_emissive) {
			_emissive = p_emissive;
		}

		void PhongMaterial::setAmbient(const glm::vec3& p_ambient) {
			_ambient = p_ambient;
		}

		void PhongMaterial::setDiffuse(const glm::vec3& p_diffuse) {
			_diffuse = p_diffuse;
		}

		void PhongMaterial::setSpecular(const glm::vec3& p_specular) {
			_specular = p_specular;
		}

		void PhongMaterial::setShininess(GLfloat p_shininess) {
			_shininess = p_shininess;
		}

		void PhongMaterial::setDiffuseTexture(Textures::Texture2D* p_texture) {
			_diffuseTexture = p_texture;
		}

		void PhongMaterial::setSpecularTexture(Textures::Texture2D* p_texture) {
			_specularTexture = p_texture;
		}

		void PhongMaterial::setNormalTexture(Textures::Texture2D* p_texture) {
			_normalTexture = p_texture;
		}
#pragma endregion
}
