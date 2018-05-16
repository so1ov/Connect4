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
int Connect4Game::pairOfOppositeVectors = sizeof(oppositeDirections[0]) / sizeof(oppositeDirections[0][0]);

void Connect4Game::start()
{
	this->gameLoop();
}

bool Connect4Game::pointOnField(Connect4Game::Point _point)
{
	return _point.X >= 0 && _point.X < getColumns()
		&&
		_point.Y >= 0 && _point.Y < getRows();
}

int Connect4Game::maxSequenceOfSpecifiedChipOnThisStraight(Point _point, Point _direction, char _chip)
{
	C4GPoint straightBorder = _point;
	int currentSequence = 0;
	int maxSequence = -1;
	while (pointOnField(straightBorder))
	{
		straightBorder.X -= _direction.X;
		straightBorder.Y -= _direction.Y;
	}

	while (pointOnField(straightBorder))
	{
		if (field_[straightBorder.Y][straightBorder.X] == _chip)
		{
			currentSequence++;
		}
		else
		{
			if (currentSequence > maxSequence)
			{
				maxSequence = currentSequence;
			}
			currentSequence = 0;		
		}

		straightBorder.X += _direction.X;
		straightBorder.Y += _direction.Y;
	}
	return maxSequence;
}

bool Connect4Game::findWinSequenceOfSpecifiedChipOnAllStraightsThroughPoint(Point _point, char _chip)
{
	C4GPoint direction;
	int sequence;
	for (int thisPair = 0; thisPair < Connect4Game::numberOfPairs; thisPair++)
	{
		sequence = 0;
		for (int thisVector = 0; thisVector < Connect4Game::pairOfOppositeVectors; thisVector++)
		{
			direction = Connect4Game::oppositeDirections[thisPair][thisVector];
			sequence = maxSequenceOfSpecifiedChipOnThisStraight(_point, direction, _chip);
			if (sequence >= WinSequence)
			{
				return true;
			}
		}
	}

	return false;
}



void Connect4Game::calculateGameOver()
{
	C4GPoint diagonalPoint;
	int sequence;
	for (int i = 0, j = 0; i < getColumns() && j < getRows(); i++, j++)
	{
		diagonalPoint = { i, j };
		for (int player = 0; player < sizeof(players_) / sizeof(players_[0]); player++)
		{
			if (findWinSequenceOfSpecifiedChipOnAllStraightsThroughPoint(diagonalPoint, players_[player]->getChip()))
			{
				now_.winner = players_[player]->getChip();
				return;
			}
		}
	}
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
		this->calculateGameOver();
		attachedView_->refresh();
	} while (!gameOver());
}

bool Connect4Game::gameOver()
{
	if (now_.turn == options_.columns * options_.rows || now_.winner != DefaultOptions::UnknownWinner)
	{
		return true;
	}
	else
	{
		return false;
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

Connect4Game::Connect4Game(int _rows, int _columns, Connect4Player* _p1, Connect4Player* _p2)
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
	:	Connect4Game(DefaultOptions::Rows, DefaultOptions::Columns, _p1, _p2)
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
			return true;
		}
	}

	return false;
}





