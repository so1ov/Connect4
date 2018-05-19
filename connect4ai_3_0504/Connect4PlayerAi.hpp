#ifndef CONNECT4PLAYERAI_HPP
#define CONNECT4PLAYERAI_HPP

#include "Connect4Player.hpp"

#include "Connect4Game.hpp"

class Connect4PlayerAi : public Connect4Player
{
public:
	Connect4PlayerAi(char _ch);

private:
	int makeTurn();
	int decision();
	int findFreeRow(int column);
	int firstFreeColumn();

	int maxSequence(C4GPoint);
	int maxSequenceForSpecifiedChip(char _chip, C4GPoint _point);

	int maxPossibleSequence(C4GPoint);
	int maxPossibleSequenceForSpecifiedChip(char _chip, C4GPoint _point);

	int sequenceOnDirection(C4GPoint, C4GPoint _direction);
	int sequenceOnDirectionForSpecifiedChip(char _chip, C4GPoint _point, C4GPoint _direction);

	int possibleSequenceOnDirection(C4GPoint, C4GPoint _direction);
	int possibleSequenceOnDirectionForSpecifiedChip(char _chip, C4GPoint _point, C4GPoint _direction);
};

#endif