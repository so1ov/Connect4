#ifndef VIEW_HPP
#define VIEW_HPP

#include <iostream>

namespace Connect4
{
	class Game;
	class View
	{
	public:
		explicit View(Game*);

		void attachGame(Game* a);
		virtual void refresh() = 0;
	protected:
		Game* attachedGame_;
	};
}

#endif