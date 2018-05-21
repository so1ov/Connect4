#ifndef PLAYER_HPP
#define PLAYER_HPP

namespace Connect4
{
	class Game;

	class Player
	{
	public:
		explicit Player(const char _chip);

		char getChip();
		void setChip(char _chip);
		virtual int makeTurn() = 0;
		void attachGame(Game* _game);
	protected:
		char chip_;
		Game* attachedGame_;
	};
}
#endif