#include "View.hpp"

#include "Game.hpp"

void Connect4::View::attachGame(Game* _game)
{
	attachedGame_ = _game;
}

Connect4::View::View(Game* _attachedGame)
	: attachedGame_(_attachedGame)
{

}