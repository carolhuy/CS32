#ifndef _PLAYER_
#define _PLAYER_ 

#include"Actor.h"
#include<vector>
#include<iostream>
#include<string>

class Scroll; 
class Weapon; 
class Dungeon; 
class GameObject;

class Player :public Actor{
public:
	//Constructor 
	Player(Dungeon* dungeon, int r, int c); 

	//Destructor 
	~Player(); 

	//accessor function 
	std::vector<GameObject*> getInvent();

	//mutator function 
	void addInvent(GameObject* newObj);

	//Mutators 
	//Before each command from the user, there is a 1 in 10 chance the player will regain 1 hit point, up to the player's maximum hit point value
	std::string move(int dir);

	//wielding a weapon 
	void wieldWeapon(Weapon* newWeapon);

	//picking up object (PLAYER UNIQUE) 
	std::string pickObj();
	//reading scroll (PLAYER UNIQUE)

//Private variables unique to Player 
private: 
	std::vector<GameObject*> p_objects;
	Scroll* p_scroll; 
	int numWeap; 
	int numScroll; 
	Dungeon* p_dungeon; 
};

#endif