#include "Game.hpp"

#include <iostream>
#include <string>

Connect4::C4GPoint Connect4::Game::oppositeDirections[][2] =
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

int Connect4::Game::numberOfPairs = sizeof(oppositeDirections) / sizeof(oppositeDirections[0]);
int Connect4::Game::pairOfOppositeDirections = sizeof(oppositeDirections[0]) / sizeof(oppositeDirections[0][0]);

void Connect4::Game::start()
{
	this->gameLoop();
}

void Connect4::Game::gameLoop()
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

void Connect4::Game::updateCurrentCondition()
{
	Player& lastPlayer = *( players_[now_.turn % 2] );
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

std::pair<Connect4::Game::GameCondition, char> Connect4::Game::getCurrentCondition()
{
	switch (now_.condition)
	{
	case GameCondition::InProcess:
	case GameCondition::Draw:
		return std::pair<Game::GameCondition, char>(now_.condition, 0);
		break;
	case GameCondition::Player1Wins:
		return std::pair<Game::GameCondition, char>(now_.condition, players_[0]->getChip());
		break;
	case GameCondition::Player2Wins:
		return std::pair<Game::GameCondition, char>(now_.condition, players_[1]->getChip());
		break;
	}
	return std::pair<Game::GameCondition, char>(now_.condition, 0);
}

void Connect4::Game::initField(char**& _field, int _rows, int _columns, char _cell)
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

Connect4::Game::Game(Player* _p1, Player* _p2, int _rows, int _columns)
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

	this->attachView(new ViewConsole(this));
}

char** Connect4::Game::getField()
{
	return field_;
}

int Connect4::Game::getColumns()
{
	return options_.columns;
}

int Connect4::Game::getRows()
{
	return options_.rows;
}

Connect4::Game::GameOptions Connect4::Game::getOptions()
{
	return options_;
}

void Connect4::Game::attachView(View* _view)
{
	this->attachedView_ = _view;
}

int Connect4::Game::maxSequenceForSpecifiedChip(char _chip, Point _point)
{
	int currentSequence;
	int maxSequence = 0;
	C4GPoint direction;

	for (int thisPair = 0; thisPair < Game::numberOfPairs; thisPair++)
	{
		currentSequence = 1;
		for (int currentDirection = 0; currentDirection < Game::pairOfOppositeDirections; currentDirection++)
		{
			direction = Game::oppositeDirections[thisPair][currentDirection];
			currentSequence += sequenceOnDirectionForSpecifiedChip(_chip, _point, direction);
		}
		if (currentSequence > maxSequence)
		{
			maxSequence = currentSequence;
		}
	}

	return maxSequence;
}

int Connect4::Game::sequenceOnDirectionForSpecifiedChip(char _chip, Point _point, Point _direction)
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

void Connect4::Game::setCustomView(View* _view)
{
	this->attachView(_view);
}

bool Connect4::Game::pushChip(int _column, char _ch)
{
	for (int i = options_.rows - 1; i >= 0; i--)
	{
		if (field_[i][_column] == options_.emptyCellCharacter)
		{
			field_[i][_column] = _ch;
			now_.lastTurn.column = _column;
			now_.lastTurn.row = i;
			return true;
		}
	}

	return false;
}
