#include "Connect4ViewConsole.hpp"

#include "Connect4Game.hpp"

void Connect4ViewConsole::refresh()
{
	static char** field = attachedGame_->getField();
	static int rows = this->attachedGame_->getRows();
	static int columns = this->attachedGame_->getColumns();

	system("cls");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			std::cout << field[i][j];
		}
		std::cout << std::endl;
	}
	
	if (attachedGame_->getWinnerChip() != attachedGame_->getOptions().unknownWinner)
	{
		std::cout << "Player " << attachedGame_->getWinnerChip() << " wins!" << std::endl;
	}
}

Connect4ViewConsole::Connect4ViewConsole(Connect4Game* _attachedGame)
	: Connect4View(_attachedGame)
{

}