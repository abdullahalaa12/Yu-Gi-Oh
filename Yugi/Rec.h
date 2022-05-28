#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include<vector>

//ratio of spaces in window
#define RowRec 4
#define ColRec 5
#define windowX  1366
#define windowy  768
#define spaceBETGcards 30.f
#define viewgroundcardsX 291.f
#define viewgroundcardsY 424.f
#define HandHeight 143.f
#define HandWidth 1250.f
#define GroundCardHight 127.f
#define GroundCardwidth 87.f
#define handcardWIDTH 90.f
#define handcardHEIGHT 127.f
#define spaceBETHcards 7.f

using namespace sf;
using namespace std;
//our ground white-rectangles properties
class rectangleclss
{
	RectangleShape rec;
public:
	rectangleclss();
	RectangleShape setRectangle();
};




//class that creates the whole game map and index
class allmap
{
	int n; //number of spaces bet. cards on ground
	int nn;//number of cards in same row on the ground
	int hh; //number of row
	int middlespace; //space between ground of player1 and player2
public:
	//the white rectangles
	rectangleclss recproperties;
	RectangleShape rec[RowRec][ColRec];
	//positioning
	vector<Vector2<float>> position; // i made it vector type so we can save the positions of cards on the play ground and so (we will enum it later ,and for every position we will put a name like"top left card" in the enum)

	//view screen of ground cards -------------------> (there will be view screen for ground cards and other view screen that views hand cards, they are in 2 different position)
	RectangleShape viewground;

	Texture backgroundTEXTURE;
	Sprite background;


	allmap();
	void Draw(RenderWindow&,int);
};