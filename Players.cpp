#include "Players.h"

#include <iostream>

static bool onBoard(int rank, int file) {
	return ((rank >= 0) && (rank < 8) && (file >= 0) && (file < 8));
}

bool checkByKnight(int rank1, int file1, chess::Board& board, chess::Color player_side) {
	int rank2, file2;
	rank2 = rank1 + 2, file2 = file1 + 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::knight) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 + 2, file2 = file1 - 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::knight) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 - 2, file2 = file1 + 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::knight) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 - 2, file2 = file1 - 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::knight) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;

	rank2 = rank1 + 1, file2 = file1 + 2;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::knight) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 + 1, file2 = file1 - 2;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::knight) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 - 1, file2 = file1 + 2;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::knight) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 - 1, file2 = file1 - 2;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::knight) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	return false;
}

bool checkByRook(int rank1, int file1, chess::Board& board, chess::Color player_side) {
	for (int i = 1; i < 8; i++) {
		int rank2 = rank1 + i, file2 = file1;
		if (onBoard(rank2, file2)) {
			chess::Piece *piece = board.getPiece(rank2, file2);
			if (piece == nullptr) {
				continue;
			} else {
				if (piece->getColor() == player_side) {
					break;
				} else if ((piece->getType() == chess::Type::rook) || (piece->getType() == chess::Type::queen)){
					return true;
				}
			}
		} else {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		int rank2 = rank1 - i, file2 = file1;
		if (onBoard(rank2, file2)) {
			chess::Piece *piece = board.getPiece(rank2, file2);
			if (piece == nullptr) {
				continue;
			}
			else {
				if (piece->getColor() == player_side) {
					break;
				}
				else if ((piece->getType() == chess::Type::rook) || (piece->getType() == chess::Type::queen)) {
					return true;
				}
			}
		} else {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		int rank2 = rank1, file2 = file1 + i;
		if (onBoard(rank2, file2)) {
			chess::Piece *piece = board.getPiece(rank2, file2);
			if (piece == nullptr) {
				continue;
			}
			else {
				if (piece->getColor() == player_side) {
					break;
				} else if ((piece->getType() == chess::Type::rook) || (piece->getType() == chess::Type::queen)) {
					return true;
				}
			}
		} else {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		int rank2 = rank1, file2 = file1 - i;
		if (onBoard(rank2, file2)) {
			chess::Piece *piece = board.getPiece(rank2, file2);
			if (piece == nullptr) {
				continue;
			} else {
				if (piece->getColor() == player_side) {
					break;
				} else if ((piece->getType() == chess::Type::rook) || (piece->getType() == chess::Type::queen)) {
					return true;
				}
			}
		} else {
			break;
		}
	}
	return false;
}

bool checkByBishop(int rank1, int file1, chess::Board& board, chess::Color player_side) {
	for (int i = 1; i < 8; i++) {
		int rank2 = rank1 + i, file2 = file1 + i;
		if (onBoard(rank2, file2)) {
			chess::Piece *piece = board.getPiece(rank2, file2);
			if (piece == nullptr) {
				continue;
			} else {
				if (piece->getColor() == player_side) {
					break;
				} else if ((piece->getType() == chess::Type::bishop) || (piece->getType() == chess::Type::queen)) {
					return true;
				}
			}
		} else {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		int rank2 = rank1 + i, file2 = file1 - i;
		if (onBoard(rank2, file2)) {
			chess::Piece *piece = board.getPiece(rank2, file2);
			if (piece == nullptr) {
				continue;
			} else {
				if (piece->getColor() == player_side) {
					break;
				} else if ((piece->getType() == chess::Type::bishop) || (piece->getType() == chess::Type::queen)) {
					return true;
				}
			}
		} else {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		int rank2 = rank1 - i, file2 = file1 + i;
		if (onBoard(rank2, file2)) {
			chess::Piece *piece = board.getPiece(rank2, file2);
			if (piece == nullptr) {
				continue;
			} else {
				if (piece->getColor() == player_side) {
					break;
				} else if ((piece->getType() == chess::Type::bishop) || (piece->getType() == chess::Type::queen)) {
					return true;
				}
			}
		} else {
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		int rank2 = rank1 - i, file2 = file1 - i;
		if (onBoard(rank2, file2)) {
			chess::Piece *piece = board.getPiece(rank2, file2);
			if (piece == nullptr) {
				continue;
			} else {
				if (piece->getColor() == player_side) {
					break;
				} else if ((piece->getType() == chess::Type::bishop) || (piece->getType() == chess::Type::queen)) {
					return true;
				}
			}
		} else {
			break;
		}
	}
	return false;
}

bool checkByKing(int rank1, int file1, chess::Board& board, chess::Color player_side) {
	int rank2, file2;
	rank2 = rank1 + 1, file2 = file1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::king) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 - 1, file2 = file1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::king) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1, file2 = file1 + 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::king) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1, file2 = file1 - 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::king) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 + 1, file2 = file1 + 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::king) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 + 1, file2 = file1 - 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::king) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 - 1, file2 = file1 + 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::king) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	rank2 = rank1 - 1, file2 = file1 - 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::king) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	return false;
}

