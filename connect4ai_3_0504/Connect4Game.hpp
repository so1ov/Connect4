#ifndef CONNECT4GAME_HPP
#define CONNECT4GAME_HPP

#include "Connect4Util.hpp"

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
	Connect4Game(int _rows, int _columns, Connect4Player* _p1, Connect4Player* _p2);
	Connect4Game(Connect4Player* _p1, Connect4Player* _p2);

	char** getField();
	int getColumns();
	int getRows();
	GameOptions getOptions();
	void setCustomView(Connect4View*);
	void win(Connect4Player*);
	char getWinnerChip();

private:
	enum DefaultOptions
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
		struct TurnInfo
		{
			char chip;
			C4GPoint pt;
		};

		int turn = 0;
		TurnInfo lastTurn;
		char winner = UnknownWinner;
	};

	struct GameOptions
	{
		int rows = DefaultOptions::Rows;
		int columns = DefaultOptions::Columns;
		int winSequence = DefaultOptions::WinSequence;
		char firstPlayerCharacter = DefaultOptions::FirstPlayerCharacter;
		char secondPlayerCharacter = DefaultOptions::SecondPlayerCharacter;
		char emptyCellCharacter = DefaultOptions::EmptyCellCharacter;
		char unknownWinner = DefaultOptions::UnknownWinner;
	}options_;

	char** field_;
	Connect4Player* players_[2];
	Connect4View* attachedView_;
	CurrentState now_;

	void gameLoop();
	int gameOver();
	bool pushChip(int, char);
	void attachView(Connect4View*);
};

#endif