#include "King.h"


King::King() {
	this->type = 'K';
}
King::King(char color) {
	this->type = 'K';
	this->color = color;
}
King::King(char color, Pos pos) {
	this->type = 'K';
	this->color = color;
	this->pos = pos;
}
