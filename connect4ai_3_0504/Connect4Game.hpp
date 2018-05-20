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

	void start();
	Connect4Game(Connect4Player* _p1, Connect4Player* _p2, int _rows, int _columns);
	Connect4Game(Connect4Player* _p1, Connect4Player* _p2);

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
			char chip;
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
	bool pushChip(int, char);
	void attachView(Connect4View*);

	int maxSequenceForSpecifiedChip(char _chip, Point _point);
	int sequenceOnDirectionForSpecifiedChip(char _chip, Point _point, Point _direction);
};

using C4GPoint = Connect4Game::Point;

#include "Connect4Player.hpp"
#include "Connect4View.hpp"
#include "Connect4ViewConsole.hpp"
#include "Connect4PlayerAi.hpp"
#include "Connect4PlayerKeyboard.hpp"

#endif