#ifndef CONNECT4PLAYERAI_HPP
#define CONNECT4PLAYERAI_HPP

#include "Connect4Player.hpp"

class Connect4PlayerAi : public Connect4Player
{
public:
	Connect4PlayerAi(char _ch);

private:
	int makeTurn();
	int decision();
	int findFreeRow(int column);
	int firstFreeColumn();

	int maxSequence(int _x, int _y);
	int maxSequenceForSpecifiedChip(char _chip, int _x, int _y);

	int maxPossibleSequence(int _x, int _y);
	int maxPossibleSequenceForSpecifiedChip(char _chip, int _x, int _y);

	int sequenceOnDirection(int _x, int _y, int _dx, int _dy);
	int sequenceOnDirectionForSpecifiedChip(char _chip, int _x, int _y, int _dx, int _dy);

	int possibleSequenceOnDirection(int _x, int _y, int _dx, int _dy);
	int possibleSequenceOnDirectionForSpecifiedChip(char _chip, int _x, int _y, int _dx, int _dy);
};

#endif