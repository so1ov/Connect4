#include "ViewConsole.hpp"

#include "Game.hpp"

void Connect4::ViewConsole::refresh()
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
	case Game::GameCondition::InProcess:
		break;
	case Game::GameCondition::Draw:
		std::cout << "Draw!" << std::endl;
		break;
	case Game::GameCondition::Player1Wins:
	case Game::GameCondition::Player2Wins:
		std::cout << "Player " << condition.second << " wins!" << std::endl;
		break;
	}
}

Connect4::ViewConsole::ViewConsole(Game* _attachedGame)
	: View(_attachedGame)
{

}