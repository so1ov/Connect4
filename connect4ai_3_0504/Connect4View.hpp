#ifndef CONNECT4VIEW_HPP
#define CONNECT4VIEW_HPP

#include <iostream>

class Connect4Game;

class Connect4View
{
public:
	void attachGame(Connect4Game* a);
	virtual void refresh() = 0;
	Connect4View(Connect4Game*);
protected:
	Connect4Game* attachedGame_;
};

#endif