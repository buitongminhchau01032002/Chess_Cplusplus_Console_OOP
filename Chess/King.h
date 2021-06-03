#pragma once
#include "Piece.h"
class King : public Piece {
public:
	King();
	King(char color);
	King(char color, Pos pos);
};

