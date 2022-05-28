#pragma once
#include"Rec.h"

class MessageMenue
{
	RectangleShape Menue;
	Text Message, Yes, No;
public:
	Font font;
	bool Show;
	MessageMenue();
	void setMessage(string);
	bool YesClicked(RenderWindow&);
	bool NoClicked(RenderWindow&);
	void Draw(RenderWindow&);
	~MessageMenue();

};

class Menue
{
	bool Show;
	int* Phase;
	RectangleShape Container;
	Text Message, Button[4];
	void set();
	int Mouse(RenderWindow&);
public:
	void Open();
	bool getShow();
	Menue(int*);
	void Draw(RenderWindow&);
	void Click(RenderWindow&);
	~Menue();
};