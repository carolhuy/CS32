#ifndef _ARENA_
#define _ARENA_

#include<iostream>
#include<string>
#include"globals.h"
#include"History.h"

class Vampire;
class Player; 

//try to comment this out and see if still runs - should because has History included 
//class History; 

class Arena
{
public:
	// Constructor/destructor
	Arena(int nRows, int nCols);
	~Arena();

	// Accessors
	int     rows() const;
	int     cols() const;
	Player* player() const;
	int     vampireCount() const;
	int     getCellStatus(int r, int c) const;
	int     numberOfVampiresAt(int r, int c) const;
	void    display(std::string msg) const;

	// Mutators
	void setCellStatus(int r, int c, int status);
	bool addVampire(int r, int c);
	bool addPlayer(int r, int c);
	void moveVampires();

	History& history();


private:
	int      m_grid[MAXROWS][MAXCOLS];
	int      m_rows;
	int      m_cols;
	Player* m_player;
	Vampire* m_vampires[MAXVAMPIRES];
	int      m_nVampires;
	int      m_turns;

	// Helper functions
	void checkPos(int r, int c, std::string functionName) const;
	bool isPosInBounds(int r, int c) const;

	History m_history;
};
#endif 