#include "Connect4PlayerKeyboard.hpp"

#include "Connect4Game.hpp"

#include "conio.h"
#include "windows.h"
#include <iostream>

Connect4PlayerKeyboard::Connect4PlayerKeyboard(const char _ch)
	: Connect4Player(_ch)
{

}

int Connect4PlayerKeyboard::makeTurn()
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