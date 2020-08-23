#ifndef _MONSTER_
#define _MONSTER_
#include"Actor.h"
class Level; 

class Monster: public Actor {
public:
	Monster(Level* level, int r, int c, int type);
	~Monster(); 
	int getMonsNum();
	Level* getMonsLevel(); 
	//for now to test move function 
	virtual std::string move();
	//probability of dropping an item - include addObject from Level in implementation 
	//pure virtual base class problems??
	virtual bool probDropItem() =0;
	//virtual int toDrop();  
private:
	Level* monst_level;
	bool smellPlayer; 
	int monType; 
	int m_turnsAsleep;
};

///BOGEYMAN DECLARATION 
class Bogeyman : public Monster {
public:
	Bogeyman(Level* level, int r, int c);
	virtual std::string move(); 
	//probability of dropping an item - include addObject from Level in implementation 
	virtual bool probDropItem();
private:
};

//SNAKEWOMAN DECLARATION 
class Snakewoman : public Monster {
public:
	Snakewoman(Level* level, int r, int c);
	virtual std::string move();
	//probability of dropping an item - include addObject from Level in implementation 
	virtual bool probDropItem();
private:
};

/////////DRAGON DECLARATION
class Dragon :public Monster {
public: 
	Dragon(Level* level, int r, int c);
	virtual std::string move();
	//probability of dropping an item - include addObject from Level in implementation 
	virtual bool probDropItem();
private:
};

////////////////GOBLIN DECLARATION
class Goblin :public Monster {
public: 
	Goblin(Level* level, int r, int c);
	virtual std::string move();
	//probability of dropping an item - include addObject from Level in implementation 
	virtual bool probDropItem();
private:
};
#endif