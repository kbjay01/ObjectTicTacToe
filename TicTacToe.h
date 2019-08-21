#pragma once
#include <iostream>
#include <ctime>
#include <conio.h>
#include <vector>

typedef unsigned char uchar;
typedef unsigned int uint;
typedef std::vector<std::vector<FIELD>> Field3DVector;
typedef std::vector<std::vector<std::vector<uchar>>> Uchar3DVector;
using std::string;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

enum PLAYER_TYPE{ PL_CIRCLE = 'O', PL_CROSS = 'X', PL_NOTSIGNED };
enum GAME_STATE { GS_NOTSTARTED, GS_STARTED, GS_MOVE, GS_WON, GS_DRAW, GS_ENDED };
enum FIELD {
	FLD_EMPTY,
	FLD_CIRCLE = PL_CIRCLE,
	FLD_CROSS = PL_CROSS
};
 

class Game {
protected:
	GAME_STATE GameState;
public:
	Game() { GameState = GS_NOTSTARTED; }
	~Game() { GameState = GS_ENDED; }

	void StartNewGame();
	void DrawHeader();
	void PauseUntilKeyIsPressed();
	
};

class Players : public Game{
private:
	std::string player1_name, player2_name; // names of player one, and player two
	PLAYER_TYPE Player1Char, Player2Char; // player but with assigned chars (circle, cross)

protected:
	PLAYER_TYPE CurrentPlayer; // sign of player that currently makes a move

public:
	Players() { // Constructor
		player1_name = player2_name = "NO_NAME";
		Player1Char = Player2Char = PL_NOTSIGNED;
	}

	std::string GetPlayerName(__int8 nameID); // returns name of specific player
	PLAYER_TYPE GetPlayerChar(__int8 nameID); // returns char of specific player
	void AskAndSetGivenNames(); // asks users for their names and saves them to variables player1_name and player2_name
	void SetRandomSignToPlayerName(); // assigns chars to variables player1_char and player2_char
	void DrawWhosFirst(); // draw which player is going to start first
	void NextPlayer(); // changes player after move had without win or draw occured
};

class Map : public Players{
private:
	Field3DVector FieldMap;
	const Uchar3DVector Lines;
	
public:
	void DrawMap(); // Draws map into console
	bool CheckIfMoveIsLegalAndMove(uchar); // checks if outsourced move is possible, if so makes the move
	bool CheckIfSomeoneWon(); // checks if someone won
	bool CheckIfDrawOccured(); // checks if draw occured
	
	Map();
};

