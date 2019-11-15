#include "BackTrack.h"

chess::BacktrackingModule::BoardState::BoardState() {
	score = 0.0f;
	prev_move = Move();
}

chess::BacktrackingModule::BacktrackingModule() : turn(chess::Color::white), testing_board(), testing_team_white(testing_board, chess::Color::white), testing_team_black(testing_board, chess::Color::black), current_state() {
	int level = 0;
	this->backtrack(0);
}

void chess::BacktrackingModule::backtrack(unsigned int level) {
	/*Player& moving_player = ((turn == chess::Color::black) ? testing_team_black : testing_team_white);
	Player& opponent_player = ((turn == chess::Color::black) ? testing_team_white : testing_team_black);
	std::vector<std::tuple<std::tuple<int, int>, std::tuple<int, int>, int>> all_possible_moves;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece *moving_piece = testing_board.getPiece(i, j);
			if ((moving_piece != nullptr) && (moving_piece->getColor() == moving_player.getColor())) {
				std::vector<std::tuple<int, int>> valid_moves = moving_piece->getValidMoves();
				std::tuple<int, int> src = std::make_tuple(i, j);
				for (int k = 0; k < valid_moves.size(); k++) {
					std::tuple<int, int> des = valid_moves[k];
					int score = 0;
					Piece* captured_piece = testing_board.getPiece(get<0>(des), get<1>(des));
					if (captured_piece != nullptr) {
						switch (captured_piece->getType())
						{
						case Type::queen:
							score = 
						default:
							break;
						}
					}
					all_possible_moves.push_back(std::make_tuple(src, des));
				}
			}
		}
	}*/
}
