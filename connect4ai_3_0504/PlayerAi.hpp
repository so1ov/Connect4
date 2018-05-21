#ifndef PLAYERAI_HPP
#define PLAYERAI_HPP

#include "Player.hpp"

#include "Game.hpp"

namespace Connect4
{
	class PlayerAi : public Player
	{
	public:
		explicit PlayerAi(const char _ch);

	private:
		int makeTurn();
		int decision();
		int findFreeRow(const int _column);
		int firstFreeColumn();

		int maxSequence(const C4GPoint _point);
		int maxSequenceForSpecifiedChip(const char _chip, const C4GPoint _point);

		int maxPossibleSequence(const C4GPoint _point);
		int maxPossibleSequenceForSpecifiedChip(const char _chip, const C4GPoint _point);

		int sequenceOnDirection(const C4GPoint _point, const C4GPoint _direction);
		int sequenceOnDirectionForSpecifiedChip(const char _chip, const C4GPoint _point, const C4GPoint _direction);

		int possibleSequenceOnDirection(const C4GPoint _point, const C4GPoint _direction);
		int possibleSequenceOnDirectionForSpecifiedChip(const char _chip, const C4GPoint _point, const C4GPoint _direction);
	};
}

#endif