#include "TicTacToe.h"

int main() {
	while (true) {
		Game game;
		Players players;
		Map map;

		game.StartNewGame();
		game.DrawHeader();

		players.AskAndSetGivenNames(game);

		players.SetRandomSignToPlayerName();
		players.DrawWhosFirst();

		while (true) {
			game.DrawHeader();
			map.DrawMap();
			map.Move(players, game);
			if (map.CheckIfSomeoneWon(game, players) == true) break;
			if (map.CheckIfDrawOccured(game) == true) break;
			players.NextPlayer();
		}
		bool oneMoreGame = game.AskIfWantToPlayOnceAgain();
		if (oneMoreGame == false) return 0;
	}
	return 0;
}
