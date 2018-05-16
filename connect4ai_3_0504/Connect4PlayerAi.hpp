#ifndef CONNECT4PLAYERAI_HPP
#define CONNECT4PLAYERAI_HPP

#include "Connect4Player.hpp"

#include "Connect4Game.hpp"

#include <stack>
#include <vector>

class Connect4PlayerAi : public Connect4Player
{
public:
	Connect4PlayerAi(char);

private:
	struct TemporarilyMoveInfo
	{
		char chip;
		int column;
		int decision;
	};
	std::stack<TemporarilyMoveInfo> analyzedBranch;

	int makeTurn();
	int findBestMove();
	int heuristicDecision(C4GPoint);

	int findFirstFreeRow(int);
	int findFirstBusyRow(int);
	int firstFreeColumn();

	int maxSequence(C4GPoint);
	int maxSequenceForSpecifiedChip(char, C4GPoint);

	int maxPossibleSequence(C4GPoint);
	int maxPossibleSequenceForSpecifiedChip(char, C4GPoint);

	int sequenceOnDirection(C4GPoint, C4GPoint);
	int sequenceOnDirectionForSpecifiedChip(char, C4GPoint, C4GPoint);

	int possibleSequenceOnDirection(C4GPoint, C4GPoint);
	int possibleSequenceOnDirectionForSpecifiedChip(char, C4GPoint, C4GPoint);
	
	void temporarilyMove(char, int, int);
	void temporarilyMove(char, int);
	void temporarilyMove(int);
	void undoTemporarilyMove();
};

#endif