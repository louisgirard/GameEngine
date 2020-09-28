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
		::std::vector<bool> _keyStatus;
		::std::map<int, unsigned char> _keyBinding;

		::std::map<int, bool> _specialKeyStatus;
		::std::map<int, int> _specialKeyBinding;

	public:

		KeyboardStatus();

		bool isPressed(unsigned char p_key) const;

		void press(unsigned char p_key);

		void release(unsigned char p_key);

		bool isSpecialKeyPressed(int p_key) const;

		void pressSpecialKey(int p_key);

		void releaseSpecialKey(int p_key);

		void bindActionToKey(int p_action, unsigned char p_key);

		void bindActionToSpecialKey(int p_action, int p_key);

		bool isPressed(int p_action) const;

	};
}

#endif


