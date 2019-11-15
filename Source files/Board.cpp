#include "Board.h"

#include <iostream>

static bool onBoard(int rank, int file) {
	return ((rank >= 0) && (rank < 8) && (file >= 0) && (file < 8));
}

chess::Move::Move() {
	moving_piece = nullptr;
	captured_piece = nullptr;
}

chess::Move::Move(std::tuple<int, int> src, std::tuple<int, int> des, Piece* moving_piece, Piece* captured_piece) {
	this->src = src;
	this->des = des;
	this->moving_piece = moving_piece;
	this->captured_piece = captured_piece;
}

bool chess::Move::isInvalid() {
	return (moving_piece == nullptr);
}

std::tuple<int, int> chess::Move::getSrc() {
	return src;
}

std::tuple<int, int> chess::Move::getDes() {
	return des;
}

chess::Piece* chess::Move::getMovingPiece() {
	return moving_piece;
}

chess::Piece* chess::Move::getCapturedPiece() {
	return captured_piece;
}

chess::Board::Board() : squares() {
	this->placePiece(new Rook(Color::white), 0, 0);
	this->placePiece(new Knight(Color::white), 0, 1);
	this->placePiece(new Bishop(Color::white), 0, 2);
	this->placePiece(new Queen(Color::white), 0, 3);
	this->placePiece(new King(Color::white), 0, 4);
	this->placePiece(new Bishop(Color::white), 0, 5);
	this->placePiece(new Knight(Color::white), 0, 6);
	this->placePiece(new Rook(Color::white), 0, 7);
	this->placePiece(new Pawn(Color::white), 1, 0);
	this->placePiece(new Pawn(Color::white), 1, 1);
	this->placePiece(new Pawn(Color::white), 1, 2);
	this->placePiece(new Pawn(Color::white), 1, 3);
	this->placePiece(new Pawn(Color::white), 1, 4);
	this->placePiece(new Pawn(Color::white), 1, 5);
	this->placePiece(new Pawn(Color::white), 1, 6);
	this->placePiece(new Pawn(Color::white), 1, 7);

	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			this->placePiece(nullptr, i, j);
		}
	}

	this->placePiece(new Rook(Color::black), 7, 0);
	this->placePiece(new Knight(Color::black), 7, 1);
	this->placePiece(new Bishop(Color::black), 7, 2);
	this->placePiece(new Queen(Color::black), 7, 3);
	this->placePiece(new King(Color::black), 7, 4);
	this->placePiece(new Bishop(Color::black), 7, 5);
	this->placePiece(new Knight(Color::black), 7, 6);
	this->placePiece(new Rook(Color::black), 7, 7);
	this->placePiece(new Pawn(Color::black), 6, 0);
	this->placePiece(new Pawn(Color::black), 6, 1);
	this->placePiece(new Pawn(Color::black), 6, 2);
	this->placePiece(new Pawn(Color::black), 6, 3);
	this->placePiece(new Pawn(Color::black), 6, 4);
	this->placePiece(new Pawn(Color::black), 6, 5);
	this->placePiece(new Pawn(Color::black), 6, 6);
	this->placePiece(new Pawn(Color::black), 6, 7);
}

chess::Piece * chess::Board::getPiece(int rank, int file) {
	if (onBoard(rank, file))
		return squares[rank][file].getPiece();
	else
		return nullptr;
}

void chess::Board::placePiece(Piece * piece, int rank, int file) {
	if (onBoard(rank, file)) {
		squares[rank][file].placePiece(piece);
		if (piece != nullptr) {
			piece->current_block = std::make_tuple(rank, file);
			float ycord = -437.5f + rank * 125.0f;
			float xcord = 437.5f - file * 125.0f;
			float span = 100.0f;
			piece->vertices[ 0] = xcord - span / 2;
			piece->vertices[ 1] = ycord - span / 2;
			piece->vertices[ 2] = 0.0f;
			piece->vertices[ 3] = 0.0f;
			piece->vertices[ 4] = xcord + span / 2;
			piece->vertices[ 5] = ycord - span / 2;
			piece->vertices[ 6] = 1.0f;
			piece->vertices[ 7] = 0.0f;
			piece->vertices[ 8] = xcord + span / 2;
			piece->vertices[ 9] = ycord + span / 2;
			piece->vertices[10] = 1.0f;
			piece->vertices[11] = 1.0f;
			piece->vertices[12] = xcord - span / 2;
			piece->vertices[13] = ycord + span / 2;
			piece->vertices[14] = 0.0f;
			piece->vertices[15] = 1.0f;
		}
	}
}

void chess::Board::removePiece(int rank, int file) {
	if (onBoard(rank, file)) {
		Piece* piece = squares[rank][file].getPiece();
		if (piece != nullptr) {
			piece->current_block = std::make_tuple(8, 8);
		}
		squares[rank][file].removePiece();
	}
}

void chess::Board::display() {
	std::cout << "  ";
	for (int i = 0; i < 8; i++) {
		std::cout << "  " << i << " ";
	}
	std::cout << std::endl;
	for (int i = 0; i < 8; i++) {
		std::cout << i << " ";
		for (int j = 0; j < 8; j++) {
			Piece* piece = squares[i][j].getPiece();
			std::cout << " ";
			if (piece == nullptr) {
				std::cout << "  ";
			} else {
				switch (piece->getColor())
				{
				case chess::Color::white:
					std::cout << "W";
					break;
				case chess::Color::black:
					std::cout << "B";
					break;
				default:
					std::cout << " ";
					break;
				}
				switch (piece->getType())
				{
				case chess::Type::king:
					std::cout << "K";
					break;
				case chess::Type::queen:
					std::cout << "Q";
					break;
				case chess::Type::rook:
					std::cout << "R";
					break;
				case chess::Type::bishop:
					std::cout << "B";
					break;
				case chess::Type::knight:
					std::cout << "N";
					break;
				case chess::Type::pawn:
					std::cout << "P";
					break;
				default:
					std::cout << " ";
					break;
				}
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

chess::Piece* chess::Board::Square::getPiece(){
	return piece_placed;
}

void chess::Board::Square::placePiece(Piece *piece) {
	piece_placed = piece;
}

void chess::Board::Square::removePiece() {
	piece_placed = nullptr;
}
