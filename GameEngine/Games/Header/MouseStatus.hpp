#pragma once
namespace Games {
	class MouseStatus
	{
	private:
		int _x;
		int _y;
	public:
		int getX();
		int getY();
		void setX(int p_x);
		void setY(int p_y);
	};
}
