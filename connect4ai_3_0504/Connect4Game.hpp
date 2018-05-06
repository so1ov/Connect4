#ifndef CONNECT4GAME_HPP
#define CONNECT4GAME_HPP

#include <iostream>

#include "Connect4Player.hpp"
#include "Connect4View.hpp"
#include "Connect4ViewConsole.hpp"
#include "Connect4PlayerAi.hpp"
#include "Connect4PlayerKeyboard.hpp"

class Connect4Game
{
public:
	void start();
	Connect4Game(int size, Connect4Player* _p1, Connect4Player* _p2);
	Connect4Game(Connect4Player* _p1, Connect4Player* _p2);

	char** getField();
	int getSize();
	void setCustomView(Connect4View*);
	void win(char);

	std::string debugInfo();
	void setLastDecision(int);

	enum Constants
	{
		DefaultSize = 5,
		DefaultFirstPlayerCharacter = 'X',
		DefaultSecondPlayerCharacter = 'O',
		EmptyCellCharacter = '.',
		UnknownWinner = '?'
	};
	
private:
	char** field_;
	int size_;
	Connect4Player* players_[2];
	Connect4View* attachedView_;

	struct
	{
		int turn;
		int lastColumn, lastRow;
		int winner = UnknownWinner;
		int lastDecision;
	}now_;

	void gameLoop();
	int gameOver();
	bool pushChip(int, char);
	void attachView(Connect4View*);
};

#endif