#ifndef View_HPP
#define View_HPP

#include <iostream>

namespace Connect4
{
	class Game;

	class View
	{
	public:
		void attachGame(Game* a);
		virtual void refresh() = 0;
		View(Game*);
	protected:
		Game* attachedGame_;
	};
}

#endif