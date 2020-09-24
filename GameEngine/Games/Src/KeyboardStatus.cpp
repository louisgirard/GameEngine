#include <Games/Header/KeyboardStatus.h>


namespace Games {


	KeyboardStatus::KeyboardStatus(): _keyStatus(256, false)
	{}

	bool KeyboardStatus::isPressed(unsigned char key) const
	{
		return _keyStatus[key];
	}

	void KeyboardStatus::press(unsigned char p_key)
	{
		//Uncomment if you want to verify the value of a key
		//std::cout << "pressed " << (int)key << std::endl;
		_keyStatus[p_key] = true;
	}

	void KeyboardStatus::release(unsigned char p_key)
	{
		_keyStatus[p_key] = false;
	}

	void KeyboardStatus::bindActionToKey(int p_action, unsigned char p_key) {
		_keyBinding.insert(std::pair<int, unsigned char>(p_action, p_key));
	}

	bool KeyboardStatus::isPressed(int p_action) const {

		std::map<int, unsigned char>::const_iterator it;

		it = _keyBinding.find(p_action);
		if (it != _keyBinding.end()) {
			return _keyStatus[it->second];
		}
		
		return false;
	}
}
