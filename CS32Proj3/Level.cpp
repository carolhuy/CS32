#include"Level.h"
#include<iostream>
#include"utilities.h"
#include"Player.h"
#include"GameObjects.h"
#include"Dungeon.h"
#include"Monster.h"
#include"constants.h"
#include<vector>
#include<iterator>
#include<list>
#include<algorithm>

using namespace std;

///////////////////////Constructor/////////////////
Level::Level(Dungeon* dungeon, int lvNum, int nRows, int nCols) : l_dungeon(dungeon), numLevel(lvNum), m_rows(nRows), m_cols(nCols),
m_turns(0), m_nMonsters(0), maxObjects(randInt(2,3)), m_nObjects(0), maxMonsters(randInt(2, 5 * (lvNum + 1) + 1)) {
	if (nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS)
	{
		cout << "***** Level created with invalid size " << nRows << " by "
			<< nCols << "!" << endl;
		exit(1);
	}

//Fill with Walls//
	for (int r = 1; r <= m_rows; r++)
		for (int c = 1; c <= m_cols; c++)
			setCellStatus(r, c, WALLS);

//Fill with white space for rooms//
	//for rooms, use rand and store values in rand in order to make rooms? rand for columns and rows 
	//for the columns and rows left and above rand numbers, fill with wall  
	//make sure rand rooms are good size 
	//use randInt here 
	//helper function make rooms (code below) 
	//checkPath to make a path 

	//for top and bottom row 
	for (int t = 2; t <= 2; ++t) {
		for (int c = 2; c <= m_cols - 1; c++) {
			setCellStatus(t, c, EMPTY);
		}
	}

	for (int b = m_rows - 1; b <= m_rows - 1; ++b) {
		for (int c = 2; c <= m_cols - 1; c++) {
			setCellStatus(b, c, EMPTY);
		}
	}

	//fill in the blanks 
	for (int left = 2; left <= m_cols - 1; ++left) {
		for (int r = 2; r <= m_rows - 1; r++) {
			setCellStatus(r, left, EMPTY);
		}
	}
	//put stairs randomly in place without stairs 
	int stairRow = randInt(2, 18);
	int stairCol = randInt(2, 70);
	do {
		stairRow = randInt(2, 18);
		stairCol = randInt(2, 70);
	} while (getCellStatus(stairRow, stairCol) != EMPTY);
	setCellStatus(stairRow, stairCol, STAIRS);
}

///////////////////////////////Destructor///////////////////
Level::~Level() {

	//delete monsters 
	auto mItr = m_monster.begin(); 
	while (mItr != m_monster.end()) {
		if (m_monster.size() == 1) {
			delete *mItr;
			break;
		}
		mItr = m_monster.erase(mItr);
		++mItr;
	}

	//delete objects
	auto oItr = m_objects.begin();
	while (oItr != m_objects.end() ) {
		if (m_objects.size() == 1) {
			delete *oItr;
			break;
		}
		oItr = m_objects.erase(oItr);
		++oItr;
	}
	//delete dungeon 
	delete l_dungeon;

}

//////////////////////////Accessor function////////////////
int Level::rows() const {
	return m_rows;
}
int Level::cols() const {
	return m_cols;
}

int Level::getLevelNum() const {
	return numLevel;
}

int Level::getNumMon() const{
	return m_nMonsters;
}

int Level::getMaxMonster() const{
	return maxMonsters;
}

int Level::getMaxObjects() const{
	return maxObjects;
}

int Level::getCellStatus(int r, int c) const {
	checkPos(r, c, "Arena::getCellStatus");
	return m_grid[r - 1][c - 1];
}

Dungeon* Level::getDungeon() const{
	return l_dungeon;
}

