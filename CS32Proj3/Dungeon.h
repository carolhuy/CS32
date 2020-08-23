#ifndef _DUNGEON_
#define _DUNGEON_

class Level; 
class Player; 

class Dungeon {
public:
	//Constructor
	Dungeon();

	//Destructor
	~Dungeon(); 

	//Accessors 
	Level* getLevel();
	Player* getPlayer(); 
	int getLevelNum();

	//Mutators 
	//Adding a player
	bool addPlayer(int r, int c);

	//changing the level 
	void setLevel(Level* nLevel);
	void setLevelNum(int numLevel);
	void incrementLevel();

private:
	Level* d_level;
	int levelCounter; 
	Player* d_player;
};

#endif