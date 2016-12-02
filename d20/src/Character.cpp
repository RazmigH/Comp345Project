//! @file 
//! @brief Implementation file for the Character class  
//!

#include "Character.h"
#include "GameResource.h"
#include "EquipableItem.h"
#include <iostream>

const string Character::IDENTIFIER = "Character";

Character::Character(
	Class characterClass, 
	string characterName, 
	int level,
	int equipmentID,
	int inventoryID,
	bool hostility,
	string talk,
	bool p) 
	: 
	charClass(characterClass), 
	charName(characterName), 
	equipID(equipmentID),
	invID(inventoryID),
	hostile(hostility),
	strTalk(talk),
	player(p),
	dead(false),
	lvl(1)
{
	id = -1;
	for (int i = lvl; i < level; ++i) {
		levelUp();
	}

	// the playr has to be hostile or the monsters won't be able to deal any damage
	if (isPlayer() && !isHostile()) {
		log::messageln("The player must be hostile! Changing to hostile...");
		hostile = true;
	}

	vector<int> scores;
	scores = rollAbilityScores();
	//! sort from low to high in order to decide the assigment priority
	sort(scores.begin(), scores.end());
	//! ability scores are assigned depending on the priority for the
	//! character's class: first one is the lowest
	if (characterClass == FIGHTER) {
		abilityScores[INT] = scores.at(0);
		abilityScores[CHA] = scores.at(1);
		abilityScores[WIS] = scores.at(2);
		abilityScores[DEX] = scores.at(3);
		abilityScores[CON] = scores.at(4);
		abilityScores[STR] = scores.at(5);
	}
	else if (characterClass == ARCHER) {
		abilityScores[INT] = scores.at(0);
		abilityScores[CHA] = scores.at(1);
		abilityScores[WIS] = scores.at(2);
		abilityScores[STR] = scores.at(3);
		abilityScores[CON] = scores.at(4);
		abilityScores[DEX] = scores.at(5);
	}
	maxHP = 10 + getModifier(CON); //! first lvl hp always 10 + constitution modifier
	currentHP = maxHP;

	setName(charName);
	setDown();
	setScale(0.5, 0.5);


	const int r1 = (rand() % 7) + 1;
	for (int i = 0; i < r1; i++) {
		int r2 = (rand() % 7);
		Item::Equipable type = static_cast<Item::Equipable>(r2);

		int r3 = (rand() % 11);
		Item::ItemStats stat = static_cast<Item::ItemStats>(r3);

		int bonus = (rand() % 15) + 1;

		spEquipableItem item = new EquipableItem(type);
		item->setStat(stat);
		item->setBonus(bonus);

		tempInventory.push_back(item);
	}
}

Character::~Character() {

}

Character* Character::createCharacter() {

	string n = "", t = "Good luck!";
	Class c = FIGHTER;
	int lv = 1, option;
	bool h = false, p = false;

	cout << "Please fill the form to create a character" << endl;
	cout << "Choose an option for your character class 1->Fighter 2->Archer" << endl;
	cout << "Your choice: ";
	cin >> option;
	switch (option) {
	case 1: c = FIGHTER;
	case 2: c = ARCHER;
	}
	cout << "Enter the name of your character: ";
	cin >> n;
	cout << "Enter the level of your character: ";
	cin >> lv;
	cout << "Should your character be hostile 1->Yes 2->No" << endl;
	cout << "Your choice: ";
	cin >> option;
	switch (option) {
	case 1: h = true;
	case 2: h = false;
	}
	cout << "Enter something your character could say: ";
	cin >> t;
	cout << "Is your character a player 1->Yes 2->No" << endl;
	cout << "Your choice: ";
	cin >> option;
	switch (option) {
	case 1: p = true;
	case 2: p = false;
	}

	return new Character(c, n, lv, 0, 0, h, t, p);
}

