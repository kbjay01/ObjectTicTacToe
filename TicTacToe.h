#pragma once
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cctype>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

enum PLAYER_TYPE { PL_CIRCLE = 'O', PL_CROSS = 'X', PL_UNKNOWN = '?' };
enum GAME_STATE { GS_NOTSTARTED, GS_STARTED, GS_MOVE, GS_WON, GS_DRAW};
enum FIELD {
	FLD_EMPTY,
	FLD_CIRCLE = PL_CIRCLE,
	FLD_CROSS = PL_CROSS
};

using std::string;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

class Game {
protected:
	GAME_STATE gameState;
public:
	Game() { gameState = GS_NOTSTARTED; }
	
	void SetGameState(GAME_STATE);
	void StartNewGame();
	void DrawHeader() const;
	GAME_STATE GetGameState() const;
	bool AskIfWantToPlayOnceAgain() const;
	
};

class Players{
private:
	string player1_name, player2_name; // names of player one, and player two
	PLAYER_TYPE Player1Char, Player2Char; // player but with assigned chars (circle, cross)

protected:
	PLAYER_TYPE CurrentPlayerSign; // sign of player that currently makes a move
	string current_player_name; // name of current player

public:
	Players(); // Constructor

	PLAYER_TYPE GetCurrentPlayerSign() const; // return sign (char) of current player
	string GetCurrentPlayerName() const; // returns the name of current player
	void AskAndSetGivenNames(Game&); // asks users for their names and saves them to variables player1_name and player2_name
	void SetRandomSignToPlayerName(); // assigns chars to variables player1_char and player2_char
	void DrawWhosFirst(); // draw which player is going to start first
	void NextPlayer(); // changes player after move had without win or draw occured
};

class Map{
private:
	FIELD FieldMap[3][3];

public:
	Map(); // Constructor

	void DrawMap() const; // draws map into console
	void Move(const Players&, Game&); // requests fieldID from player, checks if move is possible, if so..moves
	bool const CheckIfSomeoneWon(Game&, const Players&); // checks if someone won
	bool const CheckIfDrawOccured(Game&); // checks if draw occured
};
