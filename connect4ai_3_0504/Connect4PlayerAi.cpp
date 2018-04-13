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

int Connect4PlayerAi::decision()
{
	static char** field = attachedGame_->getField();
	static int oppositeDirections[][2][2] =
	{
		{ 
			{ 1, 0 }, {-1, 0} 
		},
		{ 
			{ 0, 1 }, {0, -1} 
		},
		{ 
			{ 1, 1 }, {-1, -1} 
		},
		{ 
			{-1, 1}, {1, -1} 
		}
	};

	int columns = attachedGame_->getSize();
	int row;
	int straights = sizeof(oppositeDirections) / sizeof(oppositeDirections[0]);
	int forwardAndBackward = sizeof(oppositeDirections[0]) / sizeof(oppositeDirections[0][0]);
	int maxSequenceTotal = 0;
	int numberOfColumnWithMaxSequence = 0;
	int maxSequenceOfChipsThroughThisCell = 0;
	int currentSequenceOfChipsThroughThisCell = 0;
	int sequenceBuff;
	for (int i = 0; i < columns; i++)
	{
		row = findFreeRow(i);
		if (row == -1)
		{
			continue;
		}
		for (int j = 0; j < straights; j++)
		{
			currentSequenceOfChipsThroughThisCell = 0;

			for (int k = 0; k < forwardAndBackward; k++)
			{
				sequenceBuff = 1;
				if (i + oppositeDirections[j][k][0] * sequenceBuff < 0 ||
					i + oppositeDirections[j][k][0] * sequenceBuff >= attachedGame_->getSize() ||
					row + oppositeDirections[j][k][1] * sequenceBuff < 0 ||
					row + oppositeDirections[j][k][1] * sequenceBuff >= attachedGame_->getSize() ||
					i + oppositeDirections[j][k][0] * sequenceBuff - 1 < 0 ||
					i + oppositeDirections[j][k][0] * sequenceBuff + 1 >= attachedGame_->getSize() ||
					row + oppositeDirections[j][k][1] * sequenceBuff - 1 < 0 ||
					row + oppositeDirections[j][k][1] * sequenceBuff + 1 >= attachedGame_->getSize())
				{
					continue;
				}
					while (field[i + oppositeDirections[j][k][0] * sequenceBuff]
					[row + oppositeDirections[j][k][1] * sequenceBuff]
					==
					this->chip_)
					{
						sequenceBuff++;
					}
				
				currentSequenceOfChipsThroughThisCell += sequenceBuff;				
			}
			currentSequenceOfChipsThroughThisCell -= 1;

			if (currentSequenceOfChipsThroughThisCell > maxSequenceOfChipsThroughThisCell)
			{
				maxSequenceOfChipsThroughThisCell = currentSequenceOfChipsThroughThisCell;
			}
		}

		if (maxSequenceOfChipsThroughThisCell > maxSequenceTotal)
		{
			maxSequenceTotal = maxSequenceOfChipsThroughThisCell;
			numberOfColumnWithMaxSequence = i;
		}
	}
	
	return numberOfColumnWithMaxSequence;
}
