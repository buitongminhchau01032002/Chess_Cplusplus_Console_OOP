#pragma once
#include "Piece.h"

// Qu�n xe
class Rook : public Piece {
public:
	Rook();
	Rook(char color);
	Rook(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};

