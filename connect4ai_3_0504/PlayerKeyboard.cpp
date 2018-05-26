#include "PlayerKeyboard.hpp"

#include "Game.hpp"

#include "conio.h"
#include "windows.h"
#include <iostream>

Connect4::PlayerKeyboard::PlayerKeyboard(char _ch)
	: Player(_ch)
{

}

int Connect4::PlayerKeyboard::makeTurn()
{
	int decision = -1;

	while (decision < 0 || decision > attachedGame_->getColumns())
	{
		std::cout << "Your turn:";
		std::cin >> decision;
		std::cin.clear();
		std::cout.clear();
		std::cout << '\r';
	}
	
	return decision;
}