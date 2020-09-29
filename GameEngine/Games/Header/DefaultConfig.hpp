#ifndef _Games_DefaultConfig_H
#define _Games_DefaultConfig_H

#include <GL/freeglut.h>


/**
* File used to define default options for a games such as graphic option 
* or any other that might seems usefull to keep as a default variable 
**/
namespace Games {
	
	static const int DEFAULT_WINDOW_WIDTH = 400;
	static const int DEFAULT_WINDOW_HEIGHT = 400;

	static const GLfloat DEFAULT_FOV = 65.0f;
	static const GLfloat DEFAULT_NEAR_PLANE = 0.01f;
	static const GLfloat DEFAULT_FAR_PLANE = 1000.0f;
}

#endif // !_Games_DefaultConfig_
