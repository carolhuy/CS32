#include"Actor.h"
#include<iostream>
#include"GameObjects.h"


//const for HP, armor, strength, dexterity 
//const for sleepTime 
//accessors

//int row and int col may be rand for the room coordinates 
Actor::Actor(int row, int col):m_weapon(nullptr),m_name(""),m_row(row),m_col(col), m_dead(false), 
m_HP(0), m_armor(0), m_strength(0), m_dexterity(0),m_sleepTime(0),maxHP(0), m_sleep(false) {}

//Destructor 
//pure virtual destructor(still needs to be defined)
Actor::~Actor() {
	delete m_weapon;
}

//accessors
int  Actor::row() const {
	return m_row; 
}
int  Actor::col() const {
	return m_col; 
}

int Actor::getHP() {
	return m_HP; 
}

int Actor::getMaxHP(){
	return maxHP;
}

int Actor::getArmor() {
	return m_armor; 
}
int Actor::getStrength() {
	return m_strength;
}
int Actor::getDexterity() {
	return m_dexterity;
}
std::string Actor::getName() {
	return m_name;
}

bool Actor::isDead() const {
	return m_dead;
}

Weapon* Actor::getWeapon() {
	return m_weapon;
}

bool Actor::isSleep() const {
	return m_sleep;
}

//mutators 
void Actor::setDead() {
	m_dead = true;
}

void Actor::setHP(int newHP) {
	m_HP = newHP; 
}

void Actor::setMaxHP(int newMaxHP) {
	maxHP = newMaxHP; 
}
void Actor::setArmor(int newArmor) {
	m_armor = newArmor;
}
void Actor::setStrength(int newStrength) {
	m_strength = newStrength;
}
void Actor::setDex(int newDex) {
	m_dexterity = newDex;
}
void Actor::setWeapon(Weapon* weapon) {
	m_weapon = weapon;
}

void Actor::setRow(int row){
	m_row = row; 
}
void Actor::setCol(int col){
	m_col = col; 
}

void Actor::setName(std::string name){
	m_name = name;
}

std::string Actor::attack(Actor* defender){
	//setDead 
	std::string outputDead; 
//check if attack hits
	std::string checkAttack = getWeapon()->attackHit(defender);
	if (checkAttack=="hit") {
		//reduce HP of defender by damagePoints = randInt(0, attackerStrength + weaponDamageAmount - 1);
		int damagePoints = randInt(0, getStrength() + getWeapon()->getDamageAmount() - 1);
		defender->setHP(defender->getHP()- damagePoints);
	}
//cout string 
	//dealing final blow message 
	if (defender->getHP()<=0) {
		defender->setDead();
		outputDead += getName();
		outputDead += " ";
		outputDead += getWeapon()->getAction();
		outputDead += " ";
		outputDead += defender->getName();
		outputDead += " dealing final blow."; 
		return outputDead;
	}
	//attack message 
	std::string output = getName();
	output += " ";
	output += getWeapon()->getAction();
	output += " ";
	output += defender->getName();
	output += " and ";
	output += checkAttack;
	return output;
}