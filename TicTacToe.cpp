#include "TicTacToe.h"

//**GAME**
void Game::StartGame() {
	GameState = GS_STARTED;
}

// *********************
// **PLAYERS**
// *********************
String Players::getPlayerName(__int8 nameID){
	return (nameID == 1 ? player1_name : player2_name);
}

void Players::AskAndSetGivenNames() {

	Game::GameState = GS_STARTED;
	std::cout << "Enter player1 (circle) name: ";
	std::cin >> player1_name;
	std::cout << "Enter player2 (cross) name: ";
	std::cin >> player2_name;
}

void Players::SetRandomSignToPlayerName() {

	srand(static_cast<uint>(time(NULL)));
	player1_char = rand() % 2 == 0 ? PL_CIRCLE : PL_CROSS;
	player1_char == PL_CIRCLE ? player2_char = PL_CROSS : PL_CIRCLE;
}
 
void Players::DrawWhosFirst() {
	current_player = rand() % 2 == 0 ? PL_CIRCLE : PL_CROSS;
}

void Players::NextPlayer() {
	current_player = (current_player == PL_CIRCLE ? PL_CROSS : PL_CIRCLE);
}

// **********************
// **MAP**
// *********************

// Constructor
Map::Map() : LINES{

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
			FIELD_MAP[i][j] = FLD_EMPTY;
		}
	}	
}

void Map::DrawHeaderAndMap() {

	// *HEADER*
	std::cout << "     Objective TicTacToe     " << std::endl;
	std::cout << "-----------------------------" << std::endl;
	std::cout << "" << std::endl;

	// *BODY*

	for (uchar i = 0; i < 3; ++i) {
		// Left frame
		std::cout << " |";

		// Line
		for (uchar j = 0; j < 3; ++j) {
			if (FIELD_MAP[i][j] == FLD_EMPTY) {
				// field ID
				std::cout << i * 3 + j + 1;
			}
			else {
				std::cout << static_cast<char>(FIELD_MAP[i][j]);
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
	if (FIELD_MAP[x][y] == FLD_EMPTY) {
		FIELD_MAP[x][y] = static_cast<FIELD>(Players::current_player);
		return true;
	}
	else return false; // Impossible
}

bool Map::CheckIfSomeoneWon() {

	FIELD Field, CorrectField;
	uchar CorrectFieldCounter;
	for (uchar i = 0; i < 8; ++i)
	{
		// i iterates every possible line (there's 8 of them)
		// setting default values to variables
		Field = CorrectField = FLD_EMPTY;
		CorrectFieldCounter = 0;
		for (uchar j = 0; j < 3; ++j)
		{
			// j iterates every 3 fields in every line
			// We're getting field
			Field = FIELD_MAP[LINES[i][j][0]][LINES[i][j][1]];
			// if checked field is diffrent than correct field...
			if (Field != CorrectField)
			{
				// set correct field to current field
				CorrectField = Field;
				CorrectFieldCounter = 1;
			}
			else
				// if both fields are equal
				// increment CorrectFieldCounter
				++CorrectFieldCounter;
		}
		// check if whole line is winnable
		if (CorrectFieldCounter == 3 && CorrectField != FLD_EMPTY)
		{
			// if yes, set GameState to Won
			Game::GameState = GS_WON;
			// break loop and function
			return true;
		}
	}
}

bool Map::CheckIfDrawOccured() {

	uchar amount_Of_Filled_Fields = 0;
	for (uchar i = 0; i <= 3; i++) {
		for (uchar j = 0; j < 3; j++) {
			if (FIELD_MAP[i][j] != FLD_EMPTY) {
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
