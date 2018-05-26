#ifndef ViewCONSOLE_HPP
#define ViewCONSOLE_HPP

#include "View.hpp"

namespace Connect4
{
	class ViewConsole : public View
	{
	public:
		void refresh();
		ViewConsole(Game*);
	};
}

#endif