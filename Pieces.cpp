#include "Pieces.h"

chess::Piece::Piece(Type piece_type, Color piece_color) {
	for (int i = 0; i < 16; i++) {
		vertices[i] = 0.0f;
	}
	this->piece_type = piece_type;
	this->piece_color = piece_color;
}

chess::Type chess::Piece::getType() {
	return piece_type;
}

chess::Color chess::Piece::getColor() {
	return piece_color;
}

std::vector<std::tuple<int, int>> chess::Piece::getValidMoves() {
	return valid_moves;
}

std::vector<std::tuple<int, int>> chess::Piece::getMoveDirections() {
	return possible_directions;
}

float* chess::Piece::getVertices() {
	return vertices;
}

chess::King::King(Color piece_color) : Piece(Type::king, piece_color) {
	possible_directions.push_back(std::make_tuple( 1,  0));
	possible_directions.push_back(std::make_tuple(-1,  0));
	possible_directions.push_back(std::make_tuple( 0,  1));
	possible_directions.push_back(std::make_tuple( 0, -1));
	possible_directions.push_back(std::make_tuple( 1,  1));
	possible_directions.push_back(std::make_tuple( 1, -1));
	possible_directions.push_back(std::make_tuple(-1,  1));
	possible_directions.push_back(std::make_tuple(-1, -1));
}

bool chess::King::canMoveOneBlock() {
	return true;
}

chess::Queen::Queen(Color piece_color) : Piece(Type::queen, piece_color) {
	possible_directions.push_back(std::make_tuple( 1,  0));
	possible_directions.push_back(std::make_tuple(-1,  0));
	possible_directions.push_back(std::make_tuple( 0,  1));
	possible_directions.push_back(std::make_tuple( 0, -1));
	possible_directions.push_back(std::make_tuple( 1,  1));
	possible_directions.push_back(std::make_tuple( 1, -1));
	possible_directions.push_back(std::make_tuple(-1,  1));
	possible_directions.push_back(std::make_tuple(-1, -1));
}

bool chess::Queen::canMoveOneBlock() {
	return false;
}

chess::Rook::Rook(Color piece_color) : Piece(Type::rook, piece_color) {
	possible_directions.push_back(std::make_tuple( 1,  0));
	possible_directions.push_back(std::make_tuple(-1,  0));
	possible_directions.push_back(std::make_tuple( 0,  1));
	possible_directions.push_back(std::make_tuple( 0, -1));
}

bool chess::Rook::canMoveOneBlock() {
	return false;
}

chess::Bishop::Bishop(Color piece_color) : Piece(Type::bishop, piece_color) {
	possible_directions.push_back(std::make_tuple( 1,  1));
	possible_directions.push_back(std::make_tuple( 1, -1));
	possible_directions.push_back(std::make_tuple(-1,  1));
	possible_directions.push_back(std::make_tuple(-1, -1));
}

bool chess::Bishop::canMoveOneBlock() {
	return false;
}

chess::Knight::Knight(Color piece_color) : Piece(Type::knight, piece_color) {
	possible_directions.push_back(std::make_tuple( 2,  1));
	possible_directions.push_back(std::make_tuple( 2, -1));
	possible_directions.push_back(std::make_tuple(-2,  1));
	possible_directions.push_back(std::make_tuple(-2, -1));
	possible_directions.push_back(std::make_tuple( 1,  2));
	possible_directions.push_back(std::make_tuple( 1, -2));
	possible_directions.push_back(std::make_tuple(-1,  2));
	possible_directions.push_back(std::make_tuple(-1, -2));
}

bool chess::Knight::canMoveOneBlock() {
	return true;
}

chess::Pawn::Pawn(Color piece_color) : Piece(Type::pawn, piece_color) {
	promoted_to = Type::pawn;
}

bool chess::Pawn::canMoveOneBlock() {	
	if ((promoted_to == Type::pawn) || (promoted_to == Type::knight))
		return true;
	else
		return false;
}

chess::Type chess::Pawn::getType()
{
	return promoted_to;
}
