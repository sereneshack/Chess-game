#pragma once

#include <vector>
#include "Board.h"

namespace chess {
	class Player {
	private:		
		Color player_side;
		std::vector<Piece*> player_set;
	public:
		Player(Board& board, Color side_color);
		Color getColor();
	private:
		bool isChecked(Board& board); //Returns true if king is checked
		bool noValidMoves(); //Returns true if no valid moves are possible by any piece
	public:
		void displayValidMoves();
		bool updateValidMoves(Board& board); // Updates valid moves vector for every piece and returns noValidMoves()
		void capture(Piece* captured_piece);
		void displayInfo();
	};
}
