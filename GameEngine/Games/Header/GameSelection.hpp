#ifndef _Games_GameSelection
#define _Games_GameSelection

#include <string>
#include <type_traits>

#include <Games/Header/GameBase.hpp>

namespace Games
{
	class GameSelection
	{
	private:

		/**Game registered in the engine**/
		static ::std::vector<::std::function<GameBase * ()> > s_gameFactories;
		/**Definitions of the games registered in the engine**/
		static ::std::vector<::std::string> s_gameDescriptions;

		/**
		* Print available games in the console
		**/
		static void printSelectionMenu();

		/**
		* Select a games in the console from the available one
		* @return the choosen game index if it exist, -1 if the user want to quit the application
		**/
		static int select();

	public:

		/**
		* Register a game in the application
		* @param p_factory : a function that return the registered game
		* @param p_description : the description of the registered game
		**/
		static void registerFactory(::std::function<GameBase* ()> const & p_factory, ::std::string const & p_decription);
		
		
		/**
		* Register a game in the application
		* @param p_title : the title of the game
		* @param p_description : the description of the registered game
		* @param <Game> : the game to register
		**/
		// Needs to declare generic function in .h cause of link edition
		template <class Game>
		static void registerFactory(::std::string const & p_title, ::std::string const & p_description) {
			registerFactory<Game>(p_title + "\n" + p_description);
		} 

		/**
		* Register a game in the application
		* @param p_title : the title of the game
		* @param <Game> : the game to register
		**/
		template <class Game>
		static void registerFactory(::std::string const & p_title) {
			registerFactory([]() -> GameBase* { return new Game; }, p_title);
		}

		/**
		* Register a game in the application
		* @param <Game> : the game to register
		**/
		template <class Game>
		static void registerFactory() {
			registerFactory<Game>(typeid(Game).name());
		}

		/**
		* Select and run an available game
		* @return true if the application has been found and the user didn't ask to quit, false if he asked to quit
		**/
		static bool selectAndRun();
	};
}
#endif