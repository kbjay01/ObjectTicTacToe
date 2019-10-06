#include "TicTacToe.h"

int main() {
	Game currentGame;
	Players player;
	Map currentMap;

	currentGame.StartNewGame();
	currentGame.DrawHeader();

	player.AskAndSetGivenNames(currentGame);

	player.SetRandomSignToPlayerName();
	player.DrawWhosFirst();
	
	while (true) {
		currentGame.DrawHeader();
		currentMap.DrawMap();
		currentMap.Move(player, currentGame);
		if (currentMap.CheckIfSomeoneWon(currentGame, player) == true) break;
		if(currentMap.CheckIfDrawOccured(currentGame) == true) break;
		player.NextPlayer();
	}
}
