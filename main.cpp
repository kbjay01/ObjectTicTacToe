#include "TicTacToe.h"

int main() {
	Game CurrentGame;
	Players Player;
	Map CurrentMap;

	CurrentGame.StartNewGame();
	CurrentGame.DrawHeader();
	
	Player.AskAndSetGivenNames();
	
	Player.SetRandomSignToPlayerName();
	Player.DrawWhosFirst();

	CurrentGame.DrawHeader();
	CurrentMap.DrawMap();
	
}
