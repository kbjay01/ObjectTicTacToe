#include "TicTacToe.h"

//**GAME**

void Game::SetGameState(GAME_STATE newGameState) {
	gameState = newGameState;
}

void Game::StartNewGame() {
	gameState = GS_STARTED;
}

void Game::DrawHeader() {
	system("cls");
	std::cout << "     Objective TicTacToe     " << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "" << std::endl;
}

void Game::Pause() {
	_getch;
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

PLAYER_TYPE Players::GetCurrentPlayerSign() {
	return CurrentPlayerSign;
}

string Players::GetCurrentPlayerName() {
	return current_player_name;
}

void Players::AskAndSetGivenNames() {

	Game::gameState = GS_STARTED;
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
Map::Map() : Lines {

	{ { 0,0 }, { 0,1 }, { 0,2 } }, // top horizontal
	{ { 1,0 }, { 1,1 }, { 1,2 } },// mid vertcal
	{ { 2,0 }, { 2,1 }, { 2,2 } },// bottom horizontal
	{ { 0,0 }, { 1,0 }, { 2,0 } }, // left vertcal
	{ { 0,1 }, { 1,1 }, { 2,1 } }, // mid vertcal
	{ { 0,2 }, { 1,2 }, { 2,2 } }, // right vertcal
	{ { 0,0 }, { 1,1 }, { 2,2 } }, // right backslash
	{ { 2,0 }, { 1,1 }, { 0,2 } } } // right slash 
	{
	for (char i = 0; i < 3; ++i) {
		for (char j = 0; j < 3; ++j) {
			FieldMap[i][j] = FLD_EMPTY;
		}
	}
}
void Map::DrawMap() {

	for (char i = 0; i < 3; ++i) {
		// Left frame
		std::cout << " |";

		// Line
		for (char j = 0; j < 3; ++j) {
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

void Map::TryToMakeAMove(Players &PlayersObject, Game &GameObject ) {
	GameObject.SetGameState(GS_MOVE);

	bool can_field_be_taken = false;
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
			can_field_be_taken = true;
		}
}

bool Map::CheckIfSomeoneWon(Game &GameObject) {

	FIELD Field, CorrectField;
	char correct_field_counter;
	for (char i = 0; i < 8; ++i)
	{
		// i iterates every possible line (there's 8 of them)
		// setting default values to variables
		Field = CorrectField = FLD_EMPTY;
		correct_field_counter = 0;
		for (char j = 0; j < 3; ++j)
		{
			// j iterates every 3 fields in every line
			// We're getting field
			Field = FieldMap[Lines[i][j][0]][Lines[i][j][1]];
			// if checked field is diffrent than correct field...
			if (Field != CorrectField)
			{
				// set correct field to current field
				CorrectField = Field;
				correct_field_counter = 1;
			}
			else
				// if both fields are equal
				// increment CorrectFieldCounter
				++correct_field_counter;
		}
		// check if whole line is winnable
		if (correct_field_counter == 3 && CorrectField != FLD_EMPTY)
		{
			// if yes, set GameState to Won
			GameObject.SetGameState(GS_WON);
			std::cout << std::endl << "DRAW, None of players won";
			// break loop and function
			return true;
		}
	}
	return false;
}

bool Map::CheckIfDrawOccured(Game &GameObject) {

	char amount_of_filled_fields = 0;
	for (char i = 0; i <= 3; i++) {
		for (char j = 0; j < 3; j++) {
			if (FieldMap[i][j] != FLD_EMPTY) {
				++amount_of_filled_fields;
			}
		}
	}
	if (amount_of_filled_fields == 9) {
		GameObject.SetGameState(GS_DRAW);
		std::cout << std::endl << "DRAW. None of players won";
		GameObject.Pause();
		return true; // draw occured -> exit
	}
	return false; // draw did not occured -> go back to game
}
