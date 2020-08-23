// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
#include"Level.h"
#include"utilities.h"
#include"Player.h"
#include"GameObjects.h"
using namespace std;

// Implement these and other Game member functions you may have added.
Game::Game(int goblinSmellDistance):goblinSmellDistance(goblinSmellDistance){
	g_dungeon = new Dungeon();
	Level* newLevel = new Level(g_dungeon, 0, 18, 70);
	g_dungeon->setLevel(newLevel);

	// Add player
	int rPlayer;
	int cPlayer;
	rPlayer = randInt(2, 18);
	cPlayer = randInt(2, 70);
	do
	{
		rPlayer = randInt(2, 18);
		cPlayer = randInt(2, 70);
	} while (g_dungeon->getLevel()->getCellStatus(rPlayer, cPlayer) != EMPTY);
	g_dungeon->addPlayer(rPlayer, cPlayer);

	// Populate with monsters
	for(int i =0; i<= g_dungeon->getLevel()->getMaxMonster(); ++i)
	{
		int r = randInt(2, 18);
		int c = randInt(2, 70);
		if (r == rPlayer && c == cPlayer)
			continue;
		g_dungeon->getLevel()->addMonster(r, c);
	}

//populate with objects 
for (int j = 0; j <= g_dungeon->getLevel()->getMaxObjects(); ++j) {
	int r = randInt(2, 18);
	int c = randInt(2, 70);
	g_dungeon->getLevel()->addObject(r, c, randInt(MC,S_DEX));
}

}

void Game::play()
{
	g_dungeon->getLevel()->display("");
	Player* player = g_dungeon->getPlayer();
	if (player == nullptr)
		return;
	//while the player is not dead 
	while (!player->isDead()) {
		string msg = takePlayerTurn();
		msg += '\n';
		if (player->isDead())
			break;
		g_dungeon->getLevel()->deleteDeadMons();
		msg+=g_dungeon->getLevel()->moveMonsters();
		msg += '\n';
		g_dungeon->getLevel()->display(msg);
	}
	cout << "Press q to exit game." << endl;
	while (getCharacter() != 'q')
		;
}

std::string Game::takePlayerTurn() {
	for (;;) {
		//enter a move 
		char action = getCharacter();

			int numDir; 
			switch (action) {
			case ARROW_LEFT:
			case ARROW_DOWN:
			case ARROW_RIGHT:
			case ARROW_UP:
				decodeDirection(action, numDir);
				//make this a string, then loop the monster vector and append to string 
				return g_dungeon->getPlayer()->move(numDir);
				break;
			case 'g':
				if (g_dungeon->getLevel()->getObject(g_dungeon->getPlayer()->row(), g_dungeon->getPlayer()->col())!=nullptr) {
					GameObject* toGet = g_dungeon->getLevel()->getObject(g_dungeon->getPlayer()->row(), g_dungeon->getPlayer()->col());
					std::vector<GameObject*> playerInvent = g_dungeon->getPlayer()->getInvent();
					std::string msg = "";
					//if the inventory is smaller than limit 
					if (playerInvent.size() < 25) {
						//add object onto player's inventory 
						msg+=g_dungeon->getPlayer()->pickObj();
						//get rid of scroll/object from screen by deleting the object from level's object vector 
						g_dungeon->getLevel()->deleteObject(g_dungeon->getPlayer()->row(), g_dungeon->getPlayer()->col());
					}
					//setcell to empty 
					g_dungeon->getLevel()->setCellStatus(g_dungeon->getPlayer()->row(), g_dungeon->getPlayer()->col(), EMPTY);
					return msg;
				}
				else { 
					return ""; 
				}

				/*If that character is a letter labeling a weapon, then that weapon becomes the player's current weapon (and the previous weapon remains in the inventory);
				otherwise, the current weapon is not changed.*/
			case 'w':
				return "";
			case 'r':
				return "";
			case 'i':
				clearScreen();

				//goes through the number of player objects 
				//26 - g_dungeon->getPlayer()->getInvent().size() is used to generate corresponding letter char 
				cout << "Inventory:" << endl;
				for (size_t i = 'a'; i <= 'z' - (26 - g_dungeon->getPlayer()->getInvent().size()); ++i) {
					//gets the object we are currently on in the loop 
					GameObject* current = g_dungeon->getPlayer()->getInvent()[i - 'a'];
					//Try to convert current to a weapon pointer 
					Weapon* wp = dynamic_cast<Weapon*>(current);
					//if wp is not null, wp points to a weapon 
					if (wp != nullptr)
						cout << char(i) << '.' << (*wp).getNameWeap() << endl;
					//wp points to a scrolls 
					else {
						//convert current to a scroll 
						//POTENTIAL ERROR
						Scroll* sp = dynamic_cast<Scroll*>(current);
						cout << char(i) << '.' << (*sp).getNameScroll() << endl;
					}
				}
				//get back to display screen, monsters are still moving by default 
				return takePlayerTurn();

				//quit the game 
			case 'q':
				//	g_dungeon->getPlayer()->setHP(0);
				exit(1);

				//cheat : player strength 9, maxHP 50 
			case 'c':
				g_dungeon->getPlayer()->setMaxHP(50);
				g_dungeon->getPlayer()->setHP(50);
				g_dungeon->getPlayer()->setStrength(9);
				return "";
			default:
				//If you type something not on this list, you do nothing for this turn, but the monsters take their turn.
				return g_dungeon->getLevel()->moveMonsters();
			}
			
	}
}

bool Game::decodeDirection(char ch, int& dir)
{
	switch (tolower(ch))
	{
	default:  return false;
	case ARROW_UP: dir = NORTH; break;
	case ARROW_RIGHT: dir = EAST;  break;
	case ARROW_DOWN: dir = SOUTH; break;
	case ARROW_LEFT: dir = WEST;  break;
	}
	return true;
}

Game::~Game() {
}