#include"Monster.h"
#include"utilities.h"
#include"constants.h"
#include"GameObjects.h"
#include"constants.h"
#include"Level.h"
#include"helper.h"
#include"Dungeon.h"
#include"Player.h"
#include<cmath>
#include<stdlib.h>

Monster::Monster(Level* level, int r, int c, int type) :Actor(r,c),monst_level(level),smellPlayer(false), monType(type), m_turnsAsleep(0) {}

Monster::~Monster() {
}

int Monster::getMonsNum() {
	return monType;
}

//for now to test move function
std::string Monster::move(){
	//if asleep 
	/*if (m_turnsAsleep > 0) {
		--m_turnsAsleep;
		return "";
	}

	//if not asleep, then move in a random direction 
	//check if there is an object in the way 
	//direction want to move 
	return attemptMove(monst_level, this, randInt(0, NUMDIRS - 1), row(), col());*/
	return "";

}

Level* Monster::getMonsLevel(){
	return monst_level;
}


Bogeyman::Bogeyman(Level* level, int r, int c) : Monster(level, r, c,BG) {
	//set stats for bogeyman 
	int INITIAL_HP_BG = randInt(5, 10);
	setHP(INITIAL_HP_BG);
	setMaxHP(INITIAL_HP_BG);
	setArmor(2);
	setDex(randInt(2, 3));
	setStrength(randInt(2, 3));
	setName("Bogeyman");
	setWeapon(new Weapon(level,shortSword, this, row(), col(),SS));
}

//BOGEYMAN MOVE IMPLEMENTATION
//If the bogeyman could take one through five steps, ignoring walls or other monsters, and reach the player, then it smells the player.
std::string Bogeyman::move() {
	//find how many steps from player to bogeyman using distance formula 
	int b_row = row();
	int b_col = col();
	int p_row = getMonsLevel()->getDungeon()->getPlayer()->row();
	int p_col = getMonsLevel()->getDungeon()->getPlayer()->col();
	int distance = sqrt((p_row-b_row)*(p_row - b_row) +(p_col-b_col)* (p_col - b_col));

	//if the distance is less than 5 steps, then bogeyman moves closer 
	if (distance <= 5) {
		//if player or bogey is on the same column 
		if (b_col==p_col) {
			//check which is closer 
			//player is below bogeyman, move south 
			if (p_row > b_row) {
				return attemptMove(getMonsLevel(), this, SOUTH, b_row, b_col);
			}
			//player is above bogeyman, move north 
			return attemptMove(getMonsLevel(), this, NORTH, b_row, b_col);
		}

		//if player or bogey on the same row 
		if (b_row == p_row ) {
			//player is left of bogey, move west 
			if (p_col < b_col) {
				return attemptMove(getMonsLevel(), this, WEST, b_row, b_col);
			}
			//player is right of bogey, move east 
			return attemptMove(getMonsLevel(), this, EAST, b_row, b_col);
		}

		//if the player and bogey are not on same row or same col 
		//player is below, move south 
		if (p_row > b_row) {
			return attemptMove(getMonsLevel(), this, SOUTH, b_row, b_col);
		}
		//player is above, move north 
		else if (p_row < b_row) {
			return attemptMove(getMonsLevel(), this, NORTH, b_row, b_col);
		}
		//player is left of bogey, move west 
		else if (p_col < b_col) {
			return attemptMove(getMonsLevel(), this, WEST, b_row, b_col);
		}
		else
		//player is right of bogey, move east 
		return attemptMove(getMonsLevel(), this, EAST, b_row, b_col);
	}
	//does not smell player, do not move 
	else
		return "";
}
//BOGEYMAN DROP ITEM IMPLEMENTATION 
	//probability of dropping an item - include addObject from Level in implementation 
bool Bogeyman::probDropItem() {
	return trueWithProbability(0.1);
}

Snakewoman::Snakewoman(Level* level, int r, int c): Monster(level,r,c,SW) {
	int INITIAL_HP_SW = randInt(3, 6);
	setHP(INITIAL_HP_SW);
	setMaxHP(INITIAL_HP_SW);
	setArmor(3);
	setStrength(2);
	setDex(3);
	setName("Snakewoman");
	setWeapon(new Weapon(level,fangs, this, row(), col(),MAGICFANGS));
}