vector<int> Character::rollAbilityScores() const {
	vector<int> scores = {};
	for (int i = 0; i < NUM_STATS; ++i) {
		vector<int> rolls;
		for (int j = 0; j < 4; ++j) {
			rolls.push_back(die.roll6());
		}
		sort(rolls.begin(), rolls.end()); //! sort ascending order
		int stat = 0;
		//! skip the first roll, because he's the smallest one after the sort
		for (int i = 1; i < 4; ++i) {
			stat += rolls.at(i);
		}
		scores.push_back(stat);
	}
	
	log::messageln("Character stats roll result: ");
	for (int i = 0; i < scores.size(); ++i) {
		log::messageln("%d ",scores.at(i));
	}
	log::messageln("");

	return scores;
}

int Character::rollHP() const {
	return die.roll10();
}

int Character::calcModifier(int num) const {
	//! lowest modifier for any number below 0
	if (num <= 0) {
		return -5;
	}
	//! negative modifiers below 10
	else if (num < 10) {
		return (num - 11) / 2;
	}
	else {
		return (num - 10) / 2;
	}
}

int Character::takeDmg(int dmg) {
	if (!isHostile()) {
		log::messageln("Cannot attack a non-hostile enemy!");
		return currentHP;
	}

	currentHP -= dmg;
	if (currentHP <= 0) {
		dead = true;

		if (isPlayer()) {
			endGame();
			return -2;
		}
		else {
			log::messageln("%s was killed!",getName());
			// drops the loot and has to disapear from the map
			return -1;
		}
	}
	return currentHP;
}

void Character::endGame() {

}

int Character::getId() const{
	return id;
}
void Character::setId(int id) {
	this->id = id;
}

int Character::getLevel() const {
	return lvl;
}

void Character::setLevel(int level) {
	lvl = level;
}

int Character::getInvID() const {
	return invID;
}

void Character::setInvID(int id) {
	invID = id;
}

int Character::getEquipID() const {
	return equipID;
}

void Character::setEquipID(int id) {
	equipID = id;
}

int Character::getStat(Stats stat) const {
	return abilityScores[stat];
}

void Character::setStat(Stats stat, int value) {
	abilityScores[stat] = value;
}

int Character::getModifier(Stats stat) const {
	return calcModifier(abilityScores[stat]);
}

Character::Class Character::getCharacterClass() const {
	return charClass;
}

void Character::setCharacterClass(Class c)
{
	this->charClass = c;
	setDown();
}

int Character::getArmor() const {
	return armor + getModifier(DEX);
}

int Character::getHP() const {
	return currentHP;
}

void Character::setHP(int hp) {
	this->currentHP = hp;
}

int Character::getMaxHP() const {
	return maxHP;
}

void Character::setMaxHP(int hp) {
	maxHP = hp;
}

bool Character::isDead() const {
	return (dead == true) ? true : false;
}

//! TODO: prob will not be used for the project
int Character::statChooser() const {
	log::messageln("Please choose the stat: ");
	log::messageln("Strength -> 1");
	log::messageln("Condition -> 2");
	log::messageln("Dexterity -> 3");
	log::messageln("Intelligence -> 4");
	log::messageln("Wisdom -> 5");
	log::messageln("Charisma -> 6");
	log::messageln("Input the number corresponding to your choice: ");
	int choice = 1;
	cin >> choice;
	switch (choice) {
	case 1: return STR; break;
	case 2: return CON; break;
	case 3: return DEX; break;
	case 4: return INT; break;
	case 5: return WIS; break;
	case 6: return CHA; break;
	default: log::messageln("Invalid choice! Try again...");
	return statChooser();
	}
}
bool Character::validateNewCharacter() {
	for (int i = 0; i < NUM_STATS; ++i) {
		if (abilityScores[i] < (3 + lvl/4) || abilityScores[i] > (18 + lvl/4)) {
			return false;
		}
	}
	return true;
}

