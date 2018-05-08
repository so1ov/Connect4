#include "Connect4PlayerAi.hpp"

#include "Connect4Game.hpp"

#include "windows.h"
#include <exception>

Connect4PlayerAi::Connect4PlayerAi(char _ch)
	: Connect4Player(_ch)
{

}

int Connect4PlayerAi::makeTurn()
{
	return decision();
}

int Connect4PlayerAi::findFreeRow(int _column)
{
	static char** field = attachedGame_->getField();
	for (int i = attachedGame_->getSize()- 1; i >= 0; i--)
	{
		if (field[i][_column] == attachedGame_->Constants::EmptyCellCharacter)
		{
			return i;
		}
	}
	return -1;
}

int Connect4PlayerAi::firstFreeColumn()
{
	static char** field = this->attachedGame_->getField();
	static int size = this->attachedGame_->getSize();

	int row;
	for(int column = 0; column < size; column++)
	{
		row = findFreeRow(column);
		if (row != -1)
		{
			return column;
		}
	}

	return -1;
}

int Connect4PlayerAi::countMyChipsOnDirection(int _x, int _y, int _dx, int _dy)
{
	static char** field = this->attachedGame_->getField();
	static int size = this->attachedGame_->getSize();

	int currentX = _x + _dx;
	int currentY = _y + _dy;
	int sequence = 0;

	while (currentX < size && currentX >= 0
		&&
		currentY < size && currentY >= 0)
	{
		if (this->chip_ == field[currentY][currentX])
		{
			sequence++;
		}
		else
		{
			break;
		}

		currentX += _dx;
		currentY += _dy;
	}

	return sequence;
}

int Connect4PlayerAi::maxPossibleSequenceOnThisDirection(int _x, int _y, int _dx, int _dy)
{
	static char** field = this->attachedGame_->getField();
	static int size = this->attachedGame_->getSize();

	int currentX = _x + _dx;
	int currentY = _y + _dy;
	int sequence = 0;

	while (currentX < size && currentX >= 0
		&&
		currentY < size && currentY >= 0)
	{
		if (this->chip_ == field[currentY][currentX] 
			||
			attachedGame_->EmptyCellCharacter == field[currentY][currentX])
		{
			sequence++;
		}
		else
		{
			break;
		}

		currentX += _dx;
		currentY += _dy;
	}

	return sequence;
}

int Connect4PlayerAi::decision()
{
	static int columns = attachedGame_->getSize();
	static int oppositeDirections[][2][2] =
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

	int row;
	int dx, dy;
	int currentColumnCurrentSequence;
	int currentColumnMaxSequence;
	int currentColumnMaxPossibleSequence;
	int currentColumnCurrentPossibleSequence;
	int bestSequence = 0;
	int bestSequenceColumn = -1;
	int buffer;
	int numberOfPairs = sizeof(oppositeDirections) / sizeof(oppositeDirections[0]);
	int pair = sizeof(oppositeDirections[0]) / sizeof(oppositeDirections[0][0]);

	for (int column = 0; column < columns; column++)
	{
		row = findFreeRow(column);
		if (row == -1)
		{
			continue;
		}
		currentColumnMaxSequence = 0;
		currentColumnMaxPossibleSequence = 0;
		for (int thisPair = 0; thisPair < numberOfPairs; thisPair++)
		{
			currentColumnCurrentSequence = 0;
			currentColumnCurrentPossibleSequence = 0;
			for (int thisVector = 0; thisVector < pair; thisVector++)
			{
				dx = oppositeDirections[thisPair][thisVector][0];
				dy = oppositeDirections[thisPair][thisVector][1];
				currentColumnCurrentSequence += countMyChipsOnDirection(column, row, dx, dy);
				currentColumnCurrentPossibleSequence += maxPossibleSequenceOnThisDirection(column, row, dx, dy);
			}
			if (currentColumnMaxSequence < currentColumnCurrentSequence)
			{
				currentColumnMaxSequence = currentColumnCurrentSequence;
			}
			if (currentColumnMaxPossibleSequence < currentColumnCurrentPossibleSequence)
			{
				currentColumnMaxPossibleSequence = currentColumnCurrentPossibleSequence;
			}
		}
		if (currentColumnMaxSequence >= bestSequence
			&&
			currentColumnMaxPossibleSequence + 1 >= attachedGame_->WinSequence)
		{
			bestSequence = currentColumnMaxSequence;
			bestSequenceColumn = column;
		}
	}

	if (bestSequence + 1 == attachedGame_->WinSequence)
	{
		attachedGame_->win(this);
	}

	if (bestSequenceColumn != -1)
	{
		return bestSequenceColumn;
	}
	else
	{
		return firstFreeColumn();
	}
}