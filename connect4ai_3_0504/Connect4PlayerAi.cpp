#include "Connect4PlayerAi.hpp"

#include "Connect4Game.hpp"

#include "windows.h"

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

static int numberOfPairs = sizeof(oppositeDirections) / sizeof(oppositeDirections[0]);
static int pairOfOppositeVectors = sizeof(oppositeDirections[0]) / sizeof(oppositeDirections[0][0]);

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

int Connect4PlayerAi::sequenceOnDirection(int _x, int _y, int _dx, int _dy)
{
	return sequenceOnDirectionForSpecifiedChip(this->chip_, _x, _y, _dx, _dy);
}

int Connect4PlayerAi::sequenceOnDirectionForSpecifiedChip(char _chip, int _x, int _y, int _dx, int _dy)
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
		if (_chip == field[currentY][currentX])
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

int Connect4PlayerAi::possibleSequenceOnDirection(int _x, int _y, int _dx, int _dy)
{
	return possibleSequenceOnDirectionForSpecifiedChip(this->chip_, _x, _y, _dx, _dy);
}

int Connect4PlayerAi::possibleSequenceOnDirectionForSpecifiedChip(char _chip, int _x, int _y, int _dx, int _dy)
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
		if (_chip == field[currentY][currentX]
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

int Connect4PlayerAi::maxSequence(int _x, int _y)
{
	return maxSequenceForSpecifiedChip(this->chip_, _x, _y);
}

int Connect4PlayerAi::maxSequenceForSpecifiedChip(char _chip, int _x, int _y)
{
	int currentSequence;
	int maxSequence = 0;
	int dx, dy;

	for (int thisPair = 0; thisPair < numberOfPairs; thisPair++)
	{
		currentSequence = 0;
		for (int thisVector = 0; thisVector < pairOfOppositeVectors; thisVector++)
		{
			dx = oppositeDirections[thisPair][thisVector][0];
			dy = oppositeDirections[thisPair][thisVector][1];
			currentSequence += sequenceOnDirectionForSpecifiedChip(_chip, _x, _y, dx, dy);
		}
		if (currentSequence > maxSequence)
		{
			maxSequence = currentSequence;
		}
	}

	return maxSequence;
}

int Connect4PlayerAi::maxPossibleSequence(int _x, int _y)
{
	return maxPossibleSequenceForSpecifiedChip(this->chip_, _x, _y);
}

int Connect4PlayerAi::maxPossibleSequenceForSpecifiedChip(char _chip, int _x, int _y)
{
	int currentPossibleSequence;
	int maxPossibleSequence = 0;
	int dx, dy;

	for (int thisPair = 0; thisPair < numberOfPairs; thisPair++)
	{
		currentPossibleSequence = 0;
		for (int thisVector = 0; thisVector < pairOfOppositeVectors; thisVector++)
		{
			dx = oppositeDirections[thisPair][thisVector][0];
			dy = oppositeDirections[thisPair][thisVector][1];
			currentPossibleSequence += possibleSequenceOnDirectionForSpecifiedChip(_chip, _x, _y, dx, dy);
		}
		if (currentPossibleSequence > maxPossibleSequence)
		{
			maxPossibleSequence = currentPossibleSequence;
		}
	}

	return maxPossibleSequence;
}

int Connect4PlayerAi::decision()
{
	static int columns = attachedGame_->getSize();

	int row;
	int currentColumnMaxSequence;
	int currentColumnMaxPossibleSequence;
	int bestSequence = 0;
	int bestSequenceColumn = -1;

	for (int column = 0; column < columns; column++)
	{
		row = findFreeRow(column);
		if (row == -1)
		{
			continue;
		}
		currentColumnMaxSequence = maxSequence(column, row);
		currentColumnMaxPossibleSequence = maxPossibleSequence(column, row);
		
		if (currentColumnMaxSequence >= bestSequence
			&&
			currentColumnMaxPossibleSequence + 1 >= attachedGame_->WinSequence)
		{
			bestSequence = currentColumnMaxSequence;
			bestSequenceColumn = column;
		}
	}

	if (bestSequence + 1 >= attachedGame_->WinSequence)
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


