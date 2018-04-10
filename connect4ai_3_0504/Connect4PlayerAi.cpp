#include "Connect4PlayerAi.hpp"

#include "Connect4Game.hpp"

#include "windows.h"

Connect4PlayerAi::Connect4PlayerAi(char _ch)
	: Connect4Player(_ch)
{

}

int Connect4PlayerAi::makeTurn()
{
	int decision = rand() % attachedGame_->getSize();
	Sleep(1000);
	return decision;
}
