#ifndef _Games_DefaultConfig_H
#define _Games_DefaultConfig_H

#include <filesystem>
#include <iostream>

#include <GL/freeglut.h>

#include <System/Header/Paths.hpp>

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

	/*
	* Full pathname of the executable file
	* @return the full path to the executable files
	*/
	inline std::filesystem::path executablePath() { return System::Paths::executable(); }

#if defined WIN32 

	/*
	* Full pathname of the data directory.
	* @return the full path to the data directory
	*/
	inline ::std::filesystem::path dataPath()
	{
		// Get the environment variable set earlier with the setup.exe
		char* path;
		size_t len;
		errno_t err = _dupenv_s(&path, &len, "GameEngineRes");

		if (err) {
			std::cerr << "Error when retrieving GameEngineRes environment variable, switching to relative path" << std::endl;
			return executablePath() / ".." / "Ressources";
		}
		std::filesystem::path res = std::filesystem::path(::std::string(path));
		delete[] path;
		return res;
	}

#else

	inline ::std::filesystem::path dataPath()
	{
		return executablePath() / ".." / "Ressources";
	}
#endif
}

#endif // !_Games_DefaultConfig_
