#pragma once
#include "Pos.h"

// Class này thể hiện tổng quát các quân cờ
class Piece
{
protected:
	char type; // Kí hiệu quân cờ
	char color; // Màu quân cờ ('w' hoặc 'b')
	Pos pos; // vị trí quân cờ
	int numOfMoves; // Số lượng nước mà quân cờ đã đi
public:
	char getColor();
	char getType();
	virtual bool validateMove(Piece* board[8][8], Pos moveToPos) = 0; // Kiểm tra di chuyển hợp lệ hay không
	void setPos(Pos pos);
	void addNumOfMoves();
	int getNumOfMoves();
};

