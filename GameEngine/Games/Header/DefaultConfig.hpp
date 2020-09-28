#ifndef _Games_DefaultConfig_H
#define _Games_DefaultConfig_H

#include <GL/freeglut.h>

namespace Games {
	
	static int s_defaultWindowWidth = 400;
	static int s_defaultWindowHeight = 400;

	static GLfloat s_defaultFOV = 65.0f;
	static GLfloat s_defaultNearPlane = 0.01f;
	static GLfloat s_defaultFarPlane = 1000.0f;
}

#endif // !_Games_DefaultConfig_
