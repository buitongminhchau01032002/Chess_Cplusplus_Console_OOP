#pragma once
#include "Piece.h"

// Quân xe
class Rook : public Piece {
public:
	Rook();
	Rook(char color);
	Rook(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};

