#include "Connect4Game.hpp"

#include "windows.h"
#include <iostream>

int main()
{
	Connect4Player* p1 = new Connect4PlayerAi('X');
	Connect4Player* p2 = new Connect4PlayerKeyboard('O');
	(new Connect4Game(p1, p2))->start();
	system("pause");
	std::cout << "Hello!" << std::endl;
}

