#include "Connect4View.hpp"
#include "Connect4Game.hpp"

#include "windows.h"

#include <iostream>

void Connect4View::attachGame(Connect4Game* _game)
{
	attachedGame_ = _game;
}

Connect4View::Connect4View(Connect4Game* _attachedGame)
	: attachedGame_(_attachedGame)
{
	attachedGame_ = _attachedGame;
}