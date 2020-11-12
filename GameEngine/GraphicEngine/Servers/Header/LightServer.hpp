#pragma once

#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

#include <GraphicEngine/Materials/Header/Color.hpp>
#include <PhysicEngine/Header/MathEnabler.hpp>

namespace GraphicEngine::Servers {
		class LightServer
		{
		public:
			class Light
			{
			protected:
				/*	The identifier of the light (0 if the light is disabled) */
				GLuint _id;

				/* The position of the light */
				PhysicEngine::Vector3 _position;

				/* The ambient color */
				Materials::Color _ambient;
				/* The light diffuse color */
				Materials::Color _diffuse;
				/* The light specular color */
				Materials::Color _specular;


			protected:

				/*
				* Constructor
				* A Light can't be constructed on its own. The construction must pass via a LightServer
				*
				* @param p_position : The light's position
				* @param p_ambient : The ambient color
				* @param p_diffuse : The light diffuse color
				* @param p_specular : The light specular color
				*/
				Light(PhysicEngine::Vector3 const& p_position, Materials::Color const& p_ambient, Materials::Color const& p_diffuse, Materials::Color const& p_specular);

				/* Destructor
				* You can only destroy a light via the server
				*/
				~Light();

#pragma region BINDING
				/*
				* Binds this light in openGL
				*/
				void bind();
#pragma endregion

			public:
				friend class LightServer;

#pragma region ENABLING
				/*
				* Enables the light in the server
				*/
				void enable();

				/*
				* Disables the light in the server
				*/
				void disable();
#pragma endregion

#pragma region GETTERS
				/*
				* Determines whether the light is enabled in the server
				* @return true if enabled, else false
				*/
				bool isEnabled() const;

				/*
				* Gets the ambient color
				* @return the ambient color
				*/
				const  Materials::Color& getAmbient() const;

				/*
				* Gets the diffuse color
				* @return the diffuse color
				*/
				const  Materials::Color& getDiffuse(Materials::Color const& color) const;

				/*
				* Gets the specular color
				* @return the specular color
				*/
				const  Materials::Color& getSpecular() const;

				/*
				* Gets the position
				* @return the light's position
				*/
				PhysicEngine::Vector3 getPosition() const;
#pragma endregion

#pragma region SETTERS
				/*
				* Sets the ambient color
				* @param p_color : New ambient
				*/
				void setAmbient(Materials::Color const& p_color);

				/*
				* Sets the diffuse color
				* @param p_color : New diffuse
				*/
				void setDiffuse(Materials::Color const& p_color);

				/*
				* Sets the specular color
				* @param p_color : New specular
				*/
				void setSpecular(Materials::Color const& p_color);

				/*
				* Sets the position
				* @param p_position : New position
				*/
				void setPosition(PhysicEngine::Vector3 const& p_position);
#pragma endregion
			};
		private:
			/* The used lights. For each active light, a bit is set to one (index of the bit = index of the light) */
			unsigned char _lightMask;
			/* The allocated lights */
			::std::vector<Light*> _lights;

			/* Default constructor. Can only be accessed via singleton*/
			LightServer();

			/* Destructor */
			~LightServer();

		protected:
			
#pragma region GETTERS
			/*
			* Gets the number of free light
			* @return the number of free light
			*/
			int freeLights() const;
#pragma endregion

#pragma region ALLOCATION
			/*
			* Allocates a light and return its identifier
			* @return the allocated light identifier
			*/
			GLint allocateLight();

			/*
			* Deallocates a light
			* @param p_light : the light to freed
			*/
			void deallocateLight(GLint p_light);
#pragma endregion

		public:

			/*
			* Gets the unique instance of the server
			* @return the instance of the light server
			*/
			static LightServer* getSingleton();

#pragma region CREATION
			/*
			* Creates a light.
			* By default, the created light if not activated. Please, call the enable method if needed.
			* 
			* @param p_position : The light's position
			* @param p_ambient : The ambient color
			* @param p_diffuse : The light's diffuse color
			* @param p_specular : The light's specular color
			* @return the new light
			*/
			Light* createLight(PhysicEngine::Vector3 const& p_position, Materials::Color const& p_ambient, Materials::Color const& p_diffuse, Materials::Color const& p_specular);

			/*
			* Destroy the light
			* @param (out) p_light : If non-null the loght to destroy
			*/
			void destroyLight(Light* p_light);
#pragma endregion

#pragma region GETTERS
			/*
			* Gets the light mask. 
			* In this mask, the index of each bit set to 1 is the index of a used light.
			* @return the light mask
			*/
			unsigned char getLightMask();
#pragma endregion
		};
}



