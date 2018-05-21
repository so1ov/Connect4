#ifndef PLAYERKEYBOARD_HPP
#define PLAYERKEYBOARD_HPP

#include "Player.hpp"

namespace Connect4
{
	class PlayerKeyboard : public Player
	{
	public:
		explicit PlayerKeyboard(const char _ch);
	private:
		int makeTurn();

		enum KeyboardInputConstants
		{
			CharRepresentationOf0 = 49,
			CharRepresentationOf9 = 57,
		};
	};
}

#endif