string Character::getNameCharacterClass() const {
	switch (charClass) {
	case FIGHTER: return "Fighter";
	case ARCHER: return "Archer";
	default: return "BlaBla";
	}
}

void Character::printStats() const {
	log::messageln("****Character Info****");
	log::messageln("Id: ");
	log::messageln("Name: %s", getName());
	log::messageln("Level: %d", getLevel());
	log::messageln("Class: %s", getNameCharacterClass());
	log::messageln("Max HP: %d", getMaxHP());
	log::messageln("Current HP: %d", getHP());
	log::messageln("Strength: %d", abilityScores[STR]);
	log::messageln("Constitution: %d", abilityScores[CON]);
	log::messageln("Dexterity: %d", abilityScores[DEX]);
	log::messageln("Inteligence: %d", abilityScores[INT]);
	log::messageln("Wisdom: %d", abilityScores[WIS]);
	log::messageln("Charisma: %d", abilityScores[CHA]);
	log::messageln("Equipment ID: %d", getEquipID());
	log::messageln("Inventory ID: %d", getInvID());
	log::messageln("Talk: %s", getTalk());
	log::messageln("Hostile: %d", isHostile());
	log::messageln("Player: %d", isPlayer());
}

int Character::getArmorVar() const {
	return armor;
}

void Character::setArmorVar(int val) {
	armor += val;
}

int Character::getAtkBonusVar() const {
	return atkBonus;
}

void Character::setAtkBonusVar(int val) {
	atkBonus += val;
}

int Character::getDmgBonusVar() const {
	return dmgBonus;
}

void Character::setDmgBonusVar(int val) {
	dmgBonus += val;
}

//! TODO: modify to take in account the weapon for the modifier
int Character::getAtkBonus() const {
	if (charClass == ARCHER) {
		return die.roll20() + atkBonus + getModifier(DEX);
	}
	else {
		return die.roll20() + atkBonus + getModifier(STR);
	}
}

//! TODO: modify to take in account the weapon for the modifier
int Character::getDmgBonus() const {
	if (charClass == ARCHER) {
		return die.roll6() + dmgBonus + getModifier(DEX);
	}
	else {
		return die.roll6() + dmgBonus + getModifier(STR);
	}
}

//! Character::levelUP() -> increases the level, increases the hp, assigns an ability point
//! every 4 levels (alternates between strength-condition)
void Character::levelUp() {
	++lvl;
	log::messageln("Level up! Level %d reached!", lvl);
	maxHP += die.roll10() + getModifier(CON);
	currentHP = maxHP;

	if (charClass == ARCHER) {
		if (lvl % 4 == 0) {
			if (lvl % 8 == 0) {
				abilityScores[CON] += 1;
			}
			else {
				abilityScores[DEX] += 1;
			}
		}
	}
	else {
		if (lvl % 4 == 0) {
			if (lvl % 8 == 0) {
				abilityScores[CON] += 1;
			}
			else {
				abilityScores[STR] += 1;
			}
		}
	}
}


bool Character::isHostile() const {
	return hostile;
}

void Character::setHostile(bool h) {
	hostile = h;
}

string Character::getTalk() const {
	return strTalk;
}

void Character::setTalk(string t) {
	strTalk = t;
}

string Character::getName() const{
	return charName;
}

void Character::setName(string name) {
	charName = name;
}

bool Character::isPlayer() const {
	return (player == true) ? true : false;
}

int Character::inflictDamage(Character& c) {
	
	int dmg = 0;
	//! TODO: calc for damage

	c.takeDmg(dmg);
	
	return dmg;
}

void Character::setUp() {
	switch (charClass) {
	case FIGHTER:
		setResAnim(res::resources.getResAnim("character"), 0, 4);
		break;
	case ARCHER:
		setResAnim(res::resources.getResAnim("character"), 0, 16);
		break;
	default:
		setResAnim(res::resources.getResAnim("character"), 0, 0);
		break;
	}
	facing = Map::Direction::NORTH;
}

