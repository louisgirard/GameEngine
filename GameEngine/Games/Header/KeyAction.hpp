#ifndef _Games_KeyAction_H
#define _Games_KeyAction_H

class KeyAction {
public:
	static const int QUIT = 0;
	static const int MAINACTION = 1;

	//Translation Movement Related
	static const int MOVEFRONT = 2;
	static const int MOVEBACK = 3;
	static const int MOVELEFT = 4;
	static const int MOVERIGHT = 5;
	static const int MOVEUP = 6;
	static const int MOVEDOWN= 7;

	//Rotation Movement Related
	static const int ROTATEUP = 8;
	static const int ROTATEDOWN = 9;
	static const int ROTATELEFT = 10;
	static const int ROTATERIGHT = 11;
	
	

};

#endif // !_Games_KeyAction_H