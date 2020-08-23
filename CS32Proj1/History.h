#ifndef HISTORY
#define HISTORY 

#include"globals.h"

class History
{
private:
	//rows and column for history object 
	int h_row;
	int h_col;

	//make a grid of ints like in Arena.h 
	int h_grid[MAXROWS][MAXCOLS];

public:
	//initializes a History object that corresponds to an Arena with nRows rows and nCols columns
	History(int nRows, int nCols);

	//notifies the History object that a poisoned blood vial has been dropped at a grid point that does not currently have a poisoned blood vial
	//returns false if row r, column c is not within the bounds specified by the History constructor
	//otherwise, it returns true after recording
	bool record(int r, int c);

	//clears the screen and displays the history grid as the posted programs do
	//lear the screen, display the history grid, and write an empty line after the history grid
	//it does not print the Press enter to continue
	void display() const;
};

#endif

//how do we testg32 with different files without zip and rezipping 
//using nano 