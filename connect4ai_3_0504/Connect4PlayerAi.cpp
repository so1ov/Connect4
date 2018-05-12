#include "Connect4PlayerAi.hpp"

#include "Connect4Game.hpp"
#include "Connect4Util.hpp"

#include "windows.h"

static C4GPoint oppositeDirections[][2] =
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
	for (int i = attachedGame_->getRows()- 1; i >= 0; i--)
	{
		if (field[i][_column] == attachedGame_->getOptions().emptyCellCharacter)
		{
			return i;
		}
	}
	return -1;
}

int Connect4PlayerAi::firstFreeColumn()
{
	static char** field = this->attachedGame_->getField();
	static int columns = this->attachedGame_->getColumns();

	int row;
	for(int column = 0; column < columns; column++)
	{
		row = findFreeRow(column);
		if (row != -1)
		{
			return column;
		}
	}

	return -1;
}

int Connect4PlayerAi::sequenceOnDirection(C4GPoint _point, C4GPoint _direction)
{
	return sequenceOnDirectionForSpecifiedChip(this->chip_, _point, _direction);
}

int Connect4PlayerAi::sequenceOnDirectionForSpecifiedChip(char _chip, C4GPoint _point, C4GPoint _direction)
{
	static char** field = this->attachedGame_->getField();
	static int rows = this->attachedGame_->getRows();
	static int columns = this->attachedGame_->getColumns();

	int currentX = _point.X + _direction.X;
	int currentY = _point.Y + _direction.Y;
	int sequence = 0;

	while (currentX < columns && currentX >= 0
		&&
		currentY < rows && currentY >= 0)
	{
		if (_chip == field[currentY][currentX])
		{
			sequence++;
		}
		else
		{
			break;
		}

		currentX += _direction.X;
		currentY += _direction.Y;
	}

	return sequence;
}

int Connect4PlayerAi::possibleSequenceOnDirection(C4GPoint _point, C4GPoint _direction)
{
	return possibleSequenceOnDirectionForSpecifiedChip(this->chip_, _point, _direction);
}

int Connect4PlayerAi::possibleSequenceOnDirectionForSpecifiedChip(char _chip, C4GPoint _point, C4GPoint _direction)
{
	static char** field = this->attachedGame_->getField();
	static int rows = this->attachedGame_->getRows();
	static int columns = this->attachedGame_->getColumns();

	int currentX = _point.X + _direction.X;
	int currentY = _point.Y + _direction.Y;
	int sequence = 0;

	while (currentX < columns && currentX >= 0
		&&
		currentY < rows && currentY >= 0)
	{
		if (_chip == field[currentY][currentX]
			||
			attachedGame_->getOptions().emptyCellCharacter == field[currentY][currentX])
		{
			sequence++;
		}
		else
		{
			break;
		}

		currentX += _direction.X;
		currentY += _direction.Y;
	}

	return sequence;
}

int Connect4PlayerAi::findBusyRow(int _column)
{
	static char** field = attachedGame_->getField();
	for (int i = attachedGame_->getRows() - 1; i > 0; i--)
	{
		if (field[i][_column] == attachedGame_->getOptions().emptyCellCharacter)
		{
			return i - 1;
		}
	}
	return -1;
}

void Connect4PlayerAi::temporarilyMove(char _chip, int _column)
{
	static char** field = attachedGame_->getField();
	int row = findBusyRow(_column);
	field[row][_column] = _chip;

	analyzedBranch.push(TemporarilyMoveInfo{ _chip, _column });
}

void Connect4PlayerAi::temporarilyMove(int _column)
{
	temporarilyMove(this->chip_, _column);
}

void Connect4PlayerAi::undoTemporarilyMove()
{
	analyzedBranch.pop();
}

int Connect4PlayerAi::maxSequence(C4GPoint _point)
{
	return maxSequenceForSpecifiedChip(this->chip_, _point);
}

int Connect4PlayerAi::maxSequenceForSpecifiedChip(char _chip, C4GPoint _point)
{
	int currentSequence;
	int maxSequence = 0;
	C4GPoint direction;

	for (int thisPair = 0; thisPair < numberOfPairs; thisPair++)
	{
		currentSequence = 0;
		for (int thisVector = 0; thisVector < pairOfOppositeVectors; thisVector++)
		{
			direction = oppositeDirections[thisPair][thisVector];
			currentSequence += sequenceOnDirectionForSpecifiedChip(_chip, _point, direction);
		}
		if (currentSequence > maxSequence)
		{
			maxSequence = currentSequence;
		}
	}

	return maxSequence;
}

int Connect4PlayerAi::maxPossibleSequence(C4GPoint _point)
{
	return maxPossibleSequenceForSpecifiedChip(this->chip_, _point);
}

int Connect4PlayerAi::maxPossibleSequenceForSpecifiedChip(char _chip, C4GPoint _point)
{
	int currentPossibleSequence;
	int maxPossibleSequence = 0;
	C4GPoint direction;

	for (int thisPair = 0; thisPair < numberOfPairs; thisPair++)
	{
		currentPossibleSequence = 0;
		for (int thisVector = 0; thisVector < pairOfOppositeVectors; thisVector++)
		{
			direction = oppositeDirections[thisPair][thisVector];
			currentPossibleSequence += possibleSequenceOnDirectionForSpecifiedChip(_chip, _point, direction);
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
	static int columns = attachedGame_->getColumns();

	int row;
	C4GPoint pointToAnalyzeMove;
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

		pointToAnalyzeMove = { column, row };
		currentColumnMaxSequence = maxSequence(pointToAnalyzeMove);
		currentColumnMaxPossibleSequence = maxPossibleSequence(pointToAnalyzeMove);
		
		if (currentColumnMaxSequence >= bestSequence
			&&
			currentColumnMaxPossibleSequence + 1 >= attachedGame_->getOptions().winSequence)
		{
			bestSequence = currentColumnMaxSequence;
			bestSequenceColumn = column;
		}
	}

	if (bestSequence + 1 >= attachedGame_->getOptions().winSequence)
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


