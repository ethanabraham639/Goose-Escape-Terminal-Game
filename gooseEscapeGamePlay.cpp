					/* START of gooseEscapeGamePlay.cpp */

#include <iostream>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

extern Console out;
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/
	
/*
    Print the game world
    
    The functions should draw characters to present features of the game
    board, e.g. win location, obstacles, power ups
*/

void createBoard(int game_map[MAX_BOARD_X][MAX_BOARD_Y])   // print the game board function
{
    terminal_put(WIN_START_X, WIN_START_Y, WIN_CHAR);
    
    for(int row = 0; row < MAX_BOARD_X; row++)
    {
    	for(int col = 0; col < MAX_BOARD_Y; col++)
    	{
    		if(game_map[row][col] == SHALL_NOT_PASS)
    		{
    			terminal_put(row, col, WALL_CHAR);
			}
		}
	}
	
	terminal_put(1, 1, POWER_UP_CHAR);
	terminal_put(5, 1, COIN_CHAR);
    
}

/*
    Do something when the goose captures the player
    
    If you want to attack or something else, this is the function you 
    need to change.  For example, maybe the two touch each other and
    then fight.  You could add a health to the Actor class that is
    updated.  Run, use weapons, it's up to you!
*/

bool captured(Actor const & player)
{
    return player.get_health() == 0;
}

bool playerAttacked(Actor const & player, Actor const & monster)
{
	return(player.get_x() == monster.get_x()
		   && player.get_y() == monster.get_y());
}

//This function tells us if the player has won or not

bool player_safe(Actor const & player, int game_map[MAX_BOARD_X][MAX_BOARD_Y])
{
	return(game_map[WIN_START_X][WIN_START_Y] == player.get_actorChar());
}
/*
    Move the player to a new location based on the user input.  You may want
    to modify this if there are extra controls you want to add.
    
    All key presses start with "TK_" then the character.  So "TK_A" is the a
    key being pressed.
    
    A look-up table might be useful.
    You could decide to learn about switch statements and use them here.
*/

bool coin_collected = false;

void movePlayer(int key, Actor & player, int game_map[MAX_BOARD_X][MAX_BOARD_Y])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
        
    powerUpActivate(player, game_map, xMove, yMove);
    
    if(game_map[player.get_x() + xMove][player.get_y() + yMove] == COIN)
    {
    	coin_collected = true;
    	wall_trap(game_map);
    	
	}
			
        
    if(game_map[player.get_x() + xMove][player.get_y() + yMove] == WINNER
	   && !coin_collected)
	{
		
	}	   
	
	else if (player.can_move(xMove, yMove) 
      &&  game_map[player.get_x() + xMove][player.get_y() + yMove] != SHALL_NOT_PASS)
    {
    	player.update_location(xMove, yMove);
	}    
	
    
}

/*
    What other functions do you need to make the game work?  What can you
    add to the basic functionality to make it more fun to play?
*/

int powerUpTurns = 0;

void powerUpActivate(Actor const & player, int game_map[MAX_BOARD_X][MAX_BOARD_Y], int xMove, int yMove)
{
	if(game_map[player.get_x() + xMove][player.get_y() + yMove] == POWER_UP)
	{
		powerUpTurns = POWER_UP_ACTIVE;
		out.writeLine("You got the POWER-UP! You froze the goose for TEN TURNS!");
	}
}

bool isPowerUpActive(int powerUpTurns)
{
	return powerUpTurns != 0;
}


int move_number = 0;

//Function to make the goose mildly follow the player

void gooseChase(Actor & player, Actor & monster, int game_map[MAX_BOARD_X][MAX_BOARD_Y])
{
	int yMove = 0, xMove = 0;
	
	//These first four condition set the goose's movement to be closer to the
	//current location of the player
	
	if (player.get_x() < monster.get_x())
        xMove = -1;

    else
    	xMove = 1;
    	
    if (player.get_y() < monster.get_y())
        yMove = -1;

    else
        yMove = 1;
        
    /*	
		These next two conditions "handicap" the goose's x movement every even move
    	and y movement every off move by setting their movement to 0. This is so
    	that it is not impossible for the player to win.
    */
	
	if (move_number % 2 == 0)
    {
    	xMove = 0;
	}
	
	else
	{
		yMove = 0;
	}
	
	move_number++;
	
	if(isPowerUpActive(powerUpTurns))
	{
		xMove = 0;
		yMove = 0;
		powerUpTurns--;
	}
	
	if (monster.can_move(xMove, yMove)) 
        monster.update_location(xMove, yMove);
}

void wallBroken(Actor const & monster, int game_map[MAX_BOARD_X][MAX_BOARD_Y])
{
	if(game_map[monster.get_x()][monster.get_y()] == SHALL_NOT_PASS)
	{
		game_map[monster.get_x()][monster.get_y()] = EMPTY;
	}
}

void wall_trap(int game_map[MAX_BOARD_X][MAX_BOARD_Y])
{
	for(int row = 0; row < TRAP_BARRIER_X; row++)
    {
    	for(int col = 0; col < TRAP_BARRIER_Y; col++)
    	{
    		if(row == TRAP_BARRIER_X - 1 || col == TRAP_BARRIER_Y - 1)
    		{
    			game_map[row][col] = SHALL_NOT_PASS;
				terminal_put(row, col, WALL_CHAR);
			}
		}
	}
	
	
}


					/* END of gooseEscapeGamePlay.cpp */



