#include <iostream>
#include <conio.h>
#include "gejm.h"


int main() {
	startGame();

	while (true) {
		drawFields();

		if (GameState == GS_MOVE) {
			uchar fieldID;
			std::cin >> fieldID;
			move(fieldID - '0');
		}

		if (GameState == GS_WON || GameState == GS_DRAW) {
			drawFields();
			break;
		}
	}
	return _getch();
}