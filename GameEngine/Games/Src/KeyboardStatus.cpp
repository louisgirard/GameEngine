#include <Games/Header/KeyboardStatus.h>


namespace Games {


	KeyboardStatus::KeyboardStatus(): _keyStatus(256, false)
	{}

	bool KeyboardStatus::isPressed(unsigned char key) const
	{
		return _keyStatus[key];
	}

	void KeyboardStatus::press(unsigned char key)
	{
		//Uncomment if you want to verify the value of a key
		//std::cout << "pressed " << (int)key << std::endl;
		_keyStatus[key] = true;
	}

	void KeyboardStatus::release(unsigned char key)
	{
		_keyStatus[key] = false;
	}
}
