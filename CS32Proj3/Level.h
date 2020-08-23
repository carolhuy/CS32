#include<string>
#include"constants.h"
#include"utilities.h"
#include<vector>

#ifndef _LEVEL_
#define _LEVEL_

//creating dungeon for game - start with all #
//should have constants for movement (north south etc) 
// figure out how to do rooms

///to create pointers to these objects 
class Monster;
class GameObject; 
class Dungeon; 
class Actor;

class Level {
public:
	//Constructor
	Level(Dungeon* dungeon, int lvNum, int nRows, int nCols);

	//Destructor 
	~Level();

	//Accessor function 
	int rows() const;
	int cols() const;

	//monster accessors and scroll accessors? 

	//need accessors for number of monsters and weapons in order to use a for loop later on 
	int getCellStatus(int r, int c) const;
	int getLevelNum() const; 
	int getNumMon() const;
	int getMaxMonster() const; 
	int getMaxObjects() const;
	Dungeon* getDungeon() const; 
	std::vector<Monster*> getMonsVect() const; 
	std::vector<GameObject*> getObjectVect() const; 

	void display(std::string msg) const;

	//Mutator functions 
	//change individual cell 
	void setCellStatus(int r, int c, int status);

	//add a monster 
	bool addMonster(int r, int c);

	//add a scroll 
	bool addObject(int r, int c, int typeNum);

	// Helper functions
	void checkPos(int r, int c, std::string functionName) const;
	bool isPosInBounds(int r, int c) const;
	std::string moveMonsters();
	bool isWall(int r, int c) const;
	Actor* getActor(int r, int c);
	bool isPlayer(int r, int c);
	GameObject* getObject(int r, int c);
	void deleteDeadMons();
	//deleting specific object 
	void deleteObject(int r, int c);

private:
	Dungeon* l_dungeon;
	int m_grid[MAXROWS][MAXCOLS];

	int m_rows;
	int m_cols;
	int m_turns;
	int m_nMonsters;
	int m_nObjects;
	int maxObjects;
	int maxMonsters;
	int numLevel;  

	std::vector<Monster*> m_monster;
	std::vector<GameObject*> m_objects; 
};


#endif