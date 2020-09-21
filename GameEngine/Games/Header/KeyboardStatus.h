#ifndef _Games_KeyboardStatus_H
#define _Games_KeaboardStatus_H

#include <vector>

namespace Games {
	class KeyboardStatus
	{
	protected:
		::std::vector<bool> _keyStatus;

	public:

		KeyboardStatus()
			: _keyStatus(256, false)
		{}

		bool isPressed(unsigned char key) const
		{
			return _keyStatus[key];
		}

		void press(unsigned char key)
		{
			_keyStatus[key] = true;
		}

		void release(unsigned char key)
		{
			_keyStatus[key] = false;
		}

	};
}

#endif


