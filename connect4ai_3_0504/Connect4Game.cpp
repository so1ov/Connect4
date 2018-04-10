#include "Connect4Game.hpp"

#include <iostream>

void Connect4Game::start()
{
	now_.turn = 0;
	this->gameLoop();
}

void Connect4Game::gameLoop()
{
	bool turnIsValid;
	while (!gameOver())
	{
		attachedView_->refresh();
		turnIsValid = false;
		while (turnIsValid == false)
		{
			turnIsValid = this->pushChip(players_[now_.turn % 2]->makeTurn(),
				players_[now_.turn % 2]->getChip());
		}
		now_.turn++;
	}
}

int Connect4Game::gameOver()
{
	return 0;
}

void initField(char**& _field, int _size, char _cell)
{
	_field = new char*[_size];
	for (int i = 0; i < _size; i++)
	{
		_field[i] = new char[_size];
		for (int j = 0; j < _size; j++)
		{
			_field[i][j] = _cell;
		}
	}
}

Connect4Game::Connect4Game(int _size, Connect4Player* _p1, Connect4Player* _p2)
	:	size_(_size)
{
	initField(field_, size_, EmptyCellCharacter);

	if (_p1->getChip() == _p2->getChip())
	{ 
		_p1->setChip(DefaultFirstPlayerCharacter);
		_p2->setChip(DefaultSecondPlayerCharacter);
	}

	players_[0] = _p1;
	players_[1] = _p2;

	players_[0]->attachGame(this);
	players_[1]->attachGame(this);

	this->attachView(new Connect4ViewConsole(this));
}

Connect4Game::Connect4Game(Connect4Player* _p1, Connect4Player* _p2)
	:	size_(DefaultSize)
{
	initField(field_, size_, EmptyCellCharacter);

	if (_p1->getChip() == _p2->getChip())
	{
		_p1->setChip(DefaultFirstPlayerCharacter);
		_p2->setChip(DefaultSecondPlayerCharacter);
	}

	players_[0] = _p1;
	players_[1] = _p2;

	players_[0]->attachGame(this);
	players_[1]->attachGame(this);

	this->attachView(new Connect4ViewConsole(this));
}



char** Connect4Game::getField()
{
	return field_;
}

int Connect4Game::getSize()
{
	return size_;
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
	for (int i = size_ - 1; i >= 0; i--)
	{
		if (field_[i][_column] == EmptyCellCharacter)
		{
			field_[i][_column] = _ch;
			return true;
		}
	}

	return false;
}
