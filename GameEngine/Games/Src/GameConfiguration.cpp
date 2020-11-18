#include <Games/Header/GameConfiguration.hpp>

namespace Games {
	GameConfiguration::GameConfiguration() : _name("Game"), _useGraphics(true), _fpsRate(FPS::FpsMax),
		_glutDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE),
		_windowWidth(DEFAULT_WINDOW_WIDTH), _windowHeight(DEFAULT_WINDOW_HEIGHT),
		_fov(DEFAULT_FOV), _nearPlane(DEFAULT_NEAR_PLANE), _farPlane(DEFAULT_FAR_PLANE) {}

#pragma region GETTERS
	bool GameConfiguration::graphicEnabled() const {
		return _useGraphics;
	}

	int GameConfiguration::getWindowWidth() const {
		return _windowWidth;
	}

	int GameConfiguration::getWindowHeight() const {
		return _windowHeight;
	}

	std::string GameConfiguration::getName() const {
		return _name;
	}

	GLfloat GameConfiguration::getFOV() const {
		return _fov;
	}

	GLfloat GameConfiguration::getNearPlane() const {
		return _nearPlane;
	}

	GLfloat GameConfiguration::getFarPlane() const {
		return _farPlane;
	}

	GLint GameConfiguration::getDisplayMode() const {
		return _glutDisplayMode;
	}

	FPS GameConfiguration::getFPS() const {
		return _fpsRate;
	}
#pragma endregion

#pragma region SETTERS
	void GameConfiguration::enableGraphic(bool p_state) {
		_useGraphics = p_state;
	}

	void GameConfiguration::setWindowDimension(int p_width, int p_height) {
		_windowHeight = p_height;
		_windowWidth = p_width;
	}

	void GameConfiguration::setName(std::string p_name) {
		_name = p_name;
	}

	void GameConfiguration::setProjectionFrustum(GLfloat p_fov, GLfloat p_nearPlane, GLfloat p_farPlane) {
		_fov = p_fov;
		_nearPlane = p_nearPlane;
		_farPlane = p_farPlane;
	}

	void GameConfiguration::setDisplayMode(GLint p_mode) {
		_glutDisplayMode = p_mode;
	}

	void GameConfiguration::setFPS(FPS p_fpsRate) {
		_fpsRate = p_fpsRate;
	}

#pragma endregion
	GameConfiguration GameConfiguration::disabledGraphicConfig() {
		GameConfiguration config;
		config.enableGraphic(false);
		return config;
	}
}