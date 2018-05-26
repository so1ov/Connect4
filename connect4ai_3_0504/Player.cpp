#include "Player.hpp"

#include "Game.hpp"

Connect4::Player::Player(char _ch)
	:	chip_(_ch)
{

}

char Connect4::Player::getChip()
{
	return chip_;
}

void Connect4::Player::setChip(char _ch)
{
	chip_ = _ch;
}

void Connect4::Player::attachGame(Game* _attachedGame)
{
	attachedGame_ = _attachedGame;
}
