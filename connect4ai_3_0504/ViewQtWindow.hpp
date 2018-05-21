#ifndef VIEWQTWINDOW_HPP
#define VIEWQTWINDOW_HPP

#include "View.hpp"
#include "Game.hpp"

namespace Connect4
{
	class ViewQtWindow : public View
	{
	public:
		explicit ViewQtWindow(Game*);

		void refresh();
	};
}
#endif