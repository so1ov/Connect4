#ifndef CONNECT4PLAYERAI_HPP
#define CONNECT4PLAYERAI_HPP

#include "Connect4Player.hpp"

class Connect4PlayerAi : public Connect4Player
{
public:
	Connect4PlayerAi(char _ch);
private:
	int makeTurn();
	int decision();
	int countOnDirection(int, int, int, int);
	int findFreeRow(int);
};

#endif