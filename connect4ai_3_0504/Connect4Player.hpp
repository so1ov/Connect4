#ifndef CONNECT4PLAYER_HPP
#define CONNECT4PLAYER_HPP

class Connect4Game;

class Connect4Player
{
public:
	explicit Connect4Player(const char _chip);

	char getChip();
	void setChip(char _chip);
	virtual int makeTurn() = 0;
	void attachGame(Connect4Game* _game);
protected:
	char chip_;
	Connect4Game* attachedGame_;
};


#endif