#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop();
	Bishop(char color);
	Bishop(char color, Pos pos);
	bool validateMove(Piece*** board, Pos moveToPos);
};
