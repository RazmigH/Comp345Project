#pragma once
#include "Fighter.h"
#include <string>

class Npc : public Fighter {
public:
	Npc(string charName, int equipID, int invID);
	Npc(string charName, int lvl, int equipID, int invID);
	Npc(string charName, int lvl, int maxHP, int currHP,
		int, int, int, int, int, int, int equipID, int invID);
	Npc(string charName, int equipID, int invID, bool hostile, string text);
	Npc(string charName, int lvl, int equipID, int invID, bool hostile, string text);
	Npc(string charName, int lvl, int maxHP, int currHP,
		int, int, int, int, int, int, int equipID, int invID, bool hostile, string text);
	string getTalk() const;
	bool isHostile() const;
	virtual int takeDmg(int);
	virtual void printStats() const;
protected:
	string strTalk;
	bool hostile;
	void getItems();
	void removeFromMap();
};