bool checkByPawn(int rank1, int file1, chess::Board& board, chess::Color player_side) {
	int rank2 = rank1 + ((player_side == chess::Color::white) ? 1 : -1);
	int file2 = file1 + 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::pawn) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	file2 = file1 - 1;
	if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getType() == chess::Type::pawn) && (board.getPiece(rank2, file2)->getColor() != player_side))
		return true;
	return false;
}

bool chess::Player::isChecked(Board& board) {
	int rank = 0, file = 0;
	//finding the king
	for (unsigned int i = 0; i < player_set.size(); i++) {
		if (player_set[i]->getType() == chess::Type::king) {
			rank = std::get<0>(player_set[i]->current_block);
			file = std::get<1>(player_set[i]->current_block);
			break;
		}
	}
	if (checkByKnight(rank, file, board, player_side))
		return true;
	if (checkByRook(rank, file, board, player_side))
		return true;
	if (checkByBishop(rank, file, board, player_side))
		return true;
	if (checkByKing(rank, file, board, player_side))
		return true;
	if (checkByPawn(rank, file, board, player_side))
		return true;
	return false;
}

bool chess::Player::noValidMoves() {
	for (unsigned int i = 0; i < player_set.size(); i++) {
		if (player_set[i]->valid_moves.size() > 0)
			return false;
	}
	return true;
}

chess::Player::Player(Board & board, Color side_color) {
	player_side = side_color;
	Piece *piece;

	if (side_color == chess::Color::white) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 8; j++) {
				piece = board.getPiece(i, j);
				if (piece->getType() == chess::Type::pawn) {
					piece->valid_moves.push_back(std::make_tuple(2, j));
					piece->valid_moves.push_back(std::make_tuple(3, j));
				} else if (piece->getType() == chess::Type::knight) {
					piece->valid_moves.push_back(std::make_tuple(2, j - 1));
					piece->valid_moves.push_back(std::make_tuple(2, j + 1));
				}
				player_set.push_back(piece);
				piece->current_block = std::make_tuple(i, j);
			}
		}
	} else {
		for (int i = 7; i > 5; i--) {
			for (int j = 0; j < 8; j++) {
				piece = board.getPiece(i, j);
				if (piece->getType() == chess::Type::pawn) {
					piece->valid_moves.push_back(std::make_tuple(5, j));
					piece->valid_moves.push_back(std::make_tuple(4, j));
				} else if (piece->getType() == chess::Type::knight) {
					piece->valid_moves.push_back(std::make_tuple(5, j - 1));
					piece->valid_moves.push_back(std::make_tuple(5, j + 1));
				}
				player_set.push_back(piece);
				piece->current_block = std::make_tuple(i, j);
			}
		}
	}
}

chess::Color chess::Player::getColor() {
	return player_side;
}

void chess::Player::displayValidMoves() {
	for (auto itr = player_set.begin(); itr != player_set.end(); itr++) {
		std::vector<std::tuple<int, int>> valid_moves_vector = (*itr)->getValidMoves();
		for (unsigned int i = 0; i < valid_moves_vector.size(); i++) {
			std::cout << std::get<0>((*itr)->current_block) << " " << std::get<1>((*itr)->current_block) << " -> " << std::get<0>(valid_moves_vector[i]) << " " << std::get<1>(valid_moves_vector[i]) << std::endl;
		}
	}
}

