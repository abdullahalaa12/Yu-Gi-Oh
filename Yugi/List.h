#pragma once

#include"Spell.h"
#include"Trap.h"
#include"monsters-2.h"
#include"Rec.h"
#include<list>
#include<vector>

class Deck
{
	vector<Card*> deck;
	Sprite* Spr;
	int capacity;
	Card* newSpell(int);
	Card* newTrap(int);
public:
	Deck(int, int);
	void Draw(RenderWindow&);
	Card* TakeCard();
	void Shuffle();
	void AddCard(Card*);
	int getSize();
	~Deck();
};




class Graveyard
{
	vector<Card*> Grave;
	Sprite* Spr;
	RectangleShape Container;
	Sprite* Next, *Prev;
	Texture N, P;
	int Page;
	void Sort(int);

public:

	int MonsterSize;
	int CardSize;
	bool Show;
	Graveyard(int, allmap*);
	void Draw(RenderWindow&);
	void Click(RenderWindow&);
	bool AddCard(Card*);
	Card* DisplayCard(int);
	Card* DisplayCard(Vector2<float>);
	Card* TakeCard(int);
	Card* TakeCard(Card*);
	int getSize();
	~Graveyard();
};





class Hand
{
	list<Card*> _list;
	int capacity;
	float Y;
	allmap* Map;
	void Sort();

public:
	Hand(int, int, allmap*);
	void Draw(RenderWindow&);
	void setCapacity(int);
	int getCapacity();
	bool AddCard(Card*);
	Card* DisplayCard(int);
	Card* DisplayCard(Vector2<float>);
	Card* TakeCard(int);
	Card* TakeCard(Card*);
	int getSize();
	~Hand();
};



class Ground
{
	list<Card*> _list;
	int capacity;
	int MonsterSize;
	int CardSize;
	int mRow;
	int cRow;
	allmap* Map;

public:
	Ground(int, int, allmap*);
	void Draw(RenderWindow&);
	bool AddCard(Card*);
	Card* DisplayCard(int);
	Card* DisplayCard(Vector2<float>);
	Card* TakeCard(int);
	Card* TakeCard(Card*);
	int getSize();
	int getMonsterSize();
	int getCardSize();
	~Ground();
};