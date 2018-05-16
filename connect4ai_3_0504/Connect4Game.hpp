#ifndef CONNECT4GAME_HPP
#define CONNECT4GAME_HPP

class Connect4Player;
class Connect4View;

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

	struct Point
	{
		int X;
		int Y;
	};

	static Point oppositeDirections[][2];
	static int numberOfPairs;
	static int pairOfOppositeVectors;

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
			Point pt;
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
	void calculateGameOver();
	bool gameOver();
	bool pushChip(int, char);
	bool pointOnField(Point);
	bool findWinSequenceOfSpecifiedChipOnAllStraightsThroughPoint(Point, char);
	int maxSequenceOfSpecifiedChipOnThisStraight(Point, Point, char);
	void attachView(Connect4View*);
};

using C4GPoint = Connect4Game::Point;

#include "Connect4Player.hpp"
#include "Connect4View.hpp"
#include "Connect4ViewConsole.hpp"
#include "Connect4PlayerAi.hpp"
#include "Connect4PlayerKeyboard.hpp"

#endif