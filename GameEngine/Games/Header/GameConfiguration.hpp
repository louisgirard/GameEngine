#ifndef _Games_GameConfiguration_H
#define _Games_GameConfiguration_H

#include <string>

#include <Games/Header/DefaultConfig.hpp>

namespace Games {

	/**FPS possible rates**/
	typedef enum { FpsMax = 0, Fps60 = 1, Fps30 = 2 } FPS;

	class GameConfiguration
	{
	private :

		/**Game Name**/
		std::string _name;

		/**Does the game use the graphic library**/
		bool _useGraphics;

		/** Targetted frame rate.If used the frame rate will never be greater than the provided value(see FPS enum type). **/
		FPS _fpsRate;

		/*  GLUT display mode
		* Default mode is GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE
		* Meaning we are displaying in rgb, using a depth buffer,
		* double buffered window(help to address flicker problems) and with window multisampling support
		*/
		GLuint _glutDisplayMode;

		/**Game window dimensions**/
		int _windowWidth;
		int _windowHeight;

		/**Camera Frustum**/
		GLfloat _fov;
		GLfloat _nearPlane;
		GLfloat _farPlane;

	public :

		/**Default constructor**/
		GameConfiguration();

#pragma region GETTERS

		/**
		* Are the game graphics enabled ?
		* @return a boolean to specify if the graphic are enabled
		**/
		bool graphicEnabled() const;

		/**
		* Get the game's window width
		* @return width of the game's window
		**/
		int getWindowWidth() const;

		/**
		* Get the game's window height
		* @return height of the game's window
		**/
		int getWindowHeight() const;

		/**
		* Get the game's name
		* @return the name of the game
		**/
		std::string getName() const;

		/**
		* Get the camera field of view
		* @return game's camera field of view
		**/
		GLfloat getFOV() const;

		/**
		* Get the camera near plane
		* @return game's camera near plane
		**/
		GLfloat getNearPlane() const;

		/**
		* Get the camera far plane
		* @return game's camera far plane
		**/
		GLfloat getFarPlane() const;

		/**
		* Get GLUT display mode
		* @return GLUT display mode
		**/
		GLint getDisplayMode() const;

		/**
		* Get FPS rate
		* @return FPS rate
		**/
		FPS getFPS() const;
#pragma endregion


#pragma region SETTERS

		/**
		* Toggle graphic enabling
		* @param p_state : enable value for game's graphics
		**/
		void enableGraphic(bool p_state);

		/**
		* Set window's dimensions
		* @param p_width : game's window width
		* @param p_height : game's window height
		**/
		void setWindowDimension(int p_width, int p_height);

		/**
		* Set game's name
		* @param p_name : game's name
		**/
		void setName(std::string p_name);

		/**
		* Set camera's frustum
		* @param p_fov : camera's field of view
		* @param p_nearPlane : camera's near plane
		* @param p_farPlane : camera's far plane
		**/
		void setProjectionFrustum(GLfloat p_fov, GLfloat p_nearPlane, GLfloat p_farPlane);

		/**
		* Set GLUT display mode
		* @param p_mode : GLUT display mode
		**/
		void setDisplayMode(GLint p_mode);

		/**
		* Set FPS rate 
		* @param p_fpsRate : game's FPS rate
		**/
		void setFPS(FPS p_fpsRate);
#pragma endregion

	};
}

#endif // !_Games_GameConfiguration_H



