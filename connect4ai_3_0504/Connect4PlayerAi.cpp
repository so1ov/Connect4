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

int Connect4PlayerAi::countOnDirection(int _x, int _y, int _dx, int _dy)
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
	int lastDecision;
	int lastDecisionMaxSequence;
	int bestDecision = 0;
	int columnToTurn;
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
		lastDecisionMaxSequence = 0;
		for (int i = 0; i < numberOfPairs; i++)
		{
			lastDecision = 0;
			for (int j = 0; j < pair; j++)
			{
				dx = oppositeDirections[i][j][0];
				dy = oppositeDirections[i][j][1];
				lastDecision += countOnDirection(column, row, dx, dy);
			}
			if (lastDecisionMaxSequence < lastDecision)
			{
				lastDecisionMaxSequence = lastDecision;
			}
		}
		if (lastDecisionMaxSequence >= bestDecision)
		{
			bestDecision = lastDecisionMaxSequence;
			columnToTurn = column;
		}
	}

	if (bestDecision + 1 == attachedGame_->getSize())
	{
		attachedGame_->win(this);
	}
	return columnToTurn;
}