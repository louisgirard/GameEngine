#include <Games/Header/GameMenu.h>

namespace Games {
	std::vector<std::function<void()>> GameMenu::_menuCallbacks;

	GameMenu::GameMenu(::std::string const& p_title) : _title(p_title), _menuId(-1), _isButtonLinked(false), _linkedToButton(-1)
	{
		// Create the popup menu
		_menuId = glutCreateMenu(menuCallback);
	}

	GameMenu::~GameMenu()
	{
		// Destroy the Menu in GLUT
		glutDestroyMenu(_menuId);
	}



	void GameMenu::bind()
	{
		//Tell GLUT next menu operation will be for this particular menu
		glutSetMenu(_menuId);
	}

	void GameMenu::menuCallback(int p_selected) {
		_menuCallbacks[p_selected]();
	}

	void GameMenu::activate(int button)
	{
		//We verify that the button being attached comes from the mouse
		assert((button == GLUT_LEFT_BUTTON) || (button == GLUT_MIDDLE_BUTTON) | (button == GLUT_RIGHT_BUTTON));
		//Unlink from current button if there is any
		deactivate();
		//Set current Menu as this in GLUT
		bind();
		//link the button from the menu in GLUT
		glutAttachMenu(button);
	}

	void GameMenu::deactivate()
	{
		if (_isButtonLinked)
		{
			//We actually unlink the button from the menu in GLUT
			glutDetachMenu(_linkedToButton);
			_isButtonLinked = false;
		}
	}

	void GameMenu::addItem(::std::string const& name, const ::std::function<void()>& callback)
	{
		//Set id for this item as the one who will be needed to call it from the vector
		int id = _menuCallbacks.size();
		//Add this item to the menu's vector of item
		_menuCallbacks.push_back(callback);
		//Set current Menu in GLUT as this one
		bind();
		//Add this item in GLUT for display and link purpose
		glutAddMenuEntry(name.c_str(), id);
	}

	void GameMenu::addSubMenu(GameMenu* menu)
	{
		//Set current Menu in GLUT as this one
		bind();
		//Add sub menu to this menu in GLUT
		glutAddSubMenu(menu->_title.c_str(), menu->_menuId);
	}
}
