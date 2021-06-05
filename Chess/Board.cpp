#include "Board.h"
#include "Rock.h"
#include "King.h"
#include "Pos.h"
#include <iostream>
#include <string>
using namespace std;

// Tạo bàn cờ ban đầu
Board::Board() {
	turn = 'w';
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = NULL;

	// Test những quân xe
	board[0][0] = new Rock('w', Pos(0, 0));
	board[0][7] = new Rock('w', Pos(0, 7));
	board[7][0] = new Rock('b', Pos(7, 0));
	board[7][7] = new Rock('b', Pos(7, 7));
}


// Di chuyển quân cờ
// Thay đổi các quân cờ trên board và đổi lượt đi
void Board::move(Pos moveFromPos, Pos moveToPos) {
	
	// Chèn quân ở ô đích
	if (board[moveToPos.getRow()][moveToPos.getCol()] != NULL)
		delete board[moveToPos.getRow()][moveToPos.getCol()];
	board[moveToPos.getRow()][moveToPos.getCol()] = board[moveFromPos.getRow()][moveFromPos.getCol()];
	board[moveToPos.getRow()][moveToPos.getCol()]->setPos(moveToPos);
	board[moveToPos.getRow()][moveToPos.getCol()]->addNumOfMoves();


	// Xoá quân ở ô nguồn
	board[moveFromPos.getRow()][moveFromPos.getCol()] = NULL;
	
	// Đổi lượt đi
	if (turn == 'w')
		turn = 'b';
	else
		turn = 'w';
}


void Board::play () {
	Pos posFrom;
	Pos posTo;
	
	// Chọn vị trí quân cờ
	do {
		if (turn == 'w')
			cout << "TRANG DI" << endl;
		else
			cout << "DEN DI" << endl;
		cout << "Chon vi tri quan co: ";
		posFrom.intput();

	} while(
		posFrom == Pos(-1, -1) ||
		board[posFrom.getRow()][posFrom.getCol()] == NULL ||
		board[posFrom.getRow()][posFrom.getCol()]->getColor() != turn
	);


	// Xuất các vị trí di chuyển hợp lệ
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			posTo = Pos(i, j);
			if (board[posFrom.getRow()][posFrom.getCol()]->validateMove(board, posTo) == true) {
				posTo.output();
				cout << endl;
			}
		}
	}

	// Di chuyển
	do {
		cout << "Chon vi tri di chuyen: ";
		posTo.intput();
	} while (
		posTo == Pos(-1, -1) ||
		board[posFrom.getRow()][posFrom.getCol()]->validateMove(board, posTo) == false
	);
	this->move(posFrom, posTo);
}

// Vẽ bàn cờ
void Board::draw() {
	cout << "   -------------------------" << endl;
	for (int i = 7; i >= 0; i--) {
		cout << " " << Pos(i, 1).toString()[1] << " |";
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != NULL)
				cout << board[i][j]->getType() << board[i][j]->getColor() << "|";
			else
				cout << "  |";
		}
		cout << endl  << "   -------------------------" << endl;
	}
	cout << "    a  b  c  d  e  f  g  h" << endl;
}