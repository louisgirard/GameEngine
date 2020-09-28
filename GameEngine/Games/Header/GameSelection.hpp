#ifndef _Games_GameSelection
#define _Games_GameSelection

#include <vector>
#include <functional>
#include <string>
#include <type_traits>
#include <Games/Header/GameBase.hpp>
#include <iostream>

namespace Games
{
	class GameSelection
	{
	private:
		static ::std::vector<::std::function<GameBase * ()> > s_gameFactories;
		static ::std::vector<::std::string> s_gameDescriptions;

		static void printSelectionMenu();

		static int select();

	public:

		static void registerFactory(::std::function<GameBase* ()> const & p_factory, ::std::string const & p_decription);

		// Needs to declare generic function in .h cause of link edition
		template <class App>
		static void registerFactory(::std::string const & title, ::std::string const & description) {
			registerFactory<App>(title + "\n" + description);
		} 

		template <class App>
		static void registerFactory(::std::string const & title) {
			registerFactory([]() -> GameBase* { return new App; }, title);
		}

		template <class App>
		static void registerFactory() {
			registerFactory<App>(typeid(App).name());
		}

		static bool selectAndRun();
	};
}
#endif