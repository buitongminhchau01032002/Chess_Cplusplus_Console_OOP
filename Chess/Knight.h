#pragma once
#include "Piece.h"

// Qu�n m�
class Knight : public Piece {
public:
	Knight();
	Knight(char color);
	Knight(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};
