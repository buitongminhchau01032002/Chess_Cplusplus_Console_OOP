#include <iostream>
#include "Board.h"
using namespace std;

int main () {
	bool quit = false;
	while (!quit) {
		Board b;
		while (!b.endGame()) {
			b.draw();
			b.play();
		}
		int choose = 1;
		do {
		cout << "Ban muon choi lai? (1: choi lai, 2: thoat): ";
		cin >> choose;
		cin.ignore();
		if (choose == 2)
			quit = true;
		} while (choose != 1 && choose != 2);
	}
	return 0;
}