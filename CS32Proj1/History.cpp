#include<iostream>
#include"History.h"
#include"globals.h"

//initializes a History object that corresponds to an Arena with nRows rows and nCols columns
History::History(int nRows, int nCols): h_row(nRows), h_col(nCols) {

	//making empty grid 
	for (int r = 1; r <= h_row; r++)
		for (int c = 1; c <= h_col; c++) {
			h_grid[r-1][c-1] = 0;
		}
}

//notifies the History object that a poisoned blood vial has been dropped at a grid point that does not currently have a poisoned blood via
bool History::record(int r, int c) {

	//returns false if row r, column c is not within the bounds specified by the History constructor
	if (r<=0 || r>h_row || c<=0 || c> h_col) {
		return false;
	}

	//otherwise, it returns true after recording
	else {
	//record value in blood vial 
		//records if it has poison by marking with a number - number corresponds with character
		h_grid[r - 1][c - 1]++;
		
		//returns true
		return true;
	}
}

//test on Windows - make have B 

void History::display() const {
	//clear the screen
	clearScreen();

	//make a grid and rows, columns 
	char displayGrid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill displayGrid with dots (empty) and letters indicated poison vials 
	for (r = 1; r <= h_row; r++) {
		for (c = 1; c <= h_col; c++) {
			if (h_grid[r - 1][c - 1] == EMPTY) {
				displayGrid[r - 1][c - 1] = '.';
			}
			else if (h_grid[r - 1][c - 1] == 1) {
				displayGrid[r - 1][c - 1] = 'A';
			}
			else if (h_grid[r - 1][c - 1] == 2) {
				displayGrid[r - 1][c - 1] = 'B';
			}
			else if (h_grid[r - 1][c - 1] == 3) {
				displayGrid[r - 1][c - 1] = 'C';
			}
			else if (h_grid[r - 1][c - 1] == 4) {
				displayGrid[r - 1][c - 1] = 'D';
			}
			else if (h_grid[r - 1][c - 1] == 5) {
				displayGrid[r - 1][c - 1] = 'E';
			}
			else if (h_grid[r - 1][c - 1] == 6) {
				displayGrid[r - 1][c - 1] = 'F';
			}
			else if (h_grid[r - 1][c - 1] == 7) {
				displayGrid[r - 1][c - 1] = 'G';
			}
			else if (h_grid[r - 1][c - 1] == 8) {
				displayGrid[r - 1][c - 1] = 'H';
			}
			else if (h_grid[r - 1][c - 1] == 9) {
				displayGrid[r - 1][c - 1] = 'I';
			}
			else if (h_grid[r - 1][c - 1] == 10) {
				displayGrid[r - 1][c - 1] = 'J';
			}
			else if (h_grid[r - 1][c - 1] == 11) {
				displayGrid[r - 1][c - 1] = 'K';
			}
			else if (h_grid[r - 1][c - 1] == 12) {
				displayGrid[r - 1][c - 1] = 'L';
			}
			else if (h_grid[r - 1][c - 1] == 13) {
				displayGrid[r - 1][c - 1] = 'M';
			}
			else if (h_grid[r - 1][c - 1] == 14) {
				displayGrid[r - 1][c - 1] = 'N';
			}
			else if (h_grid[r - 1][c - 1] == 15) {
				displayGrid[r - 1][c - 1] = 'O';
			}
			else if (h_grid[r - 1][c - 1] == 16) {
				displayGrid[r - 1][c - 1] = 'P';
			}
			else if (h_grid[r - 1][c - 1] == 17) {
				displayGrid[r - 1][c - 1] = 'Q';
			}
			else if (h_grid[r - 1][c - 1] == 18) {
				displayGrid[r - 1][c - 1] = 'R';
			}
			else if (h_grid[r - 1][c - 1] == 19) {
				displayGrid[r - 1][c - 1] = 'S';
			}
			else if (h_grid[r - 1][c - 1] == 20) {
				displayGrid[r - 1][c - 1] = 'T';
			}
			else if (h_grid[r - 1][c - 1] == 21) {
				displayGrid[r - 1][c - 1] = 'U';
			}
			else if (h_grid[r - 1][c - 1] == 22) {
				displayGrid[r - 1][c - 1] = 'V';
			}
			else if (h_grid[r - 1][c - 1] == 23) {
				displayGrid[r - 1][c - 1] = 'W';
			}
			else if (h_grid[r - 1][c - 1] == 24) {
				displayGrid[r - 1][c - 1] = 'X';
			}
			else if (h_grid[r - 1][c - 1] == 25) {
				displayGrid[r - 1][c - 1] = 'Y';
			}
			else {
				displayGrid[r - 1][c - 1] = 'Z';
			}
		}
	}
		
	// Draw the grid
	for (r = 1; r <= h_row; r++)
	{
		for (c = 1; c <= h_col; c++) {
			std::cout << displayGrid[r - 1][c - 1];
		}
		//serves to make new rows 
		std::cout << std::endl;
	}
	//write an empty line after the history grid after end of for loop
	std::cout << std::endl;
}