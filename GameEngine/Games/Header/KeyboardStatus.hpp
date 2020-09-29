#ifndef _Games_KeyboardStatus_H
#define _Games_KeaboardStatus_H

#include <vector>
#include <iostream>
#include <map>
#include <string>

#include <Games/Header/KeyAction.hpp>

namespace Games {
	class KeyboardStatus
	{
	protected:
		/**Normal key status (pressed or not)**/
		::std::vector<bool> _keyStatus;
		/**Normal key binding to an action**/
		::std::map<int, unsigned char> _keyBinding;

		/**Special key status (pressed or not)**/
		::std::map<int, bool> _specialKeyStatus;
		/**Special key binding to an action**/
		::std::map<int, int> _specialKeyBinding;

	public:

		/**Default Constructor**/
		KeyboardStatus();

		/**
		* Is the key binded to this action pressed 
		* @param p_action : the action we want to check
		* @return true if the key binded is pressed, else false
		**/
		bool isPressed(int p_action) const;

#pragma region NORMAL_KEY
		/**
		* Is the key pressed
		* @param p_key : the key we want to check
		* @return true if the key is pressed, else false
		**/
		bool isPressed(unsigned char p_key) const;

		/**
		* Press the specified key
		* @param p_key : the key to press
		**/
		void press(unsigned char p_key);

		/**
		* Release the specified key
		* @param p_key : the key to release
		**/
		void release(unsigned char p_key);

		/**
		* Bind a key to an action
		* @param p_action : the action to bind to
		* @param p_key : the key to bind
		**/
		void bindActionToKey(int p_action, unsigned char p_key);
#pragma endregion

#pragma region SPECIAL_KEY
		/**
		* Is the special key pressed
		* @param p_key : the special key we want to check
		* @return true if the special key is pressed, else false
		**/
		bool isSpecialKeyPressed(int p_key) const;

		/**
		* Press the specified special key
		* @param p_key : the special key to press
		**/
		void pressSpecialKey(int p_key);

		/**
		* Release the specified special key
		* @param p_key : the special key to release
		**/
		void releaseSpecialKey(int p_key);

		/**
		* Bind a special key to an action
		* @param p_action : the action to bind to
		* @param p_key : the special key to bind
		**/
		void bindActionToSpecialKey(int p_action, int p_key);
#pragma endregion
	};
}

#endif


