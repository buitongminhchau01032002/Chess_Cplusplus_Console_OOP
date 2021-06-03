#pragma once
#include "Piece.h"

// Quân xe
class Rock : public Piece {
public:
	Rock();
	Rock(char color);
	Rock(char color, Pos pos);
	bool validateMove(Piece* board[8][8], Pos moveToPos);
};

