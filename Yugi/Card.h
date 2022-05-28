#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include<time.h>

using namespace std;
using namespace sf;

class Card
{
	int Card_iD;
	int player;
	Texture FrontTex;
	char Type;
	char Place;
	string Card_Name;
	bool Activate;
	Vector2<float> Position;

public:
	static Texture BackTex;
	static int Count;

	Card();
	void SetFrontCard(string);
	void SetType(char);
	void SetPlace(char);
	void SetCardName(string);
	void SetActivate(bool);
	void SetPosition(Vector2<float>);
	void SetPlayer(int);
	Texture* getFrontCard();
	char getType();
	char getPlace();
	string GetCardName();
	bool GetActivate();
	Vector2<float> getPosition();
	Sprite GetCardSprite();
	int getPlayer();
	bool* TheSelect(string);
	~Card();
};
