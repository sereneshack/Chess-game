#include "GameRules.h"

#include <Windows.h>
#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <cmath>

static bool onBoard(int rank, int file) {
	return ((rank >= 0) && (rank < 8) && (file >= 0) && (file < 8));
}

static void draw(const std::string& path, float* vertices)
{
	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
	};

	OpenGL::VertexArray va;
	OpenGL::VertexBuffer vb(vertices, 4 * 4 * sizeof(float));

	OpenGL::VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	OpenGL::IndexBuffer ib(indices, 6);

	glm::mat4 proj = glm::ortho(-960.0f, 960.0f, -540.0f, 540.0f, -1.0f, 1.0f);

	OpenGL::Shader shader("res/shaders/basic01.shader");
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", proj);

	OpenGL::Texture texture(path);
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	OpenGL::Renderer renderer;
	renderer.Draw(va, ib, shader);
}

void chess::GameManager::makeMove(std::tuple<int, int> src, std::tuple<int, int> des) {
	int src_rank = std::get<0>(src), src_file = std::get<1>(src), des_rank = std::get<0>(des), des_file = std::get<1>(des);
	if ((!onBoard(src_rank, src_file)) || (!onBoard(des_rank, des_file)))
		return;
	Piece* moving_piece = board.getPiece(src_rank, src_file);
	Piece* captured_piece = board.getPiece(des_rank, des_file);
	if ((moving_piece != nullptr) && (moving_piece->getColor() == turn) && ((captured_piece == nullptr) || (captured_piece->getColor() != turn))) {
		std::vector<std::tuple<int, int>> valid_moves = moving_piece->getValidMoves();
		if (std::find(valid_moves.begin(), valid_moves.end(), des) != valid_moves.end()) {
			Player& oppenent = ((turn == chess::Color::black) ? team_white : team_black);
			if (captured_piece != nullptr) {
				oppenent.capture(captured_piece);
			}
			board.removePiece(src_rank, src_file);
			board.placePiece(moving_piece, des_rank, des_file);
			turn = ((turn == chess::Color::white) ? chess::Color::black : chess::Color::white);
			previous_moves.push(Move(src, des, moving_piece, captured_piece));
			if (oppenent.updateValidMoves(board)) {
				current_state = GameState::game_over;
			}
		}
	}
}

void chess::GameManager::undoMove() {
	if (!previous_moves.empty()) {
		Piece* moving_piece = previous_moves.top().getMovingPiece();
		Piece* captured_piece = previous_moves.top().getCapturedPiece();
		std::tuple<int, int> src = previous_moves.top().getSrc();
		std::tuple<int, int> des = previous_moves.top().getDes();
		int rank1 = std::get<0>(src), file1 = std::get<1>(src);
		int rank2 = std::get<0>(des), file2 = std::get<1>(des);
		board.placePiece(moving_piece, rank1, file1);
		board.placePiece(captured_piece, rank2, file2);
		turn = ((turn == Color::white) ? (Color::black) : (Color::white));
		Player& side = ((turn == Color::white) ? team_white : team_black);
		side.updateValidMoves(board);
		previous_moves.pop();
	}
}

chess::GameManager::GameManager(): board(), team_white(board, Color::white), team_black(board, Color::black) {
	turn = chess::Color::white;
	current_state = GameState::selecting_square;
	selector = std::make_tuple(0, 4);
}

void chess::GameManager::setSelector(int rank, int file) {
	selector = std::make_tuple(rank, file);
}

std::tuple<int, int> chess::GameManager::getSelector() {
	return selector;
}

void chess::GameManager::setHighlightedSquares(int rank, int file) {
	highlighted_squares.clear();
	if (onBoard(rank, file)) {
		Piece* piece = board.getPiece(rank, file);
		if (piece != nullptr) {
			highlighted_squares = piece->getValidMoves();
			highlighted_squares.push_back(std::make_tuple(rank, file));
		}
	}
}

