﻿#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Pos.h"
#include <iostream>
#include <string>
using namespace std;

// Tạo bàn cờ ban đầu
Board::Board() {
	numOfMoves = 0;
	turn = 'w';
	board = new Piece**[8];
	for (int i = 0; i < 8; i++) {
		board[i] = new Piece*[8];
		for (int j = 0; j < 8; j++)
			board[i][j] = NULL;
	}
	
	board[0][4] = new King('w', Pos(0, 4));
	board[7][4] = new King('b', Pos(7, 4));

	board[0][0] = new Rook('w', Pos(0, 0));
	board[0][7] = new Rook('w', Pos(0, 7));
	board[7][0] = new Rook('b', Pos(7, 0));
	board[7][7] = new Rook('b', Pos(7, 7));

	board[0][1] = new Knight('w', Pos(0, 1));
	board[0][6] = new Knight('w', Pos(0, 6));
	board[7][1] = new Knight('b', Pos(7, 1));
	board[7][6] = new Knight('b', Pos(7, 6));

	board[0][2] = new Bishop('w', Pos(0, 2));
	board[0][5] = new Bishop('w', Pos(0, 5));
	board[7][2] = new Bishop('b', Pos(7, 2));
	board[7][5] = new Bishop('b', Pos(7, 5));

	board[0][3] = new Queen('w', Pos(0, 3));
	board[7][3] = new Queen('b', Pos(7, 3));

	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new Pawn('w', Pos(1, i));
		board[6][i] = new Pawn('b', Pos(6, i));
	}
}


// Di chuyển quân cờ
// Thay đổi các quân cờ trên board
void Board::move(Pos moveFromPos, Pos moveToPos) {
	
	// Chèn quân ở ô đích
	if (board[moveToPos.getRow()][moveToPos.getCol()] != NULL)
		delete board[moveToPos.getRow()][moveToPos.getCol()];
	board[moveToPos.getRow()][moveToPos.getCol()] = board[moveFromPos.getRow()][moveFromPos.getCol()];
	board[moveToPos.getRow()][moveToPos.getCol()]->setPos(moveToPos);
	board[moveToPos.getRow()][moveToPos.getCol()]->addNumOfMoves();


	// Xoá quân ở ô nguồn
	board[moveFromPos.getRow()][moveFromPos.getCol()] = NULL;

	// Di chuyển xe nếu nước đi là nhập thành
	if (board[moveToPos.getRow()][moveToPos.getCol()]->getType() == 'K' && moveFromPos.getCol() == 4) {
		if (moveToPos.getCol() == 6) { // Nhập thành ngắn
			board[moveToPos.getRow()][5] = board[moveFromPos.getRow()][7];
			board[moveToPos.getRow()][5]->setPos(moveToPos);
			board[moveToPos.getRow()][5]->addNumOfMoves();
			board[moveFromPos.getRow()][7] = NULL;
		}
		if (moveToPos.getCol() == 2) { // Nhập thành dài
			board[moveToPos.getRow()][3] = board[moveFromPos.getRow()][0];
			board[moveToPos.getRow()][3]->setPos(moveToPos);
			board[moveToPos.getRow()][3]->addNumOfMoves();
			board[moveFromPos.getRow()][0] = NULL;
		}
	}
}


void Board::play () {
	Pos posFrom;
	Pos posTo;
	bool hasValidateMove = false;
	while (!hasValidateMove) {
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

					// Di chuyển thử
					Piece*** t = this->getBoard(); // t copy lại board
					this->move(posFrom, posTo);

					if (!this->isChecked()) { // Hợp lệ (không bị chiếu)
						posTo.output();
						cout << endl;
						hasValidateMove = true;
					}

					// Giải phóng board, gán lại giá trị ở t
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++)
							delete board[i][j];
					}
					for (int i = 0; i < 8; i++)
						delete[] board[i];
					delete[] board;
					board = t;
				}
			}
		}
		// Kiểm tra nhập thành ngắn
		if (this->isCastlingShort(posFrom)) {
			Pos(posFrom.getRow(), 6).output();
			cout << endl;
			hasValidateMove = true;
		}

		// Kiểm tra nhập thành dài
		if (this->isCastlingLong(posFrom)) {
			Pos(posFrom.getRow(), 2).output();
			cout << endl;
			hasValidateMove = true;
		}
	}

	// Chọn vị trí di chuyển
	bool canMove = false; //
	do {
		cout << "Chon vi tri di chuyen: ";
		posTo.intput();
		if (!(posTo == Pos(-1, -1)) && board[posFrom.getRow()][posFrom.getCol()]->validateMove(board, posTo) == true) {
			// Di chuyển thử
			Piece*** t = this->getBoard(); // t copy lại board
			this->move(posFrom, posTo);

			if (!this->isChecked()) { // Hợp lệ (không bị chiếu)
				canMove = true;
			}

			// Giải phóng board, gán lại giá trị ở t
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++)
					delete board[i][j];
			}
			for (int i = 0; i < 8; i++)
				delete[] board[i];
			delete[] board;
			board = t;

		}
		// Kiểm tra nhập thành ngắn
		if (this->isCastlingShort(posFrom) && posTo.getRow()==posFrom.getRow() && posTo.getCol()==6)
			canMove = true;

		// Kiểm tra nhập thành dài
		if (this->isCastlingLong(posFrom) && posTo.getRow()==posFrom.getRow() && posTo.getCol()==2)
			canMove = true;
		
	} while (!canMove);
	this->move(posFrom, posTo); // Di chuyển
	this->promote(posTo); // Phong cấp
	numOfMoves++; // Tăng nước đi
	if (turn == 'w') // Đổi lượt đi
		turn = 'b';
	else
		turn = 'w';
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

