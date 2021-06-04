#include "Rock.h"


Rock::Rock() {
	this->type = 'R';
	this->numOfMoves = 0;
}
Rock::Rock(char color) {
	this->type = 'R';
	this->numOfMoves = 0;
	this->color = color;
}
Rock::Rock(char color, Pos pos) {
	this->type = 'R';
	this->numOfMoves = 0;
	this->color = color;
	this->pos = pos;
}

// Hàm kiểm tra việc di chuyển đến vị trí đích có hợp lệ hay không
bool Rock::validateMove(Piece* board[8][8], Pos moveToPos) {
	int fromCol = pos.getCol();
	int fromRow = pos.getRow();
	int toCol = moveToPos.getCol();
	int toRow = moveToPos.getRow();

	if (pos == moveToPos) // Vị trí ô nguồn trùng vị trí ô đích
		return false;

	// Quân cờ tại ô nguồn cùng màu với quân cờ tại ô đích
	if (board[toRow][toCol] != NULL)
		if (board[toRow][toCol]->getColor() == color)
			return false;

	// Ô nguồn cùng cột với ô đích
	if (fromCol == toCol) {
		if (fromRow > toRow) {
			for (int i = fromRow-1; i > toRow; i--) {
				if (board[i][fromCol] != NULL) // Giữa ô nguồn và ô đích có quân cờ
					return false;
			}
		}
		if (fromRow < toRow) {
			for (int i = fromRow+1; i < toRow; i++) {
				if (board[i][fromCol] != NULL) // Giữa ô nguồn và ô đích có quân cờ
					return false;
			}
		}
		return true;
	}

	// Ô nguồn cùng hàng với ô đích
	if (fromRow == toRow) {
		if (fromCol > toCol) {
			for (int i = fromCol-1; i > toCol; i--) {
				if (board[fromRow][i] != NULL) // Giữa ô nguồn và ô đích có quân cờ
					return false;
			}
		}
		if (fromCol < toCol) {
			for (int i = fromCol+1; i < toCol; i++) {
				if (board[fromRow][i] != NULL) // Giữa ô nguồn và ô đích có quân cờ
					return false;
			}
		}
		return true;
	}

	return false;
}