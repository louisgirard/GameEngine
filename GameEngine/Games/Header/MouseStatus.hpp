#pragma once
namespace Games {
	class MouseStatus
	{
	private:
		//Mouse position 
		int _x;
		int _y;

	public:

#pragma region GETTERS
		/**
		* Get the x position of the mouse
		* @return x position of the mouse
		**/
		int getX();
		/**
		* Get the y position of the mouse
		* @return y position of the mouse
		**/
		int getY();
#pragma endregion

#pragma region SETTERS
		/**
		* Set the x position of the mouse
		* @param p_x : x position of the mouse
		**/
		void setX(int p_x);
		/**
		* Set the y position of the mouse
		* @param p_y : y position of the mouse
		**/
		void setY(int p_y);
#pragma endregion
	};
}
