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
private:
	struct GameOptions;
public:
	void start();
	Connect4Game(Connect4Player* _p1, Connect4Player* _p2, int _rows, int _columns);
	Connect4Game(Connect4Player* _p1, Connect4Player* _p2);

	char** getField();
	int getColumns();
	int getRows();
	GameOptions getOptions();
	void setCustomView(Connect4View*);
	void win(Connect4Player*);
	char getWinnerChip();



private:
	enum class DefaultOptions
	{
		Rows = 6,
		Columns = 7,
		WinSequence = 4,
		FirstPlayerCharacter = 'X',
		SecondPlayerCharacter = 'O',
		EmptyCellCharacter = '.',
		UnknownWinner = '?'
	};

	struct CurrentState
	{
		struct LastTurn
		{
			char chip_;
			int x_;
			int y_;
		};

		int turn = 0;
		LastTurn lastTurn;
		char winner = (char)DefaultOptions::UnknownWinner;
	};

	struct GameOptions
	{
		int rows = (int)DefaultOptions::Rows;
		int columns = (int)DefaultOptions::Columns;
		int winSequence = (int)DefaultOptions::WinSequence;
		char firstPlayerCharacter = (int)DefaultOptions::FirstPlayerCharacter;
		char secondPlayerCharacter = (int)DefaultOptions::SecondPlayerCharacter;
		char emptyCellCharacter = (int)DefaultOptions::EmptyCellCharacter;
		char unknownWinner = (int)DefaultOptions::UnknownWinner;
	};

	char** field_;
	Connect4Player* players_[2];
	Connect4View* attachedView_;
	GameOptions options_;
	CurrentState now_;


	void gameLoop();
	int gameOver();
	bool pushChip(int, char);
	void attachView(Connect4View*);
};

#endif