void chess::GameManager::clearHighlightedSquares() {
	highlighted_squares.clear();
}

std::vector<std::tuple<int, int>> chess::GameManager::getHighlightedSquares()
{
	return highlighted_squares;
}

void chess::GameManager::start() {
	GameState current_state = GameState::selecting_square;
	std::tuple<int, int> src, des;
	std::vector<std::tuple<int, int>> valid_moves;
	unsigned long long timer = GetTickCount64();
	while (current_state != GameState::game_over) {
		unsigned long long current_timer = GetTickCount64();
		if (current_timer - timer > 250) {
			timer = current_timer;
			const int rank = std::get<0>(this->getSelector()), file = std::get<1>(this->getSelector());
			if ((GetAsyncKeyState(VK_RETURN)) && 0x8000) {
				Piece* piece = board.getPiece(rank, file);
				if ((piece != nullptr) && (piece->getColor() == turn)) {
					src = this->getSelector();
					this->setHighlightedSquares(rank, file);
					valid_moves = piece->getValidMoves();
					current_state = GameState::selecting_target;
				} else {
					if (current_state == GameState::selecting_target) {					
						if (find(valid_moves.begin(), valid_moves.end(), this->getSelector()) != valid_moves.end()) {
							des = this->getSelector();
							current_state = GameState::selecting_square;
							this->makeMove(src, des);
							this->clearHighlightedSquares();
						}
					}
				}
			} else if ((GetAsyncKeyState(VK_UP)) && 0x8000) {
				if (onBoard(rank + 1, file)) {
					this->setSelector(rank + 1, file);
				}
			} else if ((GetAsyncKeyState(VK_DOWN)) && 0x8000) {
				if (onBoard(rank - 1, file)) {
					this->setSelector(rank - 1, file);
				}
			} else if ((GetAsyncKeyState(VK_LEFT)) && 0x8000) {
				if (onBoard(rank, file + 1)) {
					this->setSelector(rank, file + 1);
				}
			} else if ((GetAsyncKeyState(VK_RIGHT)) && 0x8000) {
				if (onBoard(rank, file - 1)) {
					this->setSelector(rank, file - 1);
				}
			} else if ((GetAsyncKeyState(VK_BACK)) && 0x8000) {
				this->undoMove();
			}
		}
	}
}

void draw_board(const chess::Board& board);
void draw_highlighted_squares(const std::vector<std::tuple<int, int>>& highlighted_squares);
void draw_selector(std::tuple<int, int> selector_pos);
void draw_pieces(chess::Board& board, std::tuple<int, int> selector_pos);

void chess::GameManager::render() {
	draw_board(board);
	draw_highlighted_squares(this->getHighlightedSquares());
	draw_selector(this->getSelector());
	draw_pieces(board, this->getSelector());
}

void draw_board(const chess::Board& board) {
	float board_vertices[16] = { -500.0f, -500.0f, 0.0f, 0.0f, 500.0f, -500.0f, 1.0f, 0.0f, 500.0f, 500.0f, 1.0f, 1.0f, -500.0f, 500.0f, 0.0f, 1.0f };
	draw("res/textures/gui/board.png", board_vertices);
}

void draw_highlighted_squares(const std::vector<std::tuple<int, int>>& highlighted_squares) {
	float vertices[16];
	int rank, file;
	for (auto itr = highlighted_squares.begin(); itr != highlighted_squares.end(); itr++) {
		rank = std::get<0>(*itr);
		file = std::get<1>(*itr);
		float ycord = -437.5f + rank * 125.0f;
		float xcord = 437.5f - file * 125.0f;
		float span = 100.0f;
		vertices[0] = xcord - span / 2;
		vertices[1] = ycord - span / 2;
		vertices[2] = 0.0f;
		vertices[3] = 0.0f;
		vertices[4] = xcord + span / 2;
		vertices[5] = ycord - span / 2;
		vertices[6] = 1.0f;
		vertices[7] = 0.0f;
		vertices[8] = xcord + span / 2;
		vertices[9] = ycord + span / 2;
		vertices[10] = 1.0f;
		vertices[11] = 1.0f;
		vertices[12] = xcord - span / 2;
		vertices[13] = ycord + span / 2;
		vertices[14] = 0.0f;
		vertices[15] = 1.0f;
		if ((rank + file) % 2 == 0) {
			draw("res/textures/gui/square-dark.png", vertices);
		} else {
			draw("res/textures/gui/square-light.png", vertices);
		}
	}
}

