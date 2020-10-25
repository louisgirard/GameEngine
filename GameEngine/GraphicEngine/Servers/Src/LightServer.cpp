#include <GraphicEngine/Servers/Header/LightServer.hpp>

namespace GraphicEngine::Servers {

#pragma region LIGHT
		LightServer::Light::Light(PhysicEngine::Vector3 const& p_position, Materials::Color const& p_ambient, Materials::Color const& p_diffuse, Materials::Color const& p_specular)
			: _position(p_position), _ambient(p_ambient), _diffuse(p_diffuse), _specular(p_specular), _id(0)
		{}

		LightServer::Light::~Light()
		{
			// Disable the light in the server
			if (isEnabled()) { disable(); }
		}

#pragma region BINDING
		void LightServer::Light::bind()
		{
			// Assert the id is valid in openGL
			assert(_id != 0);
			glDisable(_id);
			glEnable(_id);
			// Sets light options
			glLightfv(_id, GL_AMBIENT, _ambient.getBuffer());
			glLightfv(_id, GL_DIFFUSE, _diffuse.getBuffer());
			glLightfv(_id, GL_SPECULAR, _specular.getBuffer());
			//Set the position as buffer to send it in openGL
			float positionBuffer[4];
			positionBuffer[0] = _position._x;
			positionBuffer[1] = _position._y;
			positionBuffer[2] = _position._z;
			positionBuffer[3] = 1.0f;
			glLightfv(_id, GL_POSITION, positionBuffer);
		}
#pragma endregion

#pragma region ENABLING
		void LightServer::Light::enable()
		{
			assert(_id == 0);
			_id = LightServer::getSingleton()->allocateLight();
			bind();
		}

		void LightServer::Light::disable()
		{
			assert(_id != 0);
			LightServer::getSingleton()->deallocateLight(_id);
			_id = 0;
		}
#pragma endregion

#pragma region GETTERS
		bool LightServer::Light::isEnabled() const
		{
			return _id != 0;
		}

		const Materials::Color& LightServer::Light::getAmbient() const
		{
			return _ambient;
		}

		const Materials::Color& LightServer::Light::getDiffuse(Materials::Color const& color) const
		{
			return _diffuse;
		}

		const Materials::Color& LightServer::Light::getSpecular() const
		{
			return _specular;
		}

		PhysicEngine::Vector3 LightServer::Light::getPosition() const
		{
			return _position;
		}
#pragma endregion

#pragma region SETTERS
		void LightServer::Light::setAmbient(Materials::Color const& p_color)
		{
			_ambient = p_color;
			if (isEnabled())
			{
				glLightfv(_id, GL_AMBIENT, _ambient.getBuffer());
			}
		}

		void LightServer::Light::setDiffuse(Materials::Color const& p_color)
		{
			_diffuse = p_color;
			if (isEnabled())
			{
				glLightfv(_id, GL_DIFFUSE, _diffuse.getBuffer());
			}
		}

		void LightServer::Light::setSpecular(Materials::Color const& p_color)
		{
			_specular = p_color;
			if (isEnabled())
			{
				glLightfv(_id, GL_SPECULAR, _specular.getBuffer());
			}
		}

		void LightServer::Light::setPosition(PhysicEngine::Vector3 const& p_position)
		{
			_position = p_position;
			if (isEnabled())
			{
				float positionBuffer[4];
				positionBuffer[0] = _position._x;
				positionBuffer[1] = _position._y;
				positionBuffer[2] = _position._z;
				positionBuffer[3] = 1.0f;
				glLightfv(_id, GL_POSITION, positionBuffer);
			}
		}
#pragma endregion

#pragma endregion

#pragma region LIGHT_SERVER
		LightServer::LightServer() : _lightMask(0)
		{
			for (int cpt = 0; cpt < 8; cpt++)
			{
				glDisable(GL_LIGHT0 + cpt);
			}
		}

		LightServer::~LightServer()
		{
			// Release memory from the allocated light
			for (auto it = _lights.begin(); it != _lights.end(); ++it)
			{
				delete (*it);
			}
		}

		LightServer* LightServer::getSingleton()
		{
			static LightServer s_server;
			return &s_server;
		}

#pragma region GETTERS
		int LightServer::freeLights() const
		{
			int result = 0;
			for (int cpt = 0; cpt < 8; ++cpt)
			{
				if (((_lightMask >> cpt) & 1) == 0) // If the slot is free
				{
					result++;
				}
			}
			return result;
		}

		unsigned char LightServer::getLightMask()
		{
			return _lightMask;
		}
#pragma endregion

#pragma region ALLOCATION
		GLint LightServer::allocateLight()
		{
			assert(freeLights() > 0);
			for (int cpt = 0; cpt < 8; ++cpt)
			{
				if (((_lightMask >> cpt) & 1) == 0) // If the slot is free
				{
					// Change bit to one to mark the light has used
					_lightMask |= 1 << cpt;
					glEnable(GL_LIGHT0 + cpt);
					return GL_LIGHT0 + cpt;
				}
			}
			assert(false);
			return 8;
		}

		void LightServer::deallocateLight(GLint p_light)
		{
			unsigned int index = p_light - GL_LIGHT0;
			assert(((_lightMask >> index) & 1) == 1);
			glDisable(p_light);
			// Update mask to mark the light as unused
			_lightMask &= ~(1 << index);
		}
#pragma endregion

#pragma region CREATION
		LightServer::Light* LightServer::createLight(PhysicEngine::Vector3 const& p_position, Materials::Color const& p_ambient, Materials::Color const& p_diffuse, Materials::Color const& p_specular)
		{
			Light* result = new Light(p_position, p_diffuse, p_diffuse, p_specular);
			_lights.push_back(result);
			return result;
		}

		void LightServer::destroyLight(Light* p_light)
		{
			auto it = ::std::find(_lights.begin(), _lights.end(), p_light);
			if (it == _lights.end()) { assert(0); return; }
			// Erase the light from the buffer and delete it
			::std::swap(_lights.back(), (*it));
			_lights.pop_back();
			_lights.erase(it);
			delete p_light;
		}
#pragma endregion
#pragma endregion

}