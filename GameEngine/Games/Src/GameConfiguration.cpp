#include <Games/Header/GameConfiguration.h>

namespace Games {

	GameConfiguration::GameConfiguration() : _useGraphics(true) {
	}

	void GameConfiguration::enableGraphic(bool p_state) {
		_useGraphics = p_state;
	}

	bool GameConfiguration::graphicEnabled(){
		return _useGraphics;
	}

}