#include <Games/Header/MouseStatus.hpp>

namespace Games {
	int MouseStatus::getX()
	{
		return _x;
	}
	int MouseStatus::getY()
	{
		return _y;
	}
	void MouseStatus::setX(int p_x)
	{
		_x = p_x;
	}
	void MouseStatus::setY(int p_y)
	{
		_y = p_y;
	}
}