//////////////DISPLAY FUNCTION//////////
void Level::display(std::string msg) const {
	char displayGrid[MAXROWS][MAXCOLS];
	int r, c;

//Fill displayGrid with spaces (empty) and # (walls)
	//walls and spaces were set in constructor 
	for (r = 1; r <= rows(); r++)
		for (c = 1; c <= cols(); c++) {
			int position = getCellStatus(r, c);
			switch (position) {
			case STAIRS:
				displayGrid[r - 1][c - 1] = '>';
				break;
			case WALLS:
				displayGrid[r - 1][c - 1] = '#';
				break;
			default:
				displayGrid[r - 1][c - 1] = ' ';
			}
		}

//Indicate each monster's position//
for (auto monPtr = m_monster.begin(); monPtr != m_monster.end(); ++monPtr)
	{
	//call deleteDeadMons
		char& gridChar = displayGrid[(*monPtr)->row() - 1][(*monPtr)->col() - 1];
		int monsterType = (*monPtr)->getMonsNum();
		switch (monsterType)
		{
		case BG: gridChar = 'B'; break;
		case SW: gridChar = 'S'; break;
		case GB: gridChar = 'G'; break; 
		case DG: gridChar = 'D'; break; 
		}
	}

//Indicate each weapon's position//
for (auto wPtr = m_objects.begin(); wPtr != m_objects.end(); ++wPtr)
{
	int objType = (*wPtr)->getObjectType();
	char& gridChar = displayGrid[(*wPtr)->getObjectRow() - 1][(*wPtr)->getObjectCol() - 1];
	switch (objType)
	{
	case MC:
	case SS:
	case LS:
	case MAGICAXE:
	case MAGICFANGS:
		gridChar = ')';
		break;
	case S_ARMOR:
	case S_DEX:
	case S_HEALTH:
	case S_STRENGTH:
	case S_TELE:
		gridChar = '?';
		break;
	}
}

//Indicate player's position//
	//last because can put on top of objects 
if (l_dungeon->getPlayer() != nullptr)
displayGrid[l_dungeon->getPlayer()->row() - 1][l_dungeon->getPlayer()->col() - 1] = '@';

//clear old
clearScreen();

//Draw the filled grid//
	for (r = 1; r <= rows(); r++)
	{
		for (c = 1; c <= cols(); c++)
			cout << displayGrid[r - 1][c - 1];
		cout << endl;
	}
	cout << endl;

// Write info
	cout << "Dungeon Level: " <<getLevelNum() << ", Hit points:" << l_dungeon->getPlayer()->getHP() << ", Armor:" << l_dungeon->getPlayer()->getArmor() <<
		", Strength: " << l_dungeon->getPlayer()->getStrength() << ", Dexterity: " << l_dungeon->getPlayer()->getDexterity()<<endl<<endl;
	cout << msg; 
}

////////ADDING OBJECTS AND ACTORS////////////

//////////////////////////add a weapon or scroll//////////////
bool Level::addObject(int r, int c, int typeNum) {
	//if position is out of bounds or a wall 
	if (!isPosInBounds(r, c))
		return false;

	//if there is already a weapon there 
	if (getCellStatus(r, c) == OBJECT) {
		return false;
	}

	//if there is a wall 
	if (getCellStatus(r,c)==WALLS) {
		return false;
	}

	//store object in vector 
	if (m_nObjects < maxObjects) {
		string weaponTypeString;
		Weapon* weaponAdd=nullptr;
		Scroll* scrollAdd=nullptr; 
		switch (typeNum) {
			//if a weapon 
		case MC:
			weaponTypeString = mace;
			weaponAdd = new Weapon(this,weaponTypeString, nullptr, r, c,MC);
			m_objects.push_back(weaponAdd);
			break;
		case SS:
			weaponTypeString = shortSword;
			weaponAdd = new Weapon(this,weaponTypeString, nullptr, r, c,SS);
			m_objects.push_back(weaponAdd);
			break;
		case LS:
			weaponTypeString = longSword;
			weaponAdd = new Weapon(this,weaponTypeString, nullptr,  r, c,LS);
			m_objects.push_back(weaponAdd);
			break;

			//if a scroll
		case S_ARMOR:
			scrollAdd = new Scroll(this,nullptr,r,c,S_ARMOR);
			m_objects.push_back(scrollAdd);
			break;
		case S_DEX:
			scrollAdd = new Scroll(this,nullptr,r, c, S_DEX);
			m_objects.push_back(scrollAdd);
			break;
		case S_HEALTH:
			scrollAdd = new Scroll(this,nullptr,r, c, S_HEALTH);
			m_objects.push_back(scrollAdd);
			break;
		case S_STRENGTH:
			scrollAdd = new Scroll(this,nullptr,r, c, S_STRENGTH);
			m_objects.push_back(scrollAdd);
			break;
		case S_TELE:
			scrollAdd = new Scroll(this,nullptr,r, c, S_TELE);
			m_objects.push_back(scrollAdd);
			break;
		}
		m_nObjects++;
		setCellStatus(r, c, OBJECT);
		return true;
	}
	return false;
}

