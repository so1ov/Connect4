#ifndef CONNECT4PLAYERKEYBOARD_HPP
#define CONNECT4PLAYERKEYBOARD_HPP

#include "Connect4Player.hpp"

class Connect4PlayerKeyboard : public Connect4Player
{
public:
	Connect4PlayerKeyboard(char _ch);
private:
	int makeTurn();

	enum KeyboardInputConstants
	{
		CharRepresentationOf0 = 49,
		CharRepresentationOf9 = 57,
	};
};

#endif