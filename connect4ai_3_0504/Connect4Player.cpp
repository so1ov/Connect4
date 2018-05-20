#include "Connect4Player.hpp"

Connect4Player::Connect4Player(const char _ch)
	:	chip_(_ch)
{

}

char Connect4Player::getChip()
{
	return chip_;
}

void Connect4Player::setChip(const char _ch)
{
	chip_ = _ch;
}

void Connect4Player::attachGame(Connect4Game* _attachedGame)
{
	attachedGame_ = _attachedGame;
}
