#ifndef CONNECT4GAME_HPP
#define CONNECT4GAME_HPP

#include <iostream>

class Connect4Player;
class Connect4View;

class Connect4Game
{
private:
	struct GameOptions;
public:
	struct Point
	{
		int x;
		int y;
	};

	enum class GameCondition
	{
		InProcess = 0,
		Draw = 1,
		Player1Wins = 2,
		Player2Wins = 3,
	};

	explicit Connect4Game(Connect4Player* _p1, Connect4Player* _p2, const int _rows, const int _columns);
	explicit Connect4Game(Connect4Player* _p1, Connect4Player* _p2);

	void start();
	char** getField();
	int getColumns();
	int getRows();
	GameOptions getOptions();
	void setCustomView(Connect4View*);
	std::pair<GameCondition, char> getCurrentCondition();

	static Point oppositeDirections[][2];
	static int numberOfPairs;
	static int pairOfOppositeDirections;

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

	struct CurrentState
	{
		struct LastTurn
		{
			int column;
			int row;
		};

		int turn = 0;
		LastTurn lastTurn;
		GameCondition condition;
	};

	char** field_;
	Connect4Player* players_[2];

	Connect4View* attachedView_;
	GameOptions options_;
	CurrentState now_;


	void gameLoop();
	void updateCurrentCondition();
	bool pushChip(const int _column, const char _chip);
	void attachView(Connect4View* _view);
	void initField(char**& _field, const int _rows, const int _columns, const char _cell);
	void setLastTurnCoord(const int _row, const int _column);

	int maxSequenceForSpecifiedChip(const char _chip, const Point _point);
	int sequenceOnDirectionForSpecifiedChip(const char _chip, const Point _point, const Point _direction);
};

using C4GPoint = Connect4Game::Point;

#include "Connect4Player.hpp"
#include "Connect4View.hpp"
#include "Connect4ViewConsole.hpp"
#include "Connect4PlayerAi.hpp"
#include "Connect4PlayerKeyboard.hpp"

#endif