#pragma once

#include "Players.h"

namespace chess {
	class BacktrackingModule {
		class BoardState {
		private:
			float score;
			Move prev_move;
			friend class BacktrackingModule;
		public:
			BoardState();
		};
		Color turn;
		Board testing_board;
		Player testing_team_white, testing_team_black;
		BoardState current_state;
		BacktrackingModule();
		void backtrack(unsigned int level = 0);
	public:
		void updateStateTree();
	};
}
