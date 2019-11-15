#pragma once

#include <stack>
#include "BackTrack.h"

namespace chess {

	class GameManager {
		enum GameState { selecting_square, selecting_target, game_over };
		Board board;
		Color turn;
		Player team_white, team_black;
		std::stack<Move> previous_moves;
		std::tuple<int, int> selector;
		std::vector<std::tuple<int, int>> highlighted_squares;
		void makeMove(std::tuple<int, int> src, std::tuple<int, int> des);
		void undoMove();
		GameState current_state;
	public:
		void setSelector(int rank, int file);
		std::tuple<int, int> getSelector();
		void setHighlightedSquares(int rank, int file);
		void clearHighlightedSquares();
		std::vector<std::tuple<int, int>> getHighlightedSquares();
		GameManager();
		void start();
		void render();
	};
}
