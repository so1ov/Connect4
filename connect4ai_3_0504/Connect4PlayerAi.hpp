#ifndef CONNECT4PLAYERAI_HPP
#define CONNECT4PLAYERAI_HPP

#include "Connect4Player.hpp"

class Connect4PlayerAi : public Connect4Player
{
public:
	Connect4PlayerAi(char _ch);
private:
	int makeTurn();
};

#endif