/* can smell the player only from a distance of three or less
When a snakewoman dies, there is a 1 in 3 chance she will drop her magic fangs of sleep if there is no item at the position where she dies.*/
std::string Snakewoman::move() {
	//find how many steps from player to bogeyman using distance formula 
	int s_row = row();
	int s_col = col();
	int p_row = getMonsLevel()->getDungeon()->getPlayer()->row();
	int p_col = getMonsLevel()->getDungeon()->getPlayer()->col();
	int distance = sqrt((p_row - s_row)*(p_row - s_row) + (p_col - s_col)*(p_col - s_col));

	//if the distance is less than 5 steps, move closer 
	if (distance <= 3) {
		if (s_col == p_col) {
			//check which is closer 
			//player is below bogeyman, move south 
			if (p_row > s_row) {
				return attemptMove(getMonsLevel(), this, SOUTH, s_row, s_col);
			}
			//player is above bogeyman, move north 
			return attemptMove(getMonsLevel(), this, NORTH, s_row, s_col);
		}

		//if player or bogey on the same row 
		if (s_row == p_row) {
			//player is left of bogey, move west 
			if (p_col < s_col) {
				return attemptMove(getMonsLevel(), this, WEST, s_row, s_col);
			}
			//player is right of bogey, move east 
			return attemptMove(getMonsLevel(), this, EAST, s_row, s_col);
		}

		//if the player and bogey are not on same row or same col 
		//player is below, move south 
		if (p_row > s_row) {
			return attemptMove(getMonsLevel(), this, SOUTH, s_row, s_col);
		}
		//player is above, move north 
		else if (p_row < s_row) {
			return attemptMove(getMonsLevel(), this, NORTH, s_row, s_col);
		}
		//player is left of bogey, move west 
		else if (p_col < s_col) {
			return attemptMove(getMonsLevel(), this, WEST, s_row, s_col);
		}
		else
			//player is right of bogey, move east 
			return attemptMove(getMonsLevel(), this, EAST, s_row, s_col);

	}
	//does not smell player, do not move 
	else
		return "";
}

//SNAKEWOMAN DROP ITEM IMPLEMENTATION 
	//probability of dropping an item - include addObject from Level in implementation 
bool Snakewoman::probDropItem() {
	return trueWithProbability(0.33333);
}

Dragon::Dragon(Level* level, int r, int c):Monster(level,r,c,DG){
	int INITIAL_HP_DG = randInt(20, 25);
	setHP(INITIAL_HP_DG);
	setMaxHP(INITIAL_HP_DG);
	setArmor(4);
	setStrength(4);
	setDex(4);
	setName("Dragon");
	setWeapon(new Weapon(level,longSword, this, row(), col(),LS));
}

//Dragons do not move, since they want to protect their treasure, but like any monster, will attack the player if the player is next to it
std::string Dragon::move(){
	//calculating distance
	int d_row = row();
	int d_col = col();
	int p_row = getMonsLevel()->getDungeon()->getPlayer()->row();
	int p_col = getMonsLevel()->getDungeon()->getPlayer()->col();
	int distance = sqrt((p_row - d_row) ^ 2 + (p_col - d_col) ^ 2);
	//if the player is right next to it (aka has distance of 1) 
	if (distance == 1) {
		//attack player
		//////////////POSSIBLE RUNTIME ERROR HERE IF THERE IS NO ACTOR POINTER? BETTER WAY?/////////////
		//check if nullptr first? 
		return attack(getMonsLevel()->getDungeon()->getPlayer());
	}
	//player not next to it, does not move 
	return "";
}

//DRAGON DROP ITEM IMPLEMENTATION 
bool Dragon::probDropItem() {
	return trueWithProbability(1);
}

Goblin::Goblin(Level* level, int r, int c):Monster(level,r,c,GB){
	int INITIAL_HP_GB = randInt(15, 20);
	setHP(INITIAL_HP_GB);
	setMaxHP(INITIAL_HP_GB);
	setArmor(1);
	setStrength(3);
	setDex(1);
	setName("Goblin");
	setWeapon(new Weapon(level,shortSword, this, row(), col(),SS));
}

std::string Goblin::move(){
	int r = row();
	int c = col(); 
	return attemptMove(getMonsLevel(), this, randInt(0, NUMDIRS - 1), r, c);
}

//GOBLIN DROP ITEM IMPLEMENTATION 
	//probability of dropping magic axe or fangs 
bool Goblin::probDropItem() {
	return trueWithProbability(0.3333);
}