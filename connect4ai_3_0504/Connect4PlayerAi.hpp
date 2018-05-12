#ifndef CONNECT4PLAYERAI_HPP
#define CONNECT4PLAYERAI_HPP

#include <stack>
#include <vector>

#include "Connect4Player.hpp"
#include "Connect4Util.hpp"

class Connect4PlayerAi : public Connect4Player
{
public:
	Connect4PlayerAi(char);

private:
	struct TemporarilyMoveInfo
	{
		char chip;
		int column;
	};
	std::stack<TemporarilyMoveInfo> analyzedBranch;
	int makeTurn();
	int decision();
	int findFreeRow(int);
	int firstFreeColumn();

	int maxSequence(C4GPoint);
	int maxSequenceForSpecifiedChip(char, C4GPoint);

	int maxPossibleSequence(C4GPoint);
	int maxPossibleSequenceForSpecifiedChip(char, C4GPoint);

	int sequenceOnDirection(C4GPoint, C4GPoint);
	int sequenceOnDirectionForSpecifiedChip(char, C4GPoint, C4GPoint);

	int possibleSequenceOnDirection(C4GPoint, C4GPoint);
	int possibleSequenceOnDirectionForSpecifiedChip(char, C4GPoint, C4GPoint);

	int findBusyRow(int);
	void temporarilyMove(char, int);
	void temporarilyMove(int);
	void undoTemporarilyMove();
};

#endif