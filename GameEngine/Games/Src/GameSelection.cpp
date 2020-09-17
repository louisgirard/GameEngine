#include <Games/Header/GameSelection.h>


namespace Games {

	::std::vector<::std::function<GameBase * ()> > GameSelection::s_gameFactories;
	::std::vector<::std::string> GameSelection::s_gameDescriptions;

	int GameSelection::select() {
		if (s_gameFactories.size() == 0) return -1;
		while (true) {
			std::cout << "Choose your game (0-" << ((int)s_gameFactories.size() - 1) << ") : ";
			int selection;
			std::cin >> selection;
			if (selection >= -1 && selection < s_gameFactories.size()) return selection;
		}
	}

	void GameSelection::printSelectionMenu() {
		std::cout << "-1 - Quit Engine" << std::endl;
		for (int i = 0; i < s_gameDescriptions.size(); i++) {
			std::cout << i << " : " << s_gameDescriptions[i] << std::endl;
		}
	}
	
	void GameSelection::registerFactory(::std::function<GameBase* ()> const & p_factory, ::std::string const & p_description) {
		s_gameFactories.push_back(p_factory);
		s_gameDescriptions.push_back(p_description);
	 }

	bool GameSelection::selectAndRun() {
		GameBase* game = nullptr;
		printSelectionMenu();
		int gameSelected = select();
		if (gameSelected != -1) {
			game = s_gameFactories[gameSelected]();
			game->launch();
			delete game;
			return true;
		}
		return false;
	}
}