void Character::setDown() {
	switch (getCharacterClass()) {
	case FIGHTER:
		setResAnim(res::resources.getResAnim("character"), 0, 6);
		break;
	case ARCHER:
		setResAnim(res::resources.getResAnim("character"), 0, 18);
		break;
	default:
		setResAnim(res::resources.getResAnim("character"), 0, 2);
		break;
	}
	facing = Map::Direction::SOUTH;
}

void Character::setLeft() {
	switch (charClass) {
	case FIGHTER:
		setResAnim(res::resources.getResAnim("character"), 0, 5);
		break;
	case ARCHER:
		setResAnim(res::resources.getResAnim("character"), 0, 17);
		break;
	default:
		setResAnim(res::resources.getResAnim("character"), 0, 1);
		break;
	}
	facing = Map::Direction::WEST;
}

void Character::setRight() {
	switch (charClass) {
	case FIGHTER:
		setResAnim(res::resources.getResAnim("character"), 0, 7);
		break;
	case ARCHER:
		setResAnim(res::resources.getResAnim("character"), 0, 19);
		break;
	default:
		setResAnim(res::resources.getResAnim("character"), 0, 3);
		break;
	}
	facing = Map::Direction::EAST;
}

Map::Direction Character::getFacing() {
	return facing;
}


//semi-temp
vector<spItem> Character::getInventory() {
	return tempInventory;
}
vector<spEquipableItem> Character::getEquipment() {
	return tempEquipment;
}
void Character::addToInventory(spItem item) {
	tempInventory.push_back(item);
	notify();
}

void Character::removeFromInventory(spItem item) {
	for (vector<spItem>::iterator it = tempInventory.begin(); it != tempInventory.end(); ++it) {
		if (item->getObjectID() == (*it)->getObjectID()) {
			tempInventory.erase(it);
			break;
		}
	}
	notify();
}

void Character::equip(spEquipableItem item) {
	log::messageln("EQUIPPING ITEM WITH %d", item->getBonus());
	//find same object type and unequip
	for (vector<spEquipableItem>::iterator it = tempEquipment.begin(); it != tempEquipment.end(); ++it) {
		if (item->getType() == (*it)->getType()) {
			log::messageln("ALREADY WEARING ITEM WITH %d", (*it)->getBonus());
			unequip(*it);
			break;
		}
	}

	removeFromInventory(item);
	tempEquipment.push_back(item);
	notify();
}

void Character::unequip(spEquipableItem item) {
	for (vector<spEquipableItem>::iterator it = tempEquipment.begin(); it != tempEquipment.end(); ++it) {
		if (item->getObjectID() == (*it)->getObjectID()) {
			tempEquipment.erase(it);
			break;
		}
	}
	addToInventory(item);
	notify();
}

tinyxml2::XMLElement* Character::getXML(Xml* xml) {
	XMLElement* root = xml->createElement(IDENTIFIER);

	if (getId() != -1) {
		root->SetAttribute("id", getId());
	}
	root->SetAttribute("col", getLocation().x);
	root->SetAttribute("row", getLocation().y);

	const int ATTRIBUTE_COUNT = 15;
	string attributes[ATTRIBUTE_COUNT][2] = {
		{ "Class",			classToString(getCharacterClass()) },
		{ "Name",			getName() },
		{ "Level",			to_string(getLevel()) },
		{ "MaxHP",			to_string(getMaxHP()) },
		{ "CurrentHP",		to_string(getHP()) },
		{ "Strength",		to_string(getStat(Character::Stats::STR)) },
		{ "Constitution",	to_string(getStat(Character::Stats::CON)) },
		{ "Dexterity",		to_string(getStat(Character::Stats::DEX)) },
		{ "Intelligence",	to_string(getStat(Character::Stats::INT)) },
		{ "Wisdom",			to_string(getStat(Character::Stats::WIS)) },
		{ "Charisma",		to_string(getStat(Character::Stats::CHA)) },
		{ "EquipmentID",	to_string(getEquipID()) }, //that line was missing 
		{ "InventoryID",    to_string(getInvID()) },
		{ "Hostile",		isHostile() ? "1" : "0" },
		{ "Talk",			getTalk() }
	};

	for (int i = 0; i < ATTRIBUTE_COUNT; i++) {
		XMLElement* classEle = xml->createElement(attributes[i][0]);
		classEle->SetText(attributes[i][1].c_str());
		root->InsertEndChild(classEle);
	}

	return root;
}

