// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include"Dungeon.h"
#include<string>
// You may add data members and other member functions to this class.

class Game
{
public:
	Game(int goblinSmellDistance);
	~Game(); 
	void play();
	std::string takePlayerTurn();
	bool decodeDirection(char ch, int& dir);
private:
	int goblinSmellDistance = 0; 
	Dungeon* g_dungeon; 
};

#endif // GAME_INCLUDED