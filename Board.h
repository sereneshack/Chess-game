#pragma once

#include "Pieces.h"

#include <vector>

namespace chess {
	class Move {
		std::tuple <int, int> src, des;
		Piece* moving_piece, * captured_piece;
	public:
		Move();
		Move(std::tuple<int, int> src, std::tuple<int, int> des, Piece* moving_piece, Piece* captured_piece);
		bool isInvalid();
		std::tuple<int, int> getSrc();
		std::tuple<int, int> getDes();
		Piece* getMovingPiece();
		Piece* getCapturedPiece();
	};
	class Board {
	private:
		class Square {
		private:
			Piece* piece_placed;
		public:
			Piece* getPiece();
			void placePiece(Piece *piece);
			void removePiece();
		};
		Square squares[8][8];
	public:
		Board();
		Piece* getPiece(int rank, int file);
		void placePiece(Piece *piece, int rank, int file);
		void removePiece(int rank, int file);
		void display();
	};
}
