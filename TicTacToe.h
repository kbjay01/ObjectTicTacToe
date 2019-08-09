#pragma once
#include <iostream>
#include <ctime>
#define String std::string
#define uchar unsigned char
#define uint unsigned int

enum PLAYER_TYPE{ PL_CIRCLE = 'O', PL_CROSS = 'X', PL_NOTSIGNED };
enum GAME_STATE { GS_NOTSTARTED, GS_STARTED, GS_MOVE, GS_WON, GS_DRAW, GS_ENDED };
enum FIELD {
	FLD_EMPTY,
	FLD_CIRCLE = PL_CIRCLE,
	FLD_CROSS = PL_CROSS
};
 

class Players{
private:
	String player1_name, player2_name; // names of player one, and player two
	PLAYER_TYPE player1_char, player2_char; // player but with assigned chars (circle, cross)

public:
	static PLAYER_TYPE current_player; // sign of player that currently makes a move

	Players() { // Constructor
		player1_name = player2_name = "NO_NAME";
		player1_char = player2_char = PL_NOTSIGNED;
	}

	String getPlayerName(__int8 nameID); // returns name of player one, or player two
	void askAndSaveGivenNames(); // asks users for their names and saves them to variables player1_name and player2_name
	void assignRandomSignToPlayerName(); // assigns chars to variables player1_char and player2_char
	void drawWhosFirst(); // draw which player is going to start first
	void nextPlayer(); // changes player after move had without win or draw occured
};

class Map{
private:
	FIELD field_map[3][3];
	uchar LINES[][3][2];
	
public:
	void drawHeaderAndMap(); // Draws map into console
	bool checkIfMoveIsLegalAndMove(uchar); // checks if outsourced move is possible, if so makes the move
	bool checkIfSomeoneWon(); // checks if someone won
	bool checkIfDrawOccured(); // checks if draw occured
	void createFieldMap(); // fils array named "field_map" with FIELD values
	void createLinesArray(); // fils array named "correct_lines" with correct/winnable lines
	
};

class Game {
public:
	static GAME_STATE GameState;
	Game() { GameState = GS_NOTSTARTED; }
	~Game() { GameState = GS_ENDED; }
};