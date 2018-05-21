#include "View.hpp"
#include "Game.hpp"

#include "windows.h"

#include <iostream>

void Connect4::View::attachGame(Connect4::Game* _game)
{
	attachedGame_ = _game;
}

Connect4::View::View(Connect4::Game* _attachedGame)
	: attachedGame_(_attachedGame)
{

}