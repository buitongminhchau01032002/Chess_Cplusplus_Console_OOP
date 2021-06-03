#pragma once
#include <string>

// Class này thể hiện vị trí các quân cơ
class Pos {
private:
	int row;
	int col;
public:
	Pos();
	Pos(int, int);
	int getRow();
	int getCol();
	bool operator==(const Pos& posOther);
	static Pos toPos(std::string); // Chuyển từ kí hiệu trên bàn cờ sang dạng Pos
	std::string toString(); // Chuyển Pos sang kí hiệu
};
