#include "TicTacToe.h"

int main() {
	Game currentGame;
	Players player;
	Map currentMap;
	bool isGameOver = false;

	currentGame.StartNewGame();
	currentGame.DrawHeader();

	player.AskAndSetGivenNames(currentGame);

	player.SetRandomSignToPlayerName();
	player.DrawWhosFirst();

	while (isGameOver == false) {
		currentGame.DrawHeader();
		currentMap.DrawMap();
		currentMap.TryToMakeAMove(player, currentGame);
		isGameOver = currentMap.CheckIfSomeoneWon(currentGame, player);
		isGameOver = currentMap.CheckIfDrawOccured(currentGame);
		player.NextPlayer();
	}
}
