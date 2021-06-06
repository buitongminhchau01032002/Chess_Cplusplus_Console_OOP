#pragma once
#include "Piece.h"

// Quân tốt
class Pawn : public Piece {
public:
	Pawn();
	Pawn(char color);
	Pawn(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};


