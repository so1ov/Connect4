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
		updateCurrentCondition();
		attachedView_->refresh();
	} while (now_.condition == GameCondition::InProcess);
}

void Connect4Game::updateCurrentCondition()
{
	Connect4Player& lastPlayer = *( players_[now_.turn % 2] );
	int sequenceForLastPlayer = maxSequenceForSpecifiedChip(lastPlayer.getChip(), { now_.lastTurn.column, now_.lastTurn.row });
	if (sequenceForLastPlayer >= options_.winSequence)
	{
		if (now_.turn % 2 == 0)
		{
			now_.condition = GameCondition::Player1Wins;
			return;
		}
		else if (now_.turn % 2 == 1)
		{
			now_.condition = GameCondition::Player2Wins;
			return;
		}
		else
		{
			throw new std::exception("Not implemented >2 players support");
		}
	}
	if (now_.turn == options_.columns * options_.rows)
	{
		now_.condition = GameCondition::Draw;
	}
	else
	{
		now_.condition = GameCondition::InProcess;
	}
}

std::pair<Connect4Game::GameCondition, char> Connect4Game::getCurrentCondition()
{
	switch (now_.condition)
	{
	case GameCondition::InProcess:
	case GameCondition::Draw:
		return std::pair<Connect4Game::GameCondition, char>(now_.condition, 0);
		break;
	case GameCondition::Player1Wins:
		return std::pair<Connect4Game::GameCondition, char>(now_.condition, players_[0]->getChip());
		break;
	case GameCondition::Player2Wins:
		return std::pair<Connect4Game::GameCondition, char>(now_.condition, players_[1]->getChip());
		break;
	}
}

void Connect4Game::initField(char**& _field, const int _rows, const int _columns, const char _cell)
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

Connect4Game::Connect4Game(Connect4Player* _p1, Connect4Player* _p2, const int _rows = (int)DefaultOptions::Rows, const int _columns = (int)DefaultOptions::Columns)
{
	options_.rows = _rows;
	options_.columns = _columns;

	initField(field_, _rows, _columns, options_.emptyCellCharacter);

	if (_p1->getChip() == _p2->getChip()
		||
		_p1->getChip() == (int)DefaultOptions::UnknownWinner
		||
		_p2->getChip() == (int)DefaultOptions::UnknownWinner)
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

int Connect4Game::maxSequenceForSpecifiedChip(const char _chip, const Point _point)
{
	int currentSequence;
	int maxSequence = 0;
	C4GPoint direction;

	for (int thisPair = 0; thisPair < Connect4Game::numberOfPairs; thisPair++)
	{
		currentSequence = 1;
		for (int currentDirection = 0; currentDirection < Connect4Game::pairOfOppositeDirections; currentDirection++)
		{
			direction = Connect4Game::oppositeDirections[thisPair][currentDirection];
			currentSequence += sequenceOnDirectionForSpecifiedChip(_chip, _point, direction);
		}
		if (currentSequence > maxSequence)
		{
			maxSequence = currentSequence;
		}
	}

	return maxSequence;
}

int Connect4Game::sequenceOnDirectionForSpecifiedChip(const char _chip, const Point _point, const Point _direction)
{

	int currentX = _point.x + _direction.x;
	int currentY = _point.y + _direction.y;
	int sequence = 0;

	while (currentX < options_.columns && currentX >= 0
		&&
		currentY < options_.rows && currentY >= 0)
	{
		if (_chip == field_[currentY][currentX])
		{
			sequence++;
		}
		else
		{
			break;
		}

		currentX += _direction.x;
		currentY += _direction.y;
	}

	return sequence;
}

void Connect4Game::setCustomView(Connect4View* _view)
{
	this->attachView(_view);
}

void Connect4Game::setLastTurnCoord(const int _column, const int _row)
{
	now_.lastTurn.column = _column;
	now_.lastTurn.row = _row;
}

bool Connect4Game::pushChip(const int _column, const char _ch)
{
	for (int i = options_.rows - 1; i >= 0; i--)
	{
		if (field_[i][_column] == options_.emptyCellCharacter)
		{
			field_[i][_column] = _ch;
			setLastTurnCoord(_column, i);
			return true;
		}
	}

	return false;
}
