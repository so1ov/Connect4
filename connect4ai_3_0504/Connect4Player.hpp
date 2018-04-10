#ifndef CONNECT4PLAYER_HPP
#define CONNECT4PLAYER_HPP

class Connect4Game;

class Connect4Player
{
public:
	Connect4Player(char);
	char getChip();
	void setChip(char);
	virtual int makeTurn() = 0;
	void attachGame(Connect4Game*);
protected:
	char chip_;
	Connect4Game* attachedGame_;
};


#endif