#ifndef _CONSTANTS_ 
#define _CONSTANTS_ 

#include"utilities.h"
#include<string>

const int MAXROWS = 18;                // max number of rows in the arena
const int MAXCOLS = 70;                // max number of columns in the arena
const int INITIAL_VAMPIRE_HEALTH = 2;  // initial vampire health //EXPAND FOR ALL THE MONSTERS? 
const int POISONED_IDLE_TIME = 1;      // poisoned vampire idles this many turns //SOMETHING SIMILAR??	
									   //   between moves
//PLAYER STATS 
const int INITIAL_PLAYER_HP = 20;
const int INITIAL_PLAYER_ARMOR = 2;
const int INITIAL_PLAYER_STRENGTH = 2;
const int INITIAL_PLAYER_DEX = 2; 

//WEAPON NAMES FOR WEAPON CLASS 
const std::string shortSword = "short sword";
const std::string longSword = "long sword";
const std::string mace = "mace";
const std::string axe = "magic axe";
const std::string fangs = "magic fangs of sleep";
const std::string maceAction = "swings mace at";
const std::string longSwordAction = "swings long sword at";
const std::string shortSwordAction = "slashes short sword at";
const std::string axeAction = "chops magic axe at";
const std::string fangsAction = "strikes magic fangs at";

const int MACE_DEX_BONUS = 0; 
const int MACE_DAMAGE = 2; 
const int SHORTSWORD_DEX_BONUS = 0; 
const int SHORTSWORD_DAMAGE = 2;
const int LONGSWORD_DEXBONUS = 2; 
const int LONGSWORD_DAMAGE = 4; 
const int AXE_DEX_BONUS = 5; 
const int AXE_DAMAGE = 5; 
const int FANGS_DEX_BONUS = 3; 
const int FANGS_DAMAGE = 2;

//MOVING
const int NORTH = 0;
const int EAST = 1;
const int SOUTH = 2;
const int WEST = 3;
const int NUMDIRS = 4;

//INDICATORS FOR DISPLAY 
const int EMPTY = 0;
const int WALLS = 1;
const int OBJECT = 2; 
const int ACTOR = 3;
const int STAIRS = 4; 

//MONSTER CONSTANTS 
const int GB = 0;
const int SW = 1;
const int BG = 2;
const int DG = 3; 

//OBJECT CONSTANTS
const int MC = 0;
const int SS = 1;
const int LS = 2; 
const int S_ARMOR = 3;
const int S_STRENGTH = 4; 
const int S_HEALTH = 5; 
const int S_DEX = 6; 
const int MAGICAXE = 7; 
const int MAGICFANGS = 8; 
const int S_TELE= 9;

#endif 