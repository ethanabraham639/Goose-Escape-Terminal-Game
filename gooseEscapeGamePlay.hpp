					 /* START of gooseEscapeGamePlay.hpp */

#ifndef GOOSE_ESCAPE_GAMEPLAY
#define GOOSE_ESCAPE_GAMEPLAY
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"

/*This file is all about the game world.  You will modify this to add
    constants and function prototypes.  Modify gooseGamePlay.cpp to
	actually add functionality.
*/

/*
    Declare constants to indicate various game world features in the board
    array.  Modify them to fit what you would like to do in the game.  You can
    change the type if you choose to store your game board as something other
    than intengers.
*/	
// Going further:  Learn how to use an enum for these values
const int EMPTY = 0;
const int SHALL_NOT_PASS = 1;
const int WINNER = 2;
const int POWER_UP = 3;
const int COIN = 4;

/*
    A few examples of characters both for actors and for the game board
    itself are shown.
*/	
//display characters
const int PLAYER_CHAR = int('@');
const int MONSTER_CHAR = int('G');
const int WALL_CHAR = int('o');
const int WIN_CHAR = int('%'); //% sign, a special character used in "Rogue"
const int POWER_UP_CHAR = int('$');
const int COIN_CHAR = int('C');

/*
    Game play function prototypes are give below.
*/

// print the game board function protype

void createBoard(int game_map[MAX_BOARD_X][MAX_BOARD_Y]);

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/
bool captured(Actor const & player);

bool playerAttacked(Actor const & player, Actor const & monster);


//Function prototype for is the player has won/lost yet

bool player_safe(Actor const & player, int game_map[MAX_BOARD_X][MAX_BOARD_Y]);

/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/

void movePlayer(int key, Actor & player, int game_map[MAX_BOARD_X][MAX_BOARD_Y]);

/*
    What other functions do you need to make the game work?  What can you
    add to the basic functionality to make it more fun to play?
*/

//Function prototype for the movement of the goose

void gooseChase(Actor & player, Actor & monster,
				int game_map[MAX_BOARD_X][MAX_BOARD_Y]);
				
bool isPowerUpActive(int powerUpTurns);

void powerUpActivate(Actor const & player, int game_map[MAX_BOARD_X][MAX_BOARD_Y], int xMove, int yMove);

void wallBroken(Actor const & monster, int game_map[MAX_BOARD_X][MAX_BOARD_Y]);

void wall_trap(int game_map[MAX_BOARD_X][MAX_BOARD_Y]);


#endif

					  /* END of gooseEscapeGamePlay.hpp */
