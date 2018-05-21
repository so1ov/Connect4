#include "PlayerAi.hpp"

#include "Game.hpp"

#include "windows.h"

Connect4::PlayerAi::PlayerAi(const char _ch)
	: Player(_ch)
{

}

int Connect4::PlayerAi::makeTurn()
{
	return decision();
}

int Connect4::PlayerAi::findFreeRow(const int _column)
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

int Connect4::PlayerAi::firstFreeColumn()
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

int Connect4::PlayerAi::sequenceOnDirection(const C4GPoint _point, const C4GPoint _direction)
{
	return sequenceOnDirectionForSpecifiedChip(this->chip_, _point, _direction);
}

int Connect4::PlayerAi::sequenceOnDirectionForSpecifiedChip(const char _chip, const C4GPoint _point, const C4GPoint _direction)
{
	static char** field = this->attachedGame_->getField();
	static int rows = this->attachedGame_->getRows();
	static int columns = this->attachedGame_->getColumns();

	int currentX = _point.x + _direction.x;
	int currentY = _point.y + _direction.y;
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

		currentX += _direction.x;
		currentY += _direction.y;
	}

	return sequence;
}

int Connect4::PlayerAi::possibleSequenceOnDirection(const C4GPoint _point, const C4GPoint _direction)
{
	return possibleSequenceOnDirectionForSpecifiedChip(this->chip_, _point, _direction);
}

int Connect4::PlayerAi::possibleSequenceOnDirectionForSpecifiedChip(const char _chip, const C4GPoint _point, const C4GPoint _direction)
{
	static char** field = this->attachedGame_->getField();
	static int rows = this->attachedGame_->getRows();
	static int columns = this->attachedGame_->getColumns();

	int currentX = _point.x + _direction.x;
	int currentY = _point.y + _direction.y;
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

		currentX += _direction.x;
		currentY += _direction.y;
	}

	return sequence;
}

int Connect4::PlayerAi::maxSequence(const C4GPoint _point)
{
	return maxSequenceForSpecifiedChip(this->chip_, _point);
}

int Connect4::PlayerAi::maxSequenceForSpecifiedChip(const char _chip, const C4GPoint _point)
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

int Connect4::PlayerAi::maxPossibleSequence(const C4GPoint _point)
{
	return maxPossibleSequenceForSpecifiedChip(this->chip_, _point);
}

int Connect4::PlayerAi::maxPossibleSequenceForSpecifiedChip(const char _chip, const C4GPoint _point)
{
	int currentPossibleSequence;
	int maxPossibleSequence = 0;
	C4GPoint direction;

	for (int thisPair = 0; thisPair < Game::numberOfPairs; thisPair++)
	{
		currentPossibleSequence = 0;
		for (int currentDirection = 0; currentDirection < Game::pairOfOppositeDirections; currentDirection++)
		{
			direction = Game::oppositeDirections[thisPair][currentDirection];
			currentPossibleSequence += possibleSequenceOnDirectionForSpecifiedChip(_chip, _point, direction);
		}
		if (currentPossibleSequence > maxPossibleSequence)
		{
			maxPossibleSequence = currentPossibleSequence;
		}
	}

	return maxPossibleSequence;
}

int Connect4::PlayerAi::decision()
{
	static int columns = attachedGame_->getColumns();

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
		currentColumnMaxSequence = maxSequence({ column, row });
		currentColumnMaxPossibleSequence = maxPossibleSequence({ column, row });
		
		if (currentColumnMaxSequence >= bestSequence
			&&
			currentColumnMaxPossibleSequence + 1 >= attachedGame_->getOptions().winSequence)
		{
			bestSequence = currentColumnMaxSequence;
			bestSequenceColumn = column;
		}
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


