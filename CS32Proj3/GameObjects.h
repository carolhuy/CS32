#ifndef _GAMEOBJ_
#define _GAMEOBJ_
#include<string>
#include"utilities.h"
#include"constants.h"
class Level;
class Player;

///////////////GAME OBJECT BASE CLASS///////////////////////
class GameObject {
public:
	//Constructor 
	GameObject(Level* level, int row, int col, int type);

	//Destructor 
	virtual ~GameObject();

	//Accessors 
	int getObjectRow();
	int getObjectCol(); 
	Level* getObjectLevel();
	int getObjectType(); 

	//Mutators 
	void setObjRow(int row);
	void setObjCol(int col);
	void setObjLevel(Level* level);
	void setObjType(int type);

private:
	int g_row;
	int g_col;
	int g_type;
	Level* g_level;
};

class Actor;

/////////////////WEAPONS DERIVED DECLARATION/////////
//class for weapons 
class Weapon : public GameObject {
public:
	//Constructor
	//need pointers for attacker and defender 
	Weapon(Level* level, std::string name, Actor* attacker, int row, int col, int type);

	//Destructor - virtual?
	~Weapon();

	//accessors 
	int getDexBonus();
	int getDamageAmount();
	std::string getAction();
	std::string getNameWeap();

	//mutators 
	void setDexBonus(int newDexBonus);
	void setDamageAmount(int newDamageAmt);
	void setString(std::string newAction);
	void setAttacker(Actor* wielder);

	//string for attackHit - tells if the attack was successful 
	std::string attackHit(Actor* defender);

	//int for damage 

private:
	std::string w_name;
	std::string w_action;
	int dexBonus;
	int damageAmount;
	Actor* w_attacker;

};

///////////MAGIC FANGS DERIVED CLASS///////
/*class magicFangs : public Weapon {
public:
	//DC
	magicFangs(int r, int c) : Weapon("magic fangs of sleep", nullptr, r, c,MAGICFANGS) {
		setDamageAmount(2);
		setDexBonus(3);
	}

	bool probAsleep() {
		return trueWithProbability(0.2);
	}

private:
	//number of moves sleep will last 
	int X = randInt(2, 6);
};*/

/////////////SCROLL DECLARATION//////////////
class Scroll : public GameObject{
public:
	//Constructor 
	Scroll(Level* level, Player* player, int row, int col, int type);

	//Destructor 
	~Scroll();

	//Accessors 
	Player* getScrollPlayer();
	std::string getNameScroll();

	//Mutators 
	void setScrollPlayer(Player* player);
	void useScroll(); 
	void setNameScroll(std::string name);
private:
	Player* s_player; 
	std::string nameScroll;
};
#endif