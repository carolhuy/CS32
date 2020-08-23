#include"helper.h"
#include"Actor.h"
#include"constants.h"
#include"Level.h"
#include<iostream>
#include"Dungeon.h"

std::string attemptMove(Level* a, Actor* actor, int dir, int r, int c) {
	int rnew = r;
	int cnew = c;

	//set old cell to whatever it was previously
	//if previously empty: walk on it again 
	//wouldnt it set to Actor? 

	//check if there is an item on this
	int oldStatus = a->getCellStatus(r, c);
	a->setCellStatus(r,c,EMPTY);

	switch (dir)
	{
		// if out of bounds, don't move
		//add something here about actors?

	case NORTH: 
		if (r <= 1)
			return "";
		else rnew--; 
		break;
	case EAST:   
		if (c >= a->cols()) 
			return "";
		else cnew++; 
		break;
	case SOUTH:  
		if (r >= a->rows()) 
			return "";
		else rnew++; 
		break;
	case WEST:   
		if (c <= 1)        
			return "";
		else cnew--; 
		break;
	}
int status = a->getCellStatus(rnew, cnew);
std::string msg; 
	switch (status) {
	case WALLS:
		return "";
		break;
	case ACTOR:
		//check what kind of actor the rnew and cnew is 

		//if the current actor is a player, and the new actor is a monster 
		if (a->isPlayer(r, c) && !a->isPlayer(rnew, cnew)) {
			//player attack the monster
			msg = actor->attack(a->getActor(rnew, cnew));
			//do not move to new position 
			rnew = r;
			cnew = c;

		}

		//if current actor is monster, and the new actor is player 
		else if (!a->isPlayer(r, c) && a->isPlayer(rnew, cnew)) {
			//monster attack player 
			msg = actor->attack(a->getActor(rnew, cnew));
			//do not move to new position 
			rnew = r;
			cnew = c;
		}

		//if current is a monster and new actor is another monster 
		//if (!a->isPlayer(r, c) && !a->isPlayer(rnew, cnew)) 
		else{
			//do not move to new position 
			rnew = r;
			cnew = c;
			//do not attack 
			msg = "";
		}
		break;
	case EMPTY:
	case OBJECT:
		//switch here for picking up weapon
		actor->setRow(rnew);
		actor->setCol(cnew);
		msg = "";
		break;
	case STAIRS:
		//dungeon and actor 
		while (a->getLevelNum() < 4)
		{
			//increment the level 
			Level* newLevel = new Level(a->getDungeon(), a->getLevelNum() + 1, 18, 70);
			//store old level 
			Level* currLevel = a;
			//have dungeon point to new level 
			a->getDungeon()->setLevel(newLevel);
			//player is still in old level 
			//making a new player on the new level 
			int rPlayer;
			int cPlayer;
			rPlayer = randInt(2, 18);
			cPlayer = randInt(2, 70);
			do
			{
				rPlayer = randInt(2, 18);
				cPlayer = randInt(2, 70);
			} while (a->getDungeon()->getLevel()->getCellStatus(rPlayer, cPlayer) != EMPTY);
			a->getDungeon()->addPlayer(rPlayer, cPlayer);
			//delete old level 
			delete currLevel;
		}
	msg = "";
	}

	//set new cell to indicate has a player/monster 
	a->setCellStatus(rnew, cnew, ACTOR);
	return msg;
}