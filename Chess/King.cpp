#include "King.h"


King::King() {
	this->type = 'K';
	this->numOfMoves = 0;
}
King::King(char color) {
	this->type = 'K';
	this->numOfMoves = 0;
	this->color = color;
}
King::King(char color, Pos pos) {
	this->type = 'K';
	this->numOfMoves = 0;
	this->color = color;
	this->pos = pos;
}

// Hàm kiểm tra việc di chuyển đến vị trí đích có hợp lệ hay không
bool King::validateMove(Piece* board[8][8], Pos moveToPos) {
	return false;
}
