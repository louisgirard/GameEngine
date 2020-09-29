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

		/**Callbacks function linked to an item of the menu**/
		static std::vector<std::function<void()>> _menuCallbacks;

		/**
		* Call the function link to the selected item
		* @param p_selected : selected item
		**/
		static void menuCallback(int p_selected);

		/**
		* Bind GLUT menu for subsequent operation 
		**/
		void bind();

	protected :

		/**Menu's title**/
		::std::string _title;

		/**GLUT menu's ID**/
		int _menuId;

		/**Button linked to the menu**/
		int _linkedToButton;
		/**Boolean true if there is a button linked to the menu**/
		bool _isButtonLinked;
		

	public :
		/**Constructor
		* @param p_title : menu's title
		**/
		GameMenu(::std::string const& p_title);

		/** Destructor **/
		~GameMenu();

		/**
		* Link a button to this menu
		* @param p_button : button to link to the menu
		**/
		void activate(int p_button);

		/**
		* Deacivate the button linked to this menu
		**/
		void deactivate();

		/**
		* Add an item to this menu
		* @param p_name : item's name
		* @param p_callback : callback function linked to this item
		**/
		void addItem(::std::string const& p_name, const ::std::function<void()>& p_callback);

		/**
		* Add a submenu to this menu
		* @param p_menu : menu to add as submenu
		**/
		void addSubMenu(GameMenu* p_menu);
	};
}

#endif // !_Games_GameMenu_H



