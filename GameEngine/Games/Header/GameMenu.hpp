#ifndef _Games_GameMenu_H
#define _Games_GameMenu_H

#include <vector>
#include <functional>
#include <cassert>

#include <GL/freeglut.h>

namespace Games {
	class GameMenu
	{
	private :
		static std::vector<std::function<void()>> _menuCallbacks;

		static void menuCallback(int p_selected);

		void bind();
	protected :
		::std::string _title;
		int _menuId;
		bool _isButtonLinked;
		int _linkedToButton;

	public :
		GameMenu(::std::string const& p_title);

		~GameMenu();

		void activate(int button);

		void deactivate();

		void addItem(::std::string const& name, const ::std::function<void()>& p_callback);

		void addSubMenu(GameMenu* menu);
	};
}

#endif // !_Games_GameMenu_H



