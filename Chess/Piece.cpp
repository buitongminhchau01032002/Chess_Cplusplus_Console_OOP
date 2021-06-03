#include "Piece.h"

Piece::Piece(void) {

}
char Piece::getColor() {
	return color;
}
char Piece::getType() {
	return type;
}
void Piece::setPos(Pos pos) {
	this->pos = pos;
}

