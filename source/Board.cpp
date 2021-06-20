#include "Board.h"
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
	numOfMovesToDraw = 0;
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

// Destructor
Board::~Board() {
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			delete board[i][j];
	for (int i = 0; i < 8; i++)
		delete[] board[i];
	delete[] board;
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
			board[moveToPos.getRow()][5]->setPos(Pos(moveToPos.getRow(), 5));
			board[moveToPos.getRow()][5]->addNumOfMoves();
			board[moveFromPos.getRow()][7] = NULL;
		}
		if (moveToPos.getCol() == 2) { // Nhập thành dài
			board[moveToPos.getRow()][3] = board[moveFromPos.getRow()][0];
			board[moveToPos.getRow()][3]->setPos(Pos(moveToPos.getRow(), 3));
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
	if (board[posTo.getRow()][posTo.getCol()] == NULL) // Kiểm tra có bắt quân hay không
		numOfMovesToDraw++;
	else
		numOfMovesToDraw = 0;
	this->move(posFrom, posTo); // Di chuyển
	this->promote(posTo); // Phong cấp
	if (turn == 'w') // Đổi lượt đi
		turn = 'b';
	else
		turn = 'w';
}

// Vẽ bàn cờ
void Board::draw() {
	system("cls");
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
	if (board[pos.getRow()][pos.getCol()]->getType() == 'P')
	{
		if (pos.getRow() == 0 || pos.getRow() == 7)
		{
			int n = 0;
			do {
				cout << "\nChon quan co muon phong cap: ";
				cout << "\n1) Phong cap thanh Hau";
				cout << "\n2) Phong cap thanh Xe";
				cout << "\n3) Phong cap thanh Ma";
				cout << "\n4) Phong cap thanh Tuong";
				cout << "\nChon: ";
				cin >> n;
			} while (n != 1 && n != 2 && n != 3 && n != 4);
			cin.ignore();
			delete board[pos.getRow()][pos.getCol()];
			switch (n)
			{
			case 1: 
				board[pos.getRow()][pos.getCol()] = new Queen(turn, Pos(pos.getRow(),pos.getCol()));
				break;
			case 2:
				board[pos.getRow()][pos.getCol()] = new Rook(turn, Pos(pos.getRow(), pos.getCol()));
				break;
			case 3:
				board[pos.getRow()][pos.getCol()] = new Knight(turn, Pos(pos.getRow(), pos.getCol()));
				break;
			case 4:
				board[pos.getRow()][pos.getCol()] = new Bishop(turn, Pos(pos.getRow(), pos.getCol()));
				break;
			default:
				break;
			}
		}
	}
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

bool Board::isCheckmated() {
	if (!this->isChecked())
		return false;
	for (int fromRow = 0; fromRow < 8; fromRow++)
		for (int fromCol = 0; fromCol < 8; fromCol++)
			if (board[fromRow][fromCol] != NULL)
				if (board[fromRow][fromCol]->getColor() == turn)
					for (int toRow = 0; toRow < 8; toRow++)
						for (int toCol = 0; toCol < 8; toCol++)
							if (board[fromRow][fromCol]->validateMove(board, Pos(toRow, toCol)) == true) {
								bool isReturnFalse = false;
								// Di chuyển thử
								Piece*** t = this->getBoard(); // t copy lại board
								this->move(Pos(fromRow, fromCol), Pos(toRow, toCol));
								if (!this->isChecked()) { // Hợp lệ (không bị chiếu)
									isReturnFalse = true;
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

								if (isReturnFalse)
									return false;
							}
							return true;
}

bool Board::isDraw() {
	// Hoà khi đi đủ 50 nước không bắt quân
	if (numOfMovesToDraw == 50)
		return true;

	// Hoà khi không đủ lực lượng chiếu hết
	// vua và vua+tượng, vua và vua+mã
	int Nw = 0;
	int Nb = 0;
	int Bw = 0;
	int Bb = 0;
	bool isBreak;
	for (int i = 0; i < 8; i++) {
		isBreak = false;
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != NULL) {
				// Xuất hiện quân khác ngoài Mã, Tượng, Vua
				if (board[i][j]->getType() != 'N' && board[i][j]->getType() != 'B' && board[i][j]->getType() != 'K')
					isBreak = true;
				// Cộng thêm các quân là mã, tượng
				if (board[i][j]->getType() == 'N' && board[i][j]->getColor() == 'w')
					Nw++;
				if (board[i][j]->getType() == 'N' && board[i][j]->getColor() == 'b')
					Nb++;
				if (board[i][j]->getType() == 'B' && board[i][j]->getColor() == 'w')
					Bw++;
				if (board[i][j]->getType() == 'B' && board[i][j]->getColor() == 'b')
					Bb++;

				if (Nw+Bw == 2 || Nb+Bb == 2)
					isBreak = true;
			}
			if (isBreak)
				break;
		}
		if (isBreak)
			break;
	}
	if (Nw+Bw <= 1 && Nb+Bb <= 1 && !isBreak)
		return true;

	// Hoà do hết nước đi, vua không bị chiếu
	if (!this->isChecked()) {
		for (int fromRow = 0; fromRow < 8; fromRow++)
			for (int fromCol = 0; fromCol < 8; fromCol++)
				if (board[fromRow][fromCol] != NULL)
					if (board[fromRow][fromCol]->getColor() == turn)
						for (int toRow = 0; toRow < 8; toRow++)
							for (int toCol = 0; toCol < 8; toCol++)
								if (board[fromRow][fromCol]->validateMove(board, Pos(toRow, toCol)) == true) {
									bool isReturnFalse = false;
									// Di chuyển thử
									Piece*** t = this->getBoard(); // t copy lại board
									this->move(Pos(fromRow, fromCol), Pos(toRow, toCol));
									if (!this->isChecked()) { // Hợp lệ (không bị chiếu)
										isReturnFalse = true;
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

									if (isReturnFalse)
										return false;
								}
								return true;
	} else
		return false;
}

bool Board::endGame() {
	if (this->isCheckmated()) {
		if (this->turn == 'w')
			cout << "DEN THANG" << endl;
		else
			cout << "TRANG THANG" << endl;
		return true;
	}
	if (this->isDraw()) {
		cout << "HOA CO" << endl;
		return true;
	}
	return false;
}
