#include <Games/Header/GameConfiguration.h>

namespace Games {

	GameConfiguration::GameConfiguration() : _name("Game"), _useGraphics(true), _fpsRate(FPS::FpsMax),
		_glutDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE),
		_windowWidth(s_defaultWindowWidth), _windowHeight(s_defaultWindowHeight),
		_fov(s_defaultFOV), _nearPlane(s_defaultNearPlane), _farPlane(s_defaultFarPlane){}

	void GameConfiguration::enableGraphic(bool p_state) {
		_useGraphics = p_state;
	}

	bool GameConfiguration::graphicEnabled(){
		return _useGraphics;
	}

	void GameConfiguration::setWindowDimension(int p_width, int p_height) {
		_windowHeight = p_height;
		_windowWidth = p_width;
	}

	int GameConfiguration::getWindowWidth() {
		return _windowWidth;
	}

	int GameConfiguration::getWindowHeight() {
		return _windowHeight;
	}

	void GameConfiguration::setName(std::string p_name) {
		_name = p_name;
	}

	std::string GameConfiguration::getName() {
		return _name;
	}

	void GameConfiguration::setProjectionFrustum(GLfloat p_fov, GLfloat p_nearPlane, GLfloat p_farPlane) {
		_fov = p_fov;
		_nearPlane = p_nearPlane;
		_farPlane = p_farPlane;
	}

	GLfloat GameConfiguration::getFOV() {
		return _fov;
	}

	GLfloat GameConfiguration::getNearPlane() {
		return _nearPlane;
	}

	GLfloat GameConfiguration::getFarPlane() {
		return _farPlane;
	}

	void GameConfiguration::setDisplayMode(GLint p_mode) {
		_glutDisplayMode = p_mode;
	}

	GLint GameConfiguration::getDisplayMode() {
		return _glutDisplayMode;
	}

	void GameConfiguration::setFPS(FPS p_fpsRate) {
		_fpsRate = p_fpsRate;
	}

	FPS GameConfiguration::getFPS() {
		return _fpsRate;
	}
}