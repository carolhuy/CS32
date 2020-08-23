#include"Dungeon.h"
#include"Level.h"
#include"Player.h"
Dungeon::Dungeon():d_level(nullptr),levelCounter(0),d_player(nullptr){}

Dungeon::~Dungeon() {
	delete d_level; 
	delete d_player;
}

Level* Dungeon::getLevel() {
	return d_level;
}

Player* Dungeon::getPlayer() {
	return d_player;
}

void Dungeon::setLevel(Level* nLevel) {
	d_level = nLevel;
}

int Dungeon::getLevelNum() {
	return levelCounter;
}

void Dungeon::setLevelNum(int numLevel){
	levelCounter = numLevel;
}

void Dungeon::incrementLevel() {
	++levelCounter;
}

//adding a player 
bool Dungeon::addPlayer(int r, int c) {
	//if position is out of bounds or a wall 
	if (this->getLevel()->isPosInBounds(r, c)==false)
		return false;

	// Don't add a player if one already exists
	if (d_player!= nullptr)
		return false;
	d_player = new Player(this, r, c);
	getLevel()->setCellStatus(r, c, ACTOR);
	return true;
}