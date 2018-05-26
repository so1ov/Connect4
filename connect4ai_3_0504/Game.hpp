#ifndef Game_HPP
#define Game_HPP

#include <iostream>

namespace Connect4
{
	class View;
	class Player;

	class Game
	{
	private:
		struct GameOptions;
		enum class DefaultOptions;
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

		Game(Player* _p1, Player* _p2,
			int _rows = (int)DefaultOptions::Rows,
			int _columns = (int)DefaultOptions::Columns);

		void start();
		char** getField();
		int getColumns();
		int getRows();
		GameOptions getOptions();
		void setCustomView(View*);
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
			int rows                   = (int)DefaultOptions::Rows;
			int columns                = (int)DefaultOptions::Columns;
			int winSequence            = (int)DefaultOptions::WinSequence;
			char firstPlayerCharacter  = (int)DefaultOptions::FirstPlayerCharacter;
			char secondPlayerCharacter = (int)DefaultOptions::SecondPlayerCharacter;
			char emptyCellCharacter    = (int)DefaultOptions::EmptyCellCharacter;
			char unknownWinner         = (int)DefaultOptions::UnknownWinner;
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
		Player* players_[2];
		View* attachedView_;
		GameOptions options_;
		CurrentState now_;

		void initField(char**& _field, int _rows, int _columns, char _cell);
		void gameLoop();
		void updateCurrentCondition();
		bool pushChip(int _column, char _chip);
		void attachView(View* _view);

		int maxSequenceForSpecifiedChip(char _chip, Point _point);
		int sequenceOnDirectionForSpecifiedChip(char _chip, Point _point, Point _direction);
	};

	using C4GPoint = Game::Point;
}

#include "Player.hpp"
#include "View.hpp"
#include "ViewConsole.hpp"
#include "PlayerAi.hpp"
#include "PlayerKeyboard.hpp"

#endif