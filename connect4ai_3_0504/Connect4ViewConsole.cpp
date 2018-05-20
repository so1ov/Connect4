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
	
	auto condition = attachedGame_->getCurrentCondition();
	switch (condition.first)
	{
	case Connect4Game::GameCondition::InProcess:
		break;
	case Connect4Game::GameCondition::Draw:
		std::cout << "Draw!" << std::endl;
		break;
	case Connect4Game::GameCondition::Player1Wins:
	case Connect4Game::GameCondition::Player2Wins:
		std::cout << "Player " << condition.second << " wins!" << std::endl;
		break;
	}
}

Connect4ViewConsole::Connect4ViewConsole(Connect4Game* _attachedGame)
	: Connect4View(_attachedGame)
{

}