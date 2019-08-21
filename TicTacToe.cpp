#include "TicTacToe.h"

//**GAME**
void Game::StartNewGame() {
	GameState = GS_STARTED;
}

void Game::DrawHeader() {
	system("cls");
	std::cout << "     Objective TicTacToe     " << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "" << std::endl;
}

void Game::PauseUntilKeyIsPressed() {
	_getch();
}

// *********************
// **PLAYERS**
// *********************
std::string Players::GetPlayerName(__int8 nameID){
	return (nameID == 1 ? player1_name : player2_name);
}

PLAYER_TYPE Players::GetPlayerChar(__int8 nameID) {
	return (nameID == 1 ? Player1Char : Player2Char);
}

void Players::AskAndSetGivenNames() {

	Game::GameState = GS_STARTED;
	std::cout << "Enter player1 name: ";
	std::cin >> player1_name;
	std::cout << "Enter player2 name: ";
	std::cin >> player2_name;
	std::cout << std::endl;
}

void Players::SetRandomSignToPlayerName() {

	srand(static_cast<uint>(time(NULL)));
	Player1Char = rand() % 2 == 0 ? PL_CIRCLE : PL_CROSS;
	Player1Char == PL_CIRCLE ? Player2Char = PL_CROSS : PL_CIRCLE;
}
 
void Players::DrawWhosFirst() {
	CurrentPlayer = rand() % 2 == 0 ? PL_CIRCLE : PL_CROSS;
}

void Players::NextPlayer() {
	CurrentPlayer = (CurrentPlayer == PL_CIRCLE ? PL_CROSS : PL_CIRCLE);
}


// **********************
// **MAP**
// *********************

// Constructor
Map::Map() : Lines{

	{ { 0,0 }, { 0,1 }, { 0,2 } }, // top horizontal
	{ { 1,0 }, { 1,1 }, { 1,2 } },// mid vertcal
	{ { 2,0 }, { 2,1 }, { 2,2 } },// bottom horizontal
	{ { 0,0 }, { 1,0 }, { 2,0 } }, // left vertcal
	{ { 0,1 }, { 1,1 }, { 2,1 } }, // mid vertcal
	{ { 0,2 }, { 1,2 }, { 2,2 } }, // right vertcal
	{ { 0,0 }, { 1,1 }, { 2,2 } }, // right backslash
	{ { 2,0 }, { 1,1 }, { 0,2 } } } // right slash 

{
	for (char i = 0; i < 3; i++) {
		for (char j = 0; j < 3; j++) {
			// Filling whole array with FLD_EMPTY values
			FieldMap[i][j] = FLD_EMPTY;
		}
	}
}

void Map::DrawMap() {

	for (uchar i = 0; i < 3; ++i) {
		// Left frame
		std::cout << " |";

		// Line
		for (uchar j = 0; j < 3; ++j) {
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

bool Map::CheckIfMoveIsLegalAndMove(uchar fieldID) {

	Game::GameState = GS_MOVE;
	// if field is not in correct range -> break function
	if (!(fieldID >= 1 && fieldID <= 9)) return false;

	// Calculate field cordinates
	uint x = (fieldID - 1) / 3;
	uint y = (fieldID - 1) % 3;

	// Check if field can be taken
	if (FieldMap[x][y] == FLD_EMPTY) {
		FieldMap[x][y] = static_cast<FIELD>(Players::CurrentPlayer);
		return true;
	}
	else return false; // Impossible
}

bool Map::CheckIfSomeoneWon() {

	FIELD Field, CorrectField;
	uchar correct_field_counter;
	for (uchar i = 0; i < 8; ++i)
	{
		// i iterates every possible line (there's 8 of them)
		// setting default values to variables
		Field = CorrectField = FLD_EMPTY;
		correct_field_counter = 0;
		for (uchar j = 0; j < 3; ++j)
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
			Game::GameState = GS_WON;
			// break loop and function
			return true;
		}
	}
	return false;
}

bool Map::CheckIfDrawOccured() {

	uchar amount_Of_Filled_Fields = 0;
	for (uchar i = 0; i <= 3; i++) {
		for (uchar j = 0; j < 3; j++) {
			if (FieldMap[i][j] != FLD_EMPTY) {
				++amount_Of_Filled_Fields;
			}
		}
	}
	if (amount_Of_Filled_Fields == 9) {
		Game::GameState = GS_DRAW;
		return true; // draw occured -> exit
	}
	return false; // draw did not occured -> go back to game
}
