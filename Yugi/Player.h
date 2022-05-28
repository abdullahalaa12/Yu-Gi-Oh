#pragma once

#include"List.h"


#define HandCapacity  15
#define GroundCapacity 10
#define DeckCapacity 40

class Player
{
	RectangleShape HealthContainer;
	RectangleShape HealthBar;
	string lf;
	Text PointsText;
public:
	Player(int, allmap*);
	void Draw(RenderWindow& window);
	void DecreaseLifePoints(int);
	void IncreaseLifePoints(int);
	int LifePoints;
	Font font;
	Deck Deck;
	Hand Hand;
	Ground Ground;
	Graveyard Graveyard;
	~Player();
};