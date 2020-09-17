#ifndef _Games_GameConfiguration_H
#define _Games_GameConfiguration_H

namespace Games {

	class GameConfiguration
	{
	private :
		bool _useGraphics;

	public :
		GameConfiguration();

		void enableGraphic(bool p_state);

		bool graphicEnabled(); 
	};
}

#endif // !_Games_GameConfiguration_H



