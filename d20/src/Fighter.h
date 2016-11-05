//! @file 
//! @brief Header file for Fihgher class  
//!

#pragma once
#include <string>
#include "Character.h"

using namespace std;

//! Fighter class derived from Character
class Fighter : public Character {
public:
	Fighter(string charName, int equipID, int invID);
	Fighter(string charName, int lvl, int equipID, int invID);
	Fighter(string charName, int lvl, int maxHP, int currHP, 
		int, int, int, int, int, int, int equipID, int invID);
	int getAtkBonus() const;
	int getDmgBonus() const;
private:
	void levelUp();
};