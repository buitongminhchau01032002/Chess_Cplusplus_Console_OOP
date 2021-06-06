﻿#pragma once
#include "Piece.h"

// Class này thể hiện bàn cờ
class Board
{
private:
	Piece*** board; // Mảng 8x8 các con trỏ Piece thể hiện bàn cờ
	char turn; // Lượt đi của màu nào ('w' hoặc 'b')
	int numOfMoves; // Tổng số nước đi
public:
	Board();
	void move(Pos moveFromPos, Pos moveToPos); // Di chuyển quân cờ từ ô nguồn đến ô đích
	void play(); // Chọn quân, xuất nước đi, di chuyển
	void draw(); // Vẽ bàn cờ
	bool isControlled(Pos pos); // Kiểm tra ô có bị kiểm soát bởi quân khác màu hay không
	bool isChecked(); // Kiểm tra người chơi có lượt đi đang bị chiếu hay không
	Piece*** getBoard();
};

