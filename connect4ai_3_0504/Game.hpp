#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <stack>

namespace Connect4
{
	class Player;
	class View;

	class Game
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

		explicit Game(Connect4::Player* _p1, Connect4::Player* _p2, const int _rows, const int _columns);
		explicit Game(Player* _p1, Player* _p2);

		void start();
		char** getField();
		int getColumns();
		int getRows();
		GameOptions getOptions();
		void setCustomView(Connect4::View*);
		std::pair<GameCondition, char> getCurrentCondition();

		static Point oppositeDirections[][2];
		static int numberOfPairs;
		static int pairOfOppositeDirections;

		void temporarilyMove(const char _chip, const Point _point);
		std::pair<char, Point> undoAndReturnTemporarilyMove();
		void clearTemporarilyMoves();

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
			int turn = 0;
			Point lastTurn;
			GameCondition condition;
		};

		char** field_;
		Player* players_[2];

		View* attachedView_;
		GameOptions options_;
		CurrentState now_;
		std::stack<std::pair<char, Point>> temporarilyMoves;


		void gameLoop();
		void updateCurrentCondition();
		bool pushChip(const int _column, const char _chip);
		void attachView(View* _view);
		void initField(char**& _field, const int _rows, const int _columns, const char _cell);
		void setLastTurnCoord(const int _row, const int _column);

		int maxSequenceForSpecifiedChip(const char _chip, const Point _point);
		int sequenceOnDirectionForSpecifiedChip(const char _chip, const Point _point, const Point _direction);
	};

	using C4GPoint = Game::Point;
}

#include "Player.hpp"
#include "View.hpp"
#include "ViewConsole.hpp"
#include "PlayerAi.hpp"
#include "PlayerKeyboard.hpp"

#endif