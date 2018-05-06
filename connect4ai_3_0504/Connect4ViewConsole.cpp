#include "Connect4ViewConsole.hpp"

#include "Connect4Game.hpp"

void Connect4ViewConsole::refresh()
{
	static char** field = attachedGame_->getField();
	static int size = attachedGame_->getSize();
	system("cls");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			std::cout << field[i][j];
		}
		std::cout << std::endl;
	}
	
	if (attachedGame_->getWinnerChip() != attachedGame_->UnknownWinner)
	{
		std::cout << "Player " << attachedGame_->getWinnerChip() << " wins!" << std::endl;
	}
}

Connect4ViewConsole::Connect4ViewConsole(Connect4Game* _attachedGame)
	: Connect4View(_attachedGame)
{

}