spTile Character::getFromXML(XMLElement* element) {
	spCharacter c = new Character();

	const char* idstr = element->Attribute("id");
	if (idstr != nullptr) {
		c->setId(atoi(idstr));
	}

	const char* col = element->Attribute("col");
	const char* row = element->Attribute("row");
	if (col != nullptr && row != nullptr) {
		c->setLocation(stoi(col), stoi(row));
	}

	int i;

	XMLElement* temp = element->FirstChildElement("Class");
	if (temp != nullptr) {
		c->setCharacterClass(stringToClass(temp->GetText()));
	}

	temp = element->FirstChildElement("Name");
	if (temp != nullptr) {
		c->setName(temp->GetText() == nullptr ? "Good luck!" : temp->GetText());  // one more bug fixed: c->getName() 
	}

	temp = element->FirstChildElement("Level");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setLevel(i);
	}

	temp = element->FirstChildElement("MaxHP");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setMaxHP(i);
	}

	temp = element->FirstChildElement("CurrentHP");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setHP(i);
	}

	temp = element->FirstChildElement("Strength");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setStat(Character::Stats::STR, i);
	}

	temp = element->FirstChildElement("Constitution");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setStat(Character::Stats::CON, i);
	}

	temp = element->FirstChildElement("Dexterity");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setStat(Character::Stats::DEX, i);
	}

	temp = element->FirstChildElement("Intelligence");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setStat(Character::Stats::INT, i);
	}

	temp = element->FirstChildElement("Wisdom");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setStat(Character::Stats::WIS, i);
	}

	temp = element->FirstChildElement("Charisma");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setStat(Character::Stats::CHA, i);
	}

	temp = element->FirstChildElement("EquipmentID");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setEquipID(i);
	}

	temp = element->FirstChildElement("InventoryID");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setInvID(i);
	}

	temp = element->FirstChildElement("Hostile");
	if (temp != nullptr && temp->QueryIntText(&i) == XML_SUCCESS) {
		c->setHostile((i == 1) ? true : false);
	}

	temp = element->FirstChildElement("Talk");
	if (temp != nullptr) {
		c->setTalk(temp->GetText() == nullptr ? "" : temp->GetText());
	}

	return c;
}

string Character::classToString(Character::Class c) {
	switch (c) {
	case Character::Class::FIGHTER:
		return "fighter";
		break;
	case Character::Class::ARCHER:
		return "archer";
		break;
	default:
		return "Error: undefined Class " + c;
		break;
	}
}

Character::Class Character::stringToClass(string c) {
	if (c == "fighter") {
		return Character::Class::FIGHTER;
	}
	else if (c == "archer") {
		return Character::Class::ARCHER;
	}
	else {
		return Character::Class::BLABLA;
	}
}

string Character::getIdentifier() {
	return IDENTIFIER;
}

void Character::setInteractFrom(Map::Direction dir) {
	interactFrom = dir;
}

void Character::interact() {
	log::messageln("CHARACTER INTERACT");
	switch (interactFrom) {
	case Map::NORTH:
		setUp();
		break;
	case Map::EAST:
		setRight();
		break;
	case Map::SOUTH:
		setDown();
		break;
	case Map::WEST:
		setLeft();
		break;
	default: 
		setDown();
		break;
	}
}