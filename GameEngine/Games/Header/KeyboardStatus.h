#ifndef _Games_KeyboardStatus_H
#define _Games_KeaboardStatus_H

#include <vector>
#include <iostream>

namespace Games {
	class KeyboardStatus
	{
	protected:
		::std::vector<bool> _keyStatus;

	public:

		KeyboardStatus();

		bool isPressed(unsigned char key) const;

		void press(unsigned char key);

		void release(unsigned char key);

	};
}

#endif