bool chess::Player::updateValidMoves(Board & board) {
	for (unsigned int i = 0; i < player_set.size(); i++) {
		Piece *piece = player_set[i];
		player_set[i]->valid_moves.clear();
		std::vector<std::tuple<int, int>> move_direction_vector = piece->getMoveDirections();
		const std::tuple<int, int> current_block = player_set[i]->current_block;
		const int rank1 = std::get<0>(current_block), file1 = std::get<1>(current_block);
		if (onBoard(rank1, file1)) {
			if (piece->canMoveOneBlock()) {
				if (piece->getType() != chess::Type::pawn) {
					for (unsigned int j = 0; j < move_direction_vector.size(); j++) {
						int rank2 = rank1 + std::get<0>(move_direction_vector[j]), file2 = file1 + std::get<1>(move_direction_vector[j]);
						if (onBoard(rank2, file2)) {
							Piece* piece2 = board.getPiece(rank2, file2);
							if ((piece2 == nullptr) || (piece2->getColor() != player_side)) {
								board.removePiece(rank1, file1);
								board.placePiece(piece, rank2, file2);
								if (!this->isChecked(board))
									player_set[i]->valid_moves.push_back(std::make_tuple(rank2, file2));
								board.placePiece(piece2, rank2, file2);
								board.placePiece(piece, rank1, file1);
							}
						}
					}
				} else {
					int delta_rank = ((player_side == chess::Color::white) ? 1 : -1);
					int rank2 = rank1 + delta_rank, file2 = file1;
					if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) == nullptr)) {
						board.removePiece(rank1, file1);
						board.placePiece(piece, rank2, file2);
						if (!this->isChecked(board))
								player_set[i]->valid_moves.push_back(std::make_tuple(rank2, file2));
						board.removePiece(rank2, file2);
						board.placePiece(piece, rank1, file1);
					}
					if (((std::get<0>(piece->current_block) == 1) && (player_side == Color::white)) || ((std::get<0>(piece->current_block) == 6) && (player_side == Color::black))) {
						rank2 = rank1 + 2 * delta_rank, file2 = file1;
						if ((board.getPiece(rank1 + delta_rank, file1) == nullptr) && (board.getPiece(rank1 + 2 * delta_rank, file1) == nullptr)) {
							board.removePiece(rank1, file1);
							board.placePiece(piece, rank2, file2);
							if (!this->isChecked(board))
								player_set[i]->valid_moves.push_back(std::make_tuple(rank2, file2));
							board.removePiece(rank2, file2);
							board.placePiece(piece, rank1, file1);
						}
					}
					rank2 = rank1 + delta_rank, file2 = file1 - 1;
					if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getColor() != player_side)) {
						Piece* piece2 = board.getPiece(rank2, file2);
						board.removePiece(rank1, file1);
						board.placePiece(piece, rank2, file2);
						if (!this->isChecked(board))
							player_set[i]->valid_moves.push_back(std::make_tuple(rank2, file2));
						board.placePiece(piece, rank1, file1);
						board.placePiece(piece2, rank2, file2);
					}
					rank2 = rank1 + delta_rank, file2 = file1 + 1;
					if ((onBoard(rank2, file2)) && (board.getPiece(rank2, file2) != nullptr) && (board.getPiece(rank2, file2)->getColor() != player_side)) {
						Piece* piece2 = board.getPiece(rank2, file2);
						board.removePiece(rank1, file1);
						board.placePiece(piece, rank2, file2);
						if (!this->isChecked(board))
							player_set[i]->valid_moves.push_back(std::make_tuple(rank2, file2));
						board.placePiece(piece, rank1, file1);
						board.placePiece(piece2, rank2, file2);
					}
				}
			} else {
				for (unsigned int j = 0; j < move_direction_vector.size(); j++) {
					int delta_rank = std::get<0>(move_direction_vector[j]), delta_file = std::get<1>(move_direction_vector[j]);
					for (int k = 1; k < 8; k++) {
						int rank2 = rank1 + k * delta_rank, file2 = file1 + k * delta_file;
						if (!onBoard(rank2, file2))
							break;
						Piece* piece2 = board.getPiece(rank2, file2);
						if ((piece2 == nullptr) || (piece2->getColor() != player_side)) {
							board.removePiece(rank1, file1);
							board.placePiece(piece, rank2, file2);
							if (!this->isChecked(board))
								player_set[i]->valid_moves.push_back(std::make_tuple(rank2, file2));
							board.placePiece(piece, rank1, file1);
							board.placePiece(piece2, rank2, file2);
						}
						if (piece2 != nullptr) {
							break;
						}
					}
				}
			}
		}		
	}
	return noValidMoves();
}

void chess::Player::capture(Piece * captured_piece) {
	if (captured_piece == nullptr) {
		return;
	} else if (captured_piece->getColor() == player_side) {
		captured_piece->current_block = std::make_tuple(8, 8);
		captured_piece->valid_moves.clear();
	}
}

void chess::Player::displayInfo() {
	std::cout << ((player_side == Color::white) ? "White" : "Black") << std::endl;
	for (unsigned int i = 0; i < player_set.size(); i++) {
		std::cout << player_set[i]->getType() << " " << std::get<0>(player_set[i]->current_block) << std::get<1>(player_set[i]->current_block) << " : ";
		std::vector<std::tuple<int, int>> valid_moves_vector = player_set[i]->getValidMoves();
		for (unsigned int j = 0; j < valid_moves_vector.size(); j++) {
			std::cout << std::get<0>(valid_moves_vector[j]) << std::get<1>(valid_moves_vector[j]) << " ";
		}
		std::cout << std::endl;
	}
}
