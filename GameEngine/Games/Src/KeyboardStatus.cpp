#include <Games/Header/KeyboardStatus.hpp>

namespace Games {

	KeyboardStatus::KeyboardStatus(): _keyStatus(256, false)
	{
	}

	bool KeyboardStatus::isPressed(unsigned char key) const
	{
		return _keyStatus[key];
	}

	void KeyboardStatus::press(unsigned char p_key)
	{
		//Uncomment if you want to verify the value of a key
		//std::cout << "pressed " << (int)p_key << std::endl;
		_keyStatus[p_key] = true;
	}

	void KeyboardStatus::release(unsigned char p_key)
	{
		_keyStatus[p_key] = false;
	}

	void KeyboardStatus::bindActionToKey(int p_action, unsigned char p_key) {
		_specialKeyBinding.erase(p_action);
		_keyBinding[p_action]  = p_key;
	}

	bool KeyboardStatus::isSpecialKeyPressed(int p_key) const
	{
		std::map<int, bool>::const_iterator it;
		it = _specialKeyStatus.find(p_key);
		if (it != _specialKeyStatus.end()) {
			return it->second;
		}
		return false;
	}

	void KeyboardStatus::pressSpecialKey(int p_key)
	{
		//Uncomment if you want to verify the value of a key
		//std::cout << "pressed " << p_key << std::endl;
		_specialKeyStatus[p_key] = true;
	}

	void KeyboardStatus::releaseSpecialKey(int p_key)
	{
		//std::cout << "released " << p_key << std::endl;
		_specialKeyStatus[p_key] = false; 
	}

	void KeyboardStatus::bindActionToSpecialKey(int p_action, int p_key) {
		
		_keyBinding.erase(p_action);
		_specialKeyBinding[p_action] = p_key;

	}

	bool KeyboardStatus::isPressed(int p_action) const {

		std::map<int, unsigned char>::const_iterator it;

		it = _keyBinding.find(p_action);
		if (it != _keyBinding.end()) {
			return _keyStatus[it->second];
		}

		std::map<int, int>::const_iterator _secondit;
		_secondit = _specialKeyBinding.find(p_action);
		if (_secondit != _specialKeyBinding.end()) {
			return isSpecialKeyPressed(_secondit->second);
		}
		
		return false;
	}
}
