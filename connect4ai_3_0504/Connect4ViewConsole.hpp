#ifndef CONNECT4VIEWCONSOLE_HPP
#define CONNECT4VIEWCONSOLE_HPP

#include "Connect4View.hpp"

class Connect4ViewConsole : public Connect4View
{
public:
	explicit Connect4ViewConsole(Connect4Game*);

	void refresh();	
};

#endif