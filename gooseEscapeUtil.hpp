					  /* START of gooseEscapeUtil.hpp */

//STUDENTS: Be very careful if you decide to change these values

#ifndef GOOSE_UTIL
#define GOOSE_UTIL
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

// Screen layout
const int NUM_SCREEN_X = 80;
const int NUM_SCREEN_Y = 25;
const char SETUP_MESSAGE[] = "window: title='Escape the Goose', size=80x25";
const int MIN_SCREEN_X = 0;
const int MIN_SCREEN_Y = 0;
const int MAX_SCREEN_X = NUM_SCREEN_X - 1;
const int MAX_SCREEN_Y = NUM_SCREEN_Y - 1;

//Initial Winning Character Location

const int WIN_START_X = 76;
const int WIN_START_Y = 20;

// Play area layout
const int NUM_BOARD_X = 80;  // needs to be <= NUM_SCREEN_X
const int NUM_BOARD_Y = 21;  // needs to be < NUM_SCREEN_Y
const int MIN_BOARD_X = 0;
const int MIN_BOARD_Y = 0;
const int MAX_BOARD_X = NUM_BOARD_X - 1;
const int MAX_BOARD_Y = NUM_BOARD_Y - 1;

// Console message area layout
const int NUM_CONSOLE_X = 79;  // needs to be <= NUM_SCREEN_X
const int NUM_CONSOLE_Y = NUM_SCREEN_Y - NUM_BOARD_Y;
const int MIN_CONSOLE_X = 1;
const int MIN_CONSOLE_Y = MAX_BOARD_Y + 1;
const int MAX_CONSOLE_X = MAX_SCREEN_X;
const int MAX_CONSOLE_Y = MAX_SCREEN_Y;

//Goose Movement

const int POWER_UP_ACTIVE = 10;

//Health int Actor Class

const int MAX_HEALTH = 100;
const int ATTACK_DAMAGE = 25;

//Trap Wall Location

const int TRAP_BARRIER_X = 18;
const int TRAP_BARRIER_Y = 10;


#endif

					   /* END of gooseEscapeUtil.hpp */