/////////////////////////////////////add a monster/////////////////////
bool Level::addMonster(int r, int c) {
	//if out of bounds 
	if (!isPosInBounds(r, c))
		return false;
	//if there is already an actor there 
	if (getCellStatus(r, c) != EMPTY) {
		return false;
	}

	// Don't add a monster on a spot with a player
	if (l_dungeon->getPlayer() != nullptr && l_dungeon->getPlayer()->row() == r && l_dungeon->getPlayer()->col() == c)
		return false;

	//Don't add a monster where there is already a monster 
	for (size_t i = 0; i < m_monster.size(); ++i) {
		if (m_monster[i]!= nullptr && m_monster[i]->row() == r && m_monster[i]->col() == c) {
			return false;
		}
	}

	/*Bogeymen appear only at dungeon level 2 or deeper.
	Snakewomen may appear on any dungeon level.
	Dragons appear only at dungeon level 3 or deeper.
	Goblins may appear on any dungeon level.*/

	if (m_nMonsters >= maxMonsters) {
		return false;
	}
	//can add monsters 
	else {
		//normally only SW and GB show up 
		int maxMonster = SW;
		//level 2 or higher 
		if (numLevel >= 2) {
			maxMonster = BG;
		}
		//level 3 or higher 
		if (numLevel >= 3) {
			maxMonster = DG;
		}
		//picking a random monster 
		int typeMonster = randInt(GB,maxMonster);
		Monster* toAdd;
		switch (typeMonster) {
		case GB:
			toAdd = new Goblin(this, r, c);
			break;
		case SW:
			toAdd = new Snakewoman(this, r, c);
			break;
		case BG:
			toAdd = new Bogeyman(this, r, c);
			break;
		case DG:
			toAdd = new Dragon(this, r, c);
			break;
		}
		m_monster.push_back(toAdd);
		setCellStatus(r, c, ACTOR);
		m_nMonsters++;
		return true;
	}
}

/////////////MOVE MONSTERS 
std::string Level::moveMonsters(){
	// move all monsters 
	string totalMove=""; 
	for (size_t i = 0; i < m_monster.size(); ++i) {
		//switch case for smell later on 
		totalMove += m_monster[i]->move();
	}
	return totalMove; 
}

///////////////////////////////////
// Helper functions
void Level::checkPos(int r, int c, std::string functionName) const {
	if (!isPosInBounds(r, c))
	{
		if (m_grid[r][c] == '#') {
			cout << "Cannot Insert Player at this position"<<endl;
		}
		else
		{
			cout << "***** " << "Invalid arena position (" << r << ","
				<< c << ") in call to " << functionName << endl;
			exit(1);
		}
	}
}

bool Level::isPosInBounds(int r, int c) const {
	return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
/*	if ((r >= 1 && r <= m_rows && c >= 1 && c <= m_cols) == false || m_grid[r][c] == '#')
		return false;
	return true;*/
}

//change individual cell 
void Level::setCellStatus(int r, int c, int status) {
	checkPos(r, c, "Arena::setCellStatus");
	m_grid[r - 1][c - 1] = status;
}

//checks if it is a wall 
bool Level::isWall(int r, int c) const {
	if (m_grid[r][c] == '#') {
		return true;
	}
	return false;
}

//gives an Actor pointer at a certain position 
Actor* Level::getActor(int r, int c){
	//checking if valid coord 
	//if it is the player at the position, return the player pointer 
	if (l_dungeon->getPlayer()->row() == r && l_dungeon->getPlayer()->col() == c) {
		return l_dungeon->getPlayer();
	}
	//must be a monster 
	for (size_t i = 0; i < m_monster.size(); ++i) {
		if (m_monster[i]->row() == r && m_monster[i]->col() == c) {
			return m_monster[i];
		}
	}
	return nullptr;
}

//checking if there is an object at a position 
GameObject* Level::getObject(int r, int c) {
	for(auto itr = m_objects.begin(); itr!=m_objects.end(); ++itr){
		//only one item in array 
		if (m_objects.size() == 1) {
			if (m_objects.front()->getObjectRow() == r && m_objects.front()->getObjectCol() == c) {
				return m_objects.front();
			}
		}
		//more than one item 
		if ((*itr)->getObjectRow() == r && (*itr)->getObjectCol()) {
			return *itr;
		}
	}
	cout << "no object here" << endl;
	return nullptr;
}

bool Level::isPlayer(int r, int c){
	return (l_dungeon->getPlayer()->row() == r && l_dungeon->getPlayer()->col() == c);
}

void Level::deleteDeadMons() {
	auto itr = m_monster.begin();
	//if nothing in list, all monsters have been destroyed 
	if (itr == m_monster.end()) {
		return;
	}
	if (m_monster.size() == 1) {
		delete *itr; 
	}
	while (itr != m_monster.end()) {
		//RUNTIME ERROR HERE
		if ((*itr)->isDead()) {
			setCellStatus((*itr)->row(),(*itr)->col(),EMPTY);
			itr = m_monster.erase(itr);
		}
		++itr;
	}
}

std::vector<Monster*> Level::getMonsVect() const {
	return m_monster;
}

std::vector<GameObject*> Level::getObjectVect() const {
	return m_objects;
}

//deleting specific object 
void Level::deleteObject(int r, int c){
	auto itr = m_objects.begin();
	//if there is only one object and it needs to be deleted 
	if (m_objects.size() == 1 && (*itr)->getObjectRow() == r && (*itr)->getObjectRow() == c) {
		delete* itr;
	}
	//search the vector for the object 
	while (itr != m_objects.end()) {
		//if this is the same item as the one we want to delete 
		if ((*itr)->getObjectRow() == r && (*itr)->getObjectCol() == c) {
			itr = m_objects.erase(itr);
			break;
		}
	}
	//reach the end without finding the object 
}