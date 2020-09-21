#ifndef _Games_GameConfiguration_H
#define _Games_GameConfiguration_H

#include <Games/Header/DefaultConfig.h>
#include <GL/freeglut.h>
#include <string>

namespace Games {

	typedef enum { FpsMax = 0, Fps60 = 1, Fps30 = 2 } FPS;

	class GameConfiguration
	{
	private :

		std::string _name;

		bool _useGraphics;

		int _windowWidth;
		int _windowHeight;

		GLfloat _fov;
		GLfloat _nearPlane;
		GLfloat _farPlane;
		
		/* Default mode is GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE 
		* Meaning we are displaying in rgb, using a depth buffer,
		* double buffered window(help to address flicker problems) and with window multisampling support 
		*/
		GLuint _glutDisplayMode;

		/// Targetted frame rate. The frame rate will never be greater than the provided value (see FPS enum type).
		FPS _fpsRate;

	public :
		GameConfiguration();

		void enableGraphic(bool p_state);

		bool graphicEnabled(); 

		void setWindowDimension(int p_width, int p_height);

		int getWindowWidth();

		int getWindowHeight();

		void setName(std::string p_name);

		std::string getName();

		void setProjectionFrustum(GLfloat p_fov, GLfloat p_nearPlane, GLfloat p_farPlane);

		GLfloat getFOV();

		GLfloat getNearPlane();

		GLfloat getFarPlane();

		void setDisplayMode(GLint p_mode);

		GLint getDisplayMode();

		void setFPS(FPS p_fpsRate);

		FPS getFPS();
	};
}

#endif // !_Games_GameConfiguration_H



