#pragma once
#include "Piece.h"

// Class này thể hiện bàn cờ
class Board
{
private:
	Piece* board[8][8]; // Mảng 8x8 các con trỏ Piece thể hiện bàn cờ
	char turn; // Lượt đi của màu nào ('w' hoặc 'b')
public:
	Board();
	void move(Pos moveFromPos, Pos moveToPos); // Di chuyển quân cờ từ ô nguồn đến ô đích
	void play(); // Chọn quân, xuất nước đi, di chuyển
	void draw(); // Vẽ bàn cờ
};

