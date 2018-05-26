#ifndef PlayerKEYBOARD_HPP
#define PlayerKEYBOARD_HPP

#include "Player.hpp"

namespace Connect4
{
	class PlayerKeyboard : public Player
	{
	public:
		PlayerKeyboard(char _ch);
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