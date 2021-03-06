					   /* START OF gooseEscapeMain.cpp */

#include <BearLibTerminal.h>
#include <cmath>
#include <iostream>
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActors.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);

/*
    The code below provides a skeleton of the game play.  You will need to
    write code for setting up the game board, and playing the game itself.
    You can modify the code given as needed.
    
    Call the functions that you have written in the game play file, and that
    you have added to the Actor class.
*/
 	
    //make the player
	Actor player(PLAYER_CHAR, 10,10);
	
	//make the monster
	Actor monster(MONSTER_CHAR, 70,20);
	
    int game_map[MAX_BOARD_X][MAX_BOARD_Y] = {0};
  	
/*
    Initiallize locations in the game board to have game features.  What if you
    have man things to add to the game board?  Should you use a loop?  Does it
    make sense to store this information in a file?  Should this code be a
    function as well?
*/
    for(int row = 0; row < MAX_BOARD_X; row++)
	{
		for(int col = 1; col < MAX_BOARD_Y - 1; col++)
		{
			if((row < 60 && row > 20) && (col % 5 == 0))
			{
				game_map[row][col] = SHALL_NOT_PASS;
			}
		}
	}
	
    game_map[WIN_START_X][WIN_START_Y] = WINNER;
  	
    // Call the function to print the game board
    
    createBoard(game_map);
    
    game_map[1][1] = POWER_UP;
    game_map[5][1] = COIN;
  	
	// Printing the instructions
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use the arrow keys to move");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");
	out.writeLine("Health: " + player.get_health_string());

/*
    This is the main game loop.  It continues to let the player give input
    as long as they do not press escape or close, they are not captured by
    the goose, and they didn't reach the win tile
*/
/*
    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
    key being pressed.
*/
    int keyEntered = TK_A;  // can be any valid value that is not ESCAPE or CLOSE
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
          && !captured(player) && !player_safe(player, game_map))
	{
	    // get player key press
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
            // move the player, you can modify this function
            game_map[player.get_x()][player.get_y()] = 0;
    	    movePlayer(keyEntered, player, game_map);
    	    game_map[player.get_x()][player.get_y()] = player.get_actorChar();

            // call the goose's chase function
            
            gooseChase(player, monster, game_map);
            
            // call other functions to do stuff?
            
            if(playerAttacked(player, monster))
            {
            	player.update_health(ATTACK_DAMAGE);
            	out.writeLine("You have been hit by the GOOSE! Health: " + player.get_health_string());
			}
            
			wallBroken(monster, game_map);
            
			terminal_refresh();	    
        }
  	}

    if (keyEntered != TK_CLOSE)
    {
      	//once we're out of the loop, the game is over
        out.writeLine("Game has ended");
    
        // output why:  did the goose get us, or did we get to the win location?
        
        if(player_safe(player, game_map))
        {
        	out.writeLine("YOU ARE SAFE!");
		}
		
		else
		{
			out.writeLine("THE GOOSE CAUGHT YOU!");
		}
	
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }

	//game is done, close it  
    terminal_close();
}

						/* END of gooseEscapeMain.cpp */
