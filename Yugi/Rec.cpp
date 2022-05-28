#include "Rec.h"



rectangleclss::rectangleclss()
{
	rec.setFillColor(Color(255, 255, 255, 50));
	rec.setOutlineThickness(2.f);
	rec.setSize(Vector2f(GroundCardwidth, GroundCardHight));


}

RectangleShape rectangleclss::setRectangle()
{
	return rec;
}

allmap::allmap()
{//the white rectangles properties
	n = 1; //number of spaces bet. cards on ground
	nn = 0;//number of cards in same row on the ground
	hh = 1; //number of row
	middlespace = 0; //space between ground of player1 and player2
	for (int i = 0; i < RowRec; i++)
	{
		for (int j = 0; j < ColRec; j++)
		{

			position.push_back(Vector2f(90 + (viewgroundcardsX + n * spaceBETGcards + nn * GroundCardwidth)
				, (windowy - HandHeight - hh * GroundCardHight - hh * 1 - middlespace) + 30));
			rec[i][j] = recproperties.setRectangle();
			rec[i][j].setPosition(position[(i * ColRec) + j]);



			n = n % 5; n++;  nn++;  nn = nn % 5;
			if (nn == 0)
			{
				hh++;
			}
			if (hh > 2)
			{
				middlespace = 10;
			}
		}
	}

	// view screen of ground cards properties
	viewground.setFillColor(Color(255, 255, 255, 50));
	viewground.setOutlineThickness(2.f);
	viewground.setPosition(0, HandHeight + 30);
	viewground.setSize(Vector2f(viewgroundcardsX, viewgroundcardsY));

	//background properties
	backgroundTEXTURE.loadFromFile("Images/background.jpg");


	background.setTexture(backgroundTEXTURE);
	//background.setScale(/*1250.f / 1920.f, 710.f / 1080.f*/);
	background.setPosition(0, 0);

}

void allmap::Draw(RenderWindow& window,int turn)
{
	window.draw(background);
	window.draw(viewground);

	//Rectangles
	for (int i = 0; i < RowRec; i++) 	
			for (int j = 0; j < ColRec; j++)
			{
				window.draw(rec[i][j]);
			}
}

