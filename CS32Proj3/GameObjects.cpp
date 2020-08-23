#include"GameObjects.h"
#include"Actor.h"
#include"utilities.h"
#include<string>
#include"Player.h"
#include"Level.h"

//////GAME OBJECT BASE CLASS DEFINITION/////////
GameObject::GameObject(Level* level, int row, int col, int type):g_level(level), g_row(row),g_col(col), g_type(type){}

GameObject::~GameObject() {}

//Accessors 
int GameObject::getObjectRow() {
	return g_row;
}
int GameObject::getObjectCol() {
	return g_col;
}

Level* GameObject::getObjectLevel(){
	return g_level;
}

int GameObject::getObjectType() {
	return g_type;
}

//Mutators
//set attackers and defenders 
void GameObject::setObjRow(int row) {
	g_row = row;
}
void GameObject::setObjCol(int col) {
	g_col = col;
}
void GameObject::setObjLevel(Level* level) {
	g_level = level;
}

void GameObject::setObjType(int type){
	g_type=type;
}

/////////////////WEAPON DEFINITION//////////////
//constructor

//take in actor pointer? weapon currently not set to anything defending
//need actor grid condition for move function 
Weapon::Weapon(Level* level, std::string name, Actor* attacker, int row, int col, int type) :
	GameObject(level,row, col,type), w_name(name), w_attacker(attacker), damageAmount(0), dexBonus(0) {
	switch (type) {
	case MC:
		setDexBonus(MACE_DEX_BONUS);
		setDamageAmount(MACE_DAMAGE);
		setString(maceAction);
		break;
	case SS:
		setDexBonus(SHORTSWORD_DEX_BONUS);
		setDamageAmount(SHORTSWORD_DAMAGE);
		setString(shortSwordAction);
		break;
	case LS:
		setDexBonus(LONGSWORD_DEXBONUS);
		setDamageAmount(LONGSWORD_DAMAGE);
		setString(longSwordAction);
		break;
	case MAGICAXE:
		setDexBonus(AXE_DEX_BONUS);
		setDamageAmount(AXE_DAMAGE);
		setString(axeAction);
		break;
	case MAGICFANGS:
		setDexBonus(FANGS_DEX_BONUS);
		setDamageAmount(FANGS_DAMAGE);
		setString(fangsAction);
		break;
	}


}

//destructor- virtual? 
Weapon::~Weapon() {
	delete w_attacker;
}

//accessors 
int Weapon::getDexBonus() {
	return dexBonus;
}
int Weapon::getDamageAmount() {
	return damageAmount;
}
std::string Weapon::getAction() {
	return w_action;
}

std::string Weapon::getNameWeap() {
	return w_name;
}


//mutators 
void Weapon::setDexBonus(int newDexBonus) {
	dexBonus = newDexBonus;
}
void Weapon::setDamageAmount(int newDamageAmt) {
	damageAmount = newDamageAmt;
}

void Weapon::setString(std::string newAction) {
	w_action = newAction;
}

std::string Weapon::attackHit(Actor* defender) {
	int attackerPoints = w_attacker->getDexterity() + dexBonus;
	int defenderPoints = defender->getDexterity() + defender->getArmor();
	if (randInt(1, attackerPoints) >= randInt(1, defenderPoints)) {
		return "hit";
	}
	return "misses";
}

void Weapon::setAttacker(Actor* wielder) {
	w_attacker = wielder;
}


///////SCROLLS IMPLEMENTATION//////
	//Constructor 
Scroll::Scroll(Level* level, Player* player, int row, int col, int type) : GameObject(level,row, col, type), s_player(player){
//scroll cases here similar to weapon 
	switch (type) {
	case S_ARMOR:
		setNameScroll("scroll of improve armor");
		break;
	case S_DEX:
		setNameScroll("scroll of enhance dexterity");
		break;	
	case S_HEALTH:
			setNameScroll("scroll of enhance health");
			break;
	case S_STRENGTH:
		setNameScroll("scroll of raise strength");
		break;
	case S_TELE:
		setNameScroll("scroll of teleportation");
		break;
	}
}

//Destructor 
Scroll::~Scroll() {
	delete s_player;
}
//Accessors 
Player* Scroll::getScrollPlayer(){
	return s_player;
}

std::string Scroll::getNameScroll(){
	return nameScroll;
}

//Mutators 
void Scroll::setScrollPlayer(Player* player) {
	s_player = player; 
}

void Scroll::setNameScroll(std::string name){
	nameScroll = name;
}

void Scroll::useScroll(){
	//delete in here? or delete in player? 
	//make player stats not constant 
	//change function based on type of scroll 
	switch (getObjectType()) {
	case S_ARMOR:
		//The player's armor points are increased by a random integer from 1 to 3.
		s_player->setArmor(s_player->getArmor()+randInt(1,3));
		break;
	case S_DEX:
		//The player's dexterity is increased by 1.
		s_player->setDex(s_player->getDexterity()+1);
		break;
	case S_HEALTH:
		//The player's maximum hit point value is increased by a random integer from 3 to 8. 
		//This scroll does not affect the player's current number of hit points.
		s_player->setMaxHP(s_player->getMaxHP()+randInt(3,8));

		break;
	case S_STRENGTH:
		//The player's strength points are increased by a random integer from 1 to 3.
		s_player->setStrength(s_player->getStrength()+randInt(1,3));
		break;
	case S_TELE:
		//The player is randomly moved to another place in the level that is not occupied by a wall or a monster.
		s_player->setRow(randInt(2, 18));
		s_player->setCol(randInt(2, 70));
		break;
	}
}