bool Board::isControlled(Pos pos) {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] != NULL)
				if (turn != board[i][j]->getColor())
					if (board[i][j]->validateMove(board, pos))
						return true;
	return false;
}

bool Board::isChecked() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (board[i][j] != NULL)
				if (turn == board[i][j]->getColor())
					if (board[i][j]->getType() == 'K')
						if (this->isControlled(Pos(i, j)))
							return true;
	return false;
}

Piece*** Board::getBoard() {
	Piece*** t;
	t = new Piece**[8];
	for (int i = 0; i < 8; i++) {
		t[i] = new Piece*[8];
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == NULL)
				t[i][j] = NULL;
			else {
				if (board[i][j]->getType() == 'K')
					t[i][j] = new King(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'R')
					t[i][j] = new Rook(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'Q')
					t[i][j] = new Queen(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'N')
					t[i][j] = new Knight(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'B')
					t[i][j] = new Bishop(board[i][j]->getColor(), Pos(i, j));
				if (board[i][j]->getType() == 'P')
					t[i][j] = new Pawn(board[i][j]->getColor(), Pos(i, j));
				t[i][j]->setNumOfMoves(board[i][j]->getNumOfMoves());
			}
		}
	}
	return t;
}

void Board::promote(Pos pos) {
	
}

bool Board::isCastlingShort(Pos posFrom) {
	if (turn == 'w' && posFrom==Pos(0, 4) && board[0][4]!=NULL && board[0][7]!=NULL)
		if (board[0][4]->getType()=='K' && 
			board[0][7]->getType()=='R' &&
			board[0][4]->getNumOfMoves()==0 && 
			board[0][7]->getNumOfMoves()==0 &&
			board[0][5] == NULL &&
			board[0][6] == NULL &&
			!this->isControlled(Pos(0, 4)) &&
			!this->isControlled(Pos(0, 5)) &&
			!this->isControlled(Pos(0, 6))
			)
			return true;
	if (turn == 'b' && posFrom==Pos(7, 4) && board[7][4]!=NULL && board[7][7]!=NULL)
		if (board[7][4]->getType()=='K' && 
			board[7][7]->getType()=='R' &&
			board[7][4]->getNumOfMoves()==0 && 
			board[7][7]->getNumOfMoves()==0 &&
			board[7][5] == NULL &&
			board[7][6] == NULL &&
			!this->isControlled(Pos(7, 4)) &&
			!this->isControlled(Pos(7, 5)) &&
			!this->isControlled(Pos(7, 6))
			)
			return true;
	return false;
}
bool Board::isCastlingLong(Pos posFrom) {
	if (turn == 'w' && posFrom==Pos(0, 4) && board[0][4]!=NULL && board[0][0]!=NULL)
		if (board[0][4]->getType()=='K' && 
			board[0][0]->getType()=='R' &&
			board[0][4]->getNumOfMoves()==0 && 
			board[0][0]->getNumOfMoves()==0 &&
			board[0][1] == NULL &&
			board[0][2] == NULL &&
			board[0][3] == NULL &&
			!this->isControlled(Pos(0, 1)) &&
			!this->isControlled(Pos(0, 2)) &&
			!this->isControlled(Pos(0, 3)) &&
			!this->isControlled(Pos(0, 4))
			)
			return true;
	if (turn == 'b' && posFrom==Pos(7, 4) && board[7][4]!=NULL && board[7][0]!=NULL)
		if (board[7][4]->getType()=='K' && 
			board[7][0]->getType()=='R' &&
			board[7][4]->getNumOfMoves()==0 && 
			board[7][0]->getNumOfMoves()==0 &&
			board[7][1] == NULL &&
			board[7][2] == NULL &&
			board[7][3] == NULL &&
			!this->isControlled(Pos(7, 1)) &&
			!this->isControlled(Pos(7, 2)) &&
			!this->isControlled(Pos(7, 3)) &&
			!this->isControlled(Pos(7, 4))
			)
			return true;
	return false;
}