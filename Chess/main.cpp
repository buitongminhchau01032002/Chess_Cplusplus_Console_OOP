#include <iostream>
#include "Board.h"
using namespace std;

int main () {
	Board b;
	while (true) {
		b.draw();
		b.play();
	}
	return 0;
}