#ifndef PlayerAI_HPP
#define PlayerAI_HPP

#include "Player.hpp"

#include "Game.hpp"

namespace Connect4
{
	class PlayerAi : public Player
	{
	public:
		PlayerAi(char _ch);

	private:
		int makeTurn();
		int decision();
		int findFreeRow(int column);
		int firstFreeColumn();

		int maxSequence(C4GPoint);
		int maxSequenceForSpecifiedChip(char _chip, C4GPoint _point);

		int maxPossibleSequence(C4GPoint);
		int maxPossibleSequenceForSpecifiedChip(char _chip, C4GPoint _point);

		int sequenceOnDirection(C4GPoint _point, C4GPoint _direction);
		int sequenceOnDirectionForSpecifiedChip(char _chip, C4GPoint _point, C4GPoint _direction);

		int possibleSequenceOnDirection(C4GPoint, C4GPoint _direction);
		int possibleSequenceOnDirectionForSpecifiedChip(char _chip, C4GPoint _point, C4GPoint _direction);
	};
}

#endif