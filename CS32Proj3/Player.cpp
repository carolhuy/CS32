#include"Player.h"
#include"Dungeon.h"
#include"constants.h"
#include"GameObjects.h"
#include<iostream>
#include"Level.h"
#include"helper.h"

//monster will also need a sleep bool 

//Constructor 
Player::Player(Dungeon* dungeon, int r, int c):Actor(r,c),p_dungeon(dungeon),p_scroll(nullptr),numScroll(0),numWeap(0){
	//if out of bounds or a wall 
	if (p_dungeon->getLevel()->isPosInBounds(r,c)==false) {
		std::cout << "Player cannot be created out of bounds"<<std::endl; 
	}

	//set stats for new player
	setHP(INITIAL_PLAYER_HP);
	setMaxHP(INITIAL_PLAYER_HP);
	setArmor(INITIAL_PLAYER_ARMOR);
	setDex(INITIAL_PLAYER_DEX);
	setStrength(INITIAL_PLAYER_STRENGTH);
	setName("Player");
	Weapon* playerWeapon = new Weapon(dungeon->getLevel(), shortSword, this, row(), col(), SS);
	setWeapon(playerWeapon);
	p_objects.push_back(playerWeapon);
}

//Destructor 
Player::~Player() {
	p_scroll = nullptr;
	delete p_dungeon;
}

//accessor function 
std::vector<GameObject*> Player::getInvent() {
	return p_objects;
}

//mutator function 
//add to inventory 
void Player::addInvent(GameObject* newObj) {
	p_objects.push_back(newObj);
	//put string to display here? 
}

//move
std::string Player::move(int dir){
	return attemptMove(p_dungeon->getLevel(), this, dir, row(), col());
}

//picking up objects
std::string Player::pickObj() {
	std::string msg = "";
	//get the object 
	GameObject* current = p_dungeon->getLevel()->getObject(row(),col());
	//if this is null, then return 
	if (current == nullptr) {
		return "";
	}

	//if can add to inventory 
	if (p_objects.size() < 25) {
		//Try to convert current to a weapon pointer 
		Weapon* wp = dynamic_cast<Weapon*>(current);
		//if wp is not null, wp points to a weapon 
		if (wp != nullptr) {
			msg += "You pick up a ";
			msg += (*wp).getNameWeap();
		}
		//wp points to a scrolls 
		else{
			//convert current to a scroll 
			//POTENTIAL ERROR
			Scroll* sp = dynamic_cast<Scroll*>(current);
			msg += "You pick up a ";
			msg += (*sp).getNameScroll();
		}
		//add to inventory 
		p_objects.push_back(current);
	}
	//cannot add to inventory 
	else {
		msg += "Your knapsack is full; you can't pick that up.";
	}
	return msg;
}

void Player::wieldWeapon(Weapon* newWeapon) {
	//store the old weapon
	Weapon* oldWeapon = getWeapon();

	//give player the new weapon 
	setWeapon(newWeapon);

	//store old weapon in inventory 
	addInvent(oldWeapon);
}