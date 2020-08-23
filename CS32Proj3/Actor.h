#ifndef _ACTOR_ 
#define _ACTOR_ 

#include<string>
class Dungeon; 
class Weapon; 
class Monster; 

//BASE CLASS 
class Actor {

	//public function 
public: 
	//DC 
	Actor(int row, int col); 

	//Destructor 
	virtual ~Actor(); 

	//accessors
	int  row() const;
	int  col() const;
	int getHP();
	int getMaxHP(); 
	int getArmor();
	int getStrength();
	int getDexterity();
	std::string getName();

	bool isDead() const;
	bool isSleep() const; 
	Weapon* getWeapon();

	//mutators 
	std::string attack(Actor* defender);
	void setDead();
	void setRow(int row);
	void setCol(int col);
	void setHP(int newHP);
	void setMaxHP(int newMaxHP);
	void setArmor(int newArmor);
	void setStrength(int newStrength);
	void setDex(int newDex);
	void setWeapon(Weapon* weapon);
	void setSleep();
	void setName(std::string name);

	//private member variables 
private: 
	Weapon* m_weapon; 
	int m_row; 
	int m_col; 
	std::string m_name; 
	int m_HP; 
	int maxHP; 
	int m_armor; 
	int m_strength;
	int m_dexterity; 
	int m_sleepTime; 
	bool m_dead; 
	bool m_sleep; 
};

#endif 