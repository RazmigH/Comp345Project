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
	Fighter(string charName);
	Fighter(string charName, int lvl);
	Fighter(string charName, int lvl, int, int, int, int, int, int);
	int getAtkBonus() const;
	int getDmgBonus() const;
private:
	void levelUp();
};