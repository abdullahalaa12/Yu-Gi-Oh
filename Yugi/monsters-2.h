#pragma once

#include"Card.h"
 
class Player;

//parent class is the "card" class done by tareq;
//linkedground class is a linkedlist that contains all monster cards objects that is hand or in ground ,it also has the functions that helps getting these cards' objects
//linkedgroundspell class same as linkedground but for spell cards
//the way you summon any monster  from extra deck ,you click on the deck ,all monsters available will appear , then you click on the monster you want to summon ,and then click on the required cards needed to summon this monster
//if you miss click or you didnt click on the right cards the clicking will reset.
class monsterinfo :public Card
{
public:
	enum  TypesE :unsigned char //a group type that the monster belongs to
	{
		aqua, beast, beast_warrior, creatorGOD, cyberse, dinosaur, divine_beast, dragon,
		fairy, fiend, fish, insect, machine, plant, psychic, pyro, reptile, rock, sea_serpent,
		spellcaster, thunder, warrior, winged_beast, wyrm, zombie
	};
	enum  attribute :unsigned char  //element of monster
	{
		dark, divine, earth, fire, light, water, wind
	};

	enum SpecialMonstersummon :unsigned char  //types for special summonin monsters
	{
		tribute, special, ritual, fusion, synchro, xyz, link, pendulum, token
	};

};
class monstersparent: public monsterinfo
{
	bool didattack;
	int attack;
	int deffence;
	int level; 
	char rarity; 
	uint8_t specialtype;
	uint8_t attribute;
	uint8_t type;

public:
	monstersparent();
	void setmonster(); //sets monster in either defence or attack mode
	void SETattack(int attack);
	void SETdefence(int deffence);
	void SETlevel_rarity(int level);
	void SET_attribute(uint8_t attribute);
	void SET_type(uint8_t type);
	void SET_specialtype(uint8_t specialtype);
	int get_attack();
	int get_defence();
	int get_level();
	char get_rarity();
	uint8_t get_attribute();
	uint8_t get_type();
	uint8_t get_specialtype();
	void set_didattack(bool didattack);
	bool get_didattack();
};


class monsterchild :public monstersparent
{
	//bool Animation;
	vector<Card*> THEcards;
	Vector2f Pos;
public:
	static Texture ArrowTex;
	Sprite Arrow;
	monsterchild(int);
	void set
	(int attack, int deffence, int level, uint8_t attribute, uint8_t type);

	bool summontype(Player& player, bool summon);

	bool find(Player&, int);
	void  killem(Player& me, Player& enemy);
};