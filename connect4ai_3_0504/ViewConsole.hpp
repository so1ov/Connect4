#ifndef VIEWCONSOLE_HPP
#define VIEWCONSOLE_HPP

#include "View.hpp"

namespace Connect4
{
	class ViewConsole : public View
	{
	public:
		explicit ViewConsole(Game*);

		void refresh();
	};
}
#endif