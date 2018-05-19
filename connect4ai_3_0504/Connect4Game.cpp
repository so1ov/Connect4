#include "Connect4Game.hpp"

#include <iostream>
#include <string>

C4GPoint Connect4Game::oppositeDirections[][2] =
{
	{
		{ 1, 0 },{ -1, 0 }
	},
	{
		{ 0, 1 },{ 0, -1 }
	},
	{
		{ 1, 1 },{ -1, -1 }
	},
	{
		{ -1, 1 },{ 1, -1 }
	}
};

int Connect4Game::numberOfPairs = sizeof(oppositeDirections) / sizeof(oppositeDirections[0]);
int Connect4Game::pairOfOppositeDirections = sizeof(oppositeDirections[0]) / sizeof(oppositeDirections[0][0]);

void Connect4Game::start()
{
	this->gameLoop();
}

void Connect4Game::gameLoop()
{
	attachedView_->refresh();

	bool turnIsValid;
	do
	{
		now_.turn++;
		turnIsValid = false;
		while (turnIsValid == false)
		{
			turnIsValid = this->pushChip(players_[now_.turn % 2]->makeTurn(),
				players_[now_.turn % 2]->getChip());
		}
		attachedView_->refresh();
	} while (!gameOver());
}

int Connect4Game::gameOver()
{
	if (now_.turn == options_.columns * options_.rows || now_.winner != (char)DefaultOptions::UnknownWinner)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void initField(char**& _field, int _rows, int _columns, char _cell)
{
	_field = new char*[_rows];
	for (int i = 0; i < _rows; i++)
	{
		_field[i] = new char[_columns];
		for (int j = 0; j < _columns; j++)
		{
			_field[i][j] = _cell;
		}
	}
}

Connect4Game::Connect4Game(Connect4Player* _p1, Connect4Player* _p2, int _rows = (int)DefaultOptions::Rows, int _columns = (int)DefaultOptions::Columns)
{
	options_.rows = _rows;
	options_.columns = _columns;

	initField(field_, _rows, _columns, options_.emptyCellCharacter);

	if (_p1->getChip() == _p2->getChip())
	{ 
		_p1->setChip(options_.firstPlayerCharacter);
		_p2->setChip(options_.secondPlayerCharacter);
	}

	players_[0] = _p1;
	players_[1] = _p2;

	players_[0]->attachGame(this);
	players_[1]->attachGame(this);

	this->attachView(new Connect4ViewConsole(this));
}

Connect4Game::Connect4Game(Connect4Player* _p1, Connect4Player* _p2)
	:	Connect4Game(_p1, _p2, (int)DefaultOptions::Rows, (int)DefaultOptions::Columns)
{
	
}

void Connect4Game::win(Connect4Player* _player)
{
	now_.winner = _player->getChip();
}

char Connect4Game::getWinnerChip()
{
	return now_.winner;
}

char** Connect4Game::getField()
{
	return field_;
}

int Connect4Game::getColumns()
{
	return options_.columns;
}

int Connect4Game::getRows()
{
	return options_.rows;
}

Connect4Game::GameOptions Connect4Game::getOptions()
{
	return options_;
}

void Connect4Game::attachView(Connect4View* _view)
{
	this->attachedView_ = _view;
}

void Connect4Game::setCustomView(Connect4View* _view)
{
	this->attachView(_view);
}

bool Connect4Game::pushChip(int _column, char _ch)
{
	for (int i = options_.rows - 1; i >= 0; i--)
	{
		if (field_[i][_column] == options_.emptyCellCharacter)
		{
			field_[i][_column] = _ch;
			now_.lastTurn.column_ = _column;
			now_.lastTurn.row_ = i;
			return true;
		}
	}

	return false;
}