void draw_selector(std::tuple<int, int> selector_pos) {
	float vertices[16];
	const int rank = std::get<0>(selector_pos), file = std::get<1>(selector_pos);
	const float ycord = -437.5f + rank * 125.0f;
	const float xcord = 437.5f - file * 125.0f;
	const float span = 100.0f;
	vertices[0] = xcord - span / 2;
	vertices[1] = ycord - span / 2;
	vertices[2] = 0.0f;
	vertices[3] = 0.0f;
	vertices[4] = xcord + span / 2;
	vertices[5] = ycord - span / 2;
	vertices[6] = 1.0f;
	vertices[7] = 0.0f;
	vertices[8] = xcord + span / 2;
	vertices[9] = ycord + span / 2;
	vertices[10] = 1.0f;
	vertices[11] = 1.0f;
	vertices[12] = xcord - span / 2;
	vertices[13] = ycord + span / 2;
	vertices[14] = 0.0f;
	vertices[15] = 1.0f;
	if ((rank + file) % 2 == 0) {
		draw("res/textures/gui/box-dark.png", vertices);
	}
	else {
		draw("res/textures/gui/box-light.png", vertices);
	}
}

void draw_pieces(chess::Board& board, std::tuple<int, int> selector_pos) {
	std::string prefix = "res/textures/pieces/chess-alt-";
	std::string theme = "solid-";
	std::string suffix = ".png";
	std::string piece_color, piece_type;
	float vertices[16];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			chess::Piece* piece = board.getPiece(i, j);
			if (piece != nullptr) {
				switch (piece->getColor()) {
				case chess::Color::white:
					piece_color = "white-";
					break;
				case chess::Color::black:
					piece_color = "black-";
					break;
				}
				switch (piece->getType()) {
				case chess::Type::rook:
					piece_type = "rook";
					break;
				case chess::Type::knight:
					piece_type = "knight";
					break;
				case chess::Type::bishop:
					piece_type = "bishop";
					break;
				case chess::Type::king:
					piece_type = "king";
					break;
				case chess::Type::queen:
					piece_type = "queen";
					break;
				case chess::Type::pawn:
					piece_type = "pawn";
				default:
					break;
				}
				float ycord = -437.5f + i * 125.0f;
				float xcord = 437.5f - j * 125.0f;
				float span = 100.0f;
				if ((i == std::get<0>(selector_pos)) && (j == std::get<1>(selector_pos)))
					span = 125.0f;
				vertices[0] = xcord - span / 2;
				vertices[1] = ycord - span / 2;
				vertices[2] = 0.0f;
				vertices[3] = 0.0f;
				vertices[4] = xcord + span / 2;
				vertices[5] = ycord - span / 2;
				vertices[6] = 1.0f;
				vertices[7] = 0.0f;
				vertices[8] = xcord + span / 2;
				vertices[9] = ycord + span / 2;
				vertices[10] = 1.0f;
				vertices[11] = 1.0f;
				vertices[12] = xcord - span / 2;
				vertices[13] = ycord + span / 2;
				vertices[14] = 0.0f;
				vertices[15] = 1.0f;
				std::string path = prefix + piece_color + theme + piece_type + suffix;
				draw(path, vertices);
			}
		}
	}
}
