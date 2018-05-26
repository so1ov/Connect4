#ifndef Player_HPP
#define Player_HPP

namespace Connect4
{
	class Game;

	class Player
	{
	public:
		Player(char);
		char getChip();
		void setChip(char);
		virtual int makeTurn() = 0;
		void attachGame(Game*);
	protected:
		char chip_;
		Game* attachedGame_;
	};
}

#endif