#ifndef CONNECT4VIEW_HPP
#define CONNECT4VIEW_HPP

#include <iostream>

class Connect4Game;

class Connect4View
{
public:
	explicit Connect4View(Connect4Game*);

	void attachGame(Connect4Game* a);
	virtual void refresh() = 0;
protected:
	Connect4Game* attachedGame_;
};

#endif