#include "TicTacToe.h"

//**GAME**

void Game::SetGameState(GAME_STATE newGameState) {
	gameState = newGameState;
}

void Game::StartNewGame() {
	SetGameState(GS_STARTED);
}

void Game::DrawHeader() const{
	system("cls");
	std::cout << "     Objective TicTacToe     " << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "" << std::endl;
}

GAME_STATE Game::GetGameState() const{
	return gameState;
}

// *********************
// **PLAYERS**
// *********************

// Players Constructor
Players::Players() {
	player1_name, player2_name = "NO_NAME";
	Player1Char, Player2Char = PL_UNKNOWN;
	current_player_name = "UNKNOWN_NAME";
	CurrentPlayerSign = PL_UNKNOWN;
}

PLAYER_TYPE Players::GetCurrentPlayerSign() const {
	return CurrentPlayerSign;
}

string Players::GetCurrentPlayerName() const {
	return current_player_name;
}

void Players::AskAndSetGivenNames(Game &GameObject) {

	GameObject.SetGameState(GS_STARTED);
	std::cout << "Enter player1 name: ";
	std::cin >> player1_name;
	std::cout << "Enter player2 name: ";
	std::cin >> player2_name;
}

void Players::SetRandomSignToPlayerName() {

	srand(static_cast<int>(time(NULL)));
	Player1Char = rand() % 2 == 0 ? PL_CIRCLE : PL_CROSS;
	Player1Char == PL_CIRCLE ? Player2Char = PL_CROSS : PL_CIRCLE;
}

void Players::DrawWhosFirst() {
	CurrentPlayerSign = rand() % 2 == 0 ? PL_CIRCLE : PL_CROSS;
	current_player_name = (Player1Char == CurrentPlayerSign ? player1_name : player2_name);
}

void Players::NextPlayer() {
	CurrentPlayerSign = (CurrentPlayerSign == PL_CIRCLE ? PL_CROSS : PL_CIRCLE);
	current_player_name = (Player1Char == CurrentPlayerSign ? player1_name : player2_name);
}


// **********************
// **MAP**
// *********************

// Map Constructor
Map::Map() {
	for (char i = 0; i < 3; ++i) {
		for (char j = 0; j < 3; ++j) {
			FieldMap[i][j] = FLD_EMPTY;
		}
	}
}
void Map::DrawMap() const {
	std::cout << " -----" << std::endl;
	for (int i = 0; i < 3; ++i) {
		// Left frame
		std::cout << " |";

		// Line
		for (int j = 0; j < 3; ++j) {
			if (FieldMap[i][j] == FLD_EMPTY) {
				// field ID
				std::cout << i * 3 + j + 1;
			}
			else {
				std::cout << static_cast<char>(FieldMap[i][j]);
			}
		}
		// Right frame
		std::cout << "|" << std::endl;
	}
	std::cout << " -----" << std::endl;
	std::cout << std::endl;
}

void Map::Move(Players &PlayersObject, Game &GameObject ) {
	GameObject.SetGameState(GS_MOVE);

	char fieldID = 0;
	int x, y = 0;

	std::cout <<  PlayersObject.GetCurrentPlayerName() << " enter ID of field where" << std::endl;
	std::cout << "You want place " << static_cast<char>(PlayersObject.GetCurrentPlayerSign())<< ": ";

	do {
		fieldID = getchar() -'0';
		// Get fieldID until it will be correct		
	} while (!(fieldID >= 1 && fieldID <= 9));
		// Calculate field cordinates
		x = (fieldID - 1) / 3;
		y = (fieldID - 1) % 3;

		// Check if field can be taken
		if (FieldMap[x][y] == FLD_EMPTY) {
			FieldMap[x][y] = static_cast<FIELD>(PlayersObject.GetCurrentPlayerSign());
		}
}

bool const Map::CheckIfSomeoneWon(Game& GameObj, Players& PlayersObj) {
	PLAYER_TYPE currentPlayer = PlayersObj.GetCurrentPlayerSign();

	while (true) {
		// checking all horizontal possibilities
		if ((FieldMap[0][0] == currentPlayer && FieldMap[0][1] == currentPlayer) && FieldMap[0][2] == currentPlayer) break;
		if ((FieldMap[1][0] == currentPlayer && FieldMap[1][1] == currentPlayer) && FieldMap[1][2] == currentPlayer) break;
		if ((FieldMap[2][0] == currentPlayer && FieldMap[2][1] == currentPlayer) && FieldMap[2][2] == currentPlayer) break;

		// checking all vertival possibilities
		if ((FieldMap[0][0] == currentPlayer && FieldMap[1][0] == currentPlayer) && FieldMap[2][0] == currentPlayer) break;
		if ((FieldMap[0][1] == currentPlayer && FieldMap[1][1] == currentPlayer) && FieldMap[2][1] == currentPlayer) break;
		if ((FieldMap[0][2] == currentPlayer && FieldMap[1][2] == currentPlayer) && FieldMap[2][2] == currentPlayer) break;

		// checking two other possibilities
		if ((FieldMap[0][0] == currentPlayer && FieldMap[1][1] == currentPlayer) && FieldMap[2][2] == currentPlayer) break;
		if ((FieldMap[0][2] == currentPlayer && FieldMap[1][1] == currentPlayer) && FieldMap[2][0] == currentPlayer) break;
		return false;
	}
	GameObj.SetGameState(GS_WON);
	GameObj.DrawHeader();
	DrawMap();
	std::cout << PlayersObj.GetCurrentPlayerName() << " WON!" << std::endl;
	return true; // win occured -> exit
}

bool const Map::CheckIfDrawOccured(Game &GameObject) {

	int amount_of_filled_fields = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (FieldMap[i][j] != FLD_EMPTY) {
				++amount_of_filled_fields;
			}
		}
	}
	if (amount_of_filled_fields == 9) {
		GameObject.SetGameState(GS_DRAW);
		GameObject.DrawHeader();
		DrawMap();
		std::cout << std::endl << "DRAW. None of players won";
		return true; // draw occured -> exit
	}
	return false; // draw did not occured -> go back to game
}
