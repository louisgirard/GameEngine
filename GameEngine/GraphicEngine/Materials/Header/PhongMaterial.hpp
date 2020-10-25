#ifndef _GRAPHIC_ENGINE_PHONG_MATERIAL_HPP
#define _GRAPHIC_ENGINE_PHONG_MATERIAL_HPP

#include <glm/glm.hpp>

#include <GraphicEngine/Servers/Header/TextureServer.hpp>
#include <GraphicEngine/Header/GraphicConfig.hpp>

namespace GraphicEngine::Materials {
		class PhongMaterial
		{
		protected:

			// Emissive light color  
			glm::vec3 _emissive;
			// Ambient light color
			glm::vec3 _ambient;
			// Diffuse default color
			glm::vec3 _diffuse;
			// Specular default color
			glm::vec3 _specular;
			// Shininess coefficient
			GLfloat _shininess;

			// Diffuse texture
			Textures::Texture2D* _diffuseTexture;
			// Specular texture
			Textures::Texture2D* _specularTexture;
			// Normal texture
			Textures::Texture2D* _normalTexture;

		public:

			/*
			* Constructor
			* @param p_useDefaultTextures : Use defaults textures 
			*/
			PhongMaterial(bool p_useDefaultTextures = true);

#pragma region GETTERS
			/*
			* Gets the emissive color
			* @return emmissive color
			*/
			const glm::vec3& getEmissive() const;

			/*
			* Gets the ambient color
			* @return ambient color
			*/
			const glm::vec3& getAmbient() const;

			/*
			* Gets the diffuse color
			* @return diffuse color
			*/
			const glm::vec3& getDiffuse() const;

			/*
			* Gets the specular color
			* @return specular color
			*/
			const glm::vec3& getSpecular() const;

			/*
			* Gets the shininess
			* @return shininess
			*/
			GLfloat getShininess() const;

			/*
			* Gets the diffuse texture
			* @return diffuse texture
			*/
			Textures::Texture2D* getDiffuseTexture() const;

			/*
			* Gets the specular texture
			* @return specular texture
			*/
			Textures::Texture2D* getSpecularTexture() const;

			/*
			* Gets the normal texture
			* @return normal texture
			*/
			Textures::Texture2D* getNormalTexture() const;
#pragma endregion

#pragma region SETTERS
			/*
			* Sets the emissive color
			* @param p_emissive : New emissive color
			*/
			void setEmissive(const glm::vec3& p_emissive);

			/*
			* Sets the ambient color
			* @param p_ambient : New ambient color
			*/
			void setAmbient(const glm::vec3& p_ambient);

			/*
			* Sets the diffuse color
			* @param p_diffuse : New diffuse color
			*/
			void setDiffuse(const glm::vec3& p_diffuse);

			/*
			* Sets the specular color
			* @param p_specular : New specular color
			*/
			void setSpecular(const glm::vec3& p_specular);
			/*
			* Sets the shininess
			* @param p_shininess : New shininess
			*/
			void setShininess(GLfloat p_shininess);

			/*
			* Sets the diffuse texture
			* @param p_texture : New diffuse texture
			*/
			void setDiffuseTexture(Textures::Texture2D* p_texture);
			
			/*
			* Sets the specular texture
			* @param p_texture : New specular texture
			*/
			void setSpecularTexture(Textures::Texture2D* p_texture);

			/*
			* Sets the normal texture
			* @param p_texture : New normal texture
			*/
			void setNormalTexture(Textures::Texture2D* p_texture);
#pragma endregion
		};
}

#endif // !_GRAPHIC_ENGINE_PHONG_MATERIAL_HPP



