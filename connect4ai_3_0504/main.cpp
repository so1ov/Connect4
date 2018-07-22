#include "Game.hpp"
#include "PlayerAi.hpp"

#include "windows.h"
#include <iostream>

int main()
{
	using namespace Connect4;
	Player* p1 = new PlayerAi('X');
	Player* p2 = new PlayerAi('O');
	(new Game(p1, p2))->start();
	system("pause");
}

