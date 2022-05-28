#include "Card.h"
#include"Global.h"

//intiliaze the card id and Name
Card::Card() :Position(0, 0)
{
	Card_iD = ++Count;
	Activate = true;
	Card_Name = " ";
	Type = ' ';  //M   for  Monster   //S   for  Spell   //T   for Trap
	Place = 'D';   //D for Deck   //T   for  Graveyard   //G   for  Ground     //H   for Hand
}



//This Function is to load image to the card which takes a string parameter to be put in the Texture
void Card::SetFrontCard(string name)
{
	FrontTex.loadFromFile(name);
}


//Monster    OR   Spell    OR   Trap     ONLY!!!
void Card::SetType(char Type)
{
	this->Type = Type;
}

void Card::SetPlace(char Place)
{
	this->Place = Place;
}




void Card::SetCardName(string name)
{
	Card_Name = name;
}




void Card::SetActivate(bool Act)
{
	Activate = Act;
}




void Card::SetPosition(Vector2<float> Pos)
{
	Position = Pos;
}

void Card::SetPlayer(int P)
{
	player = P;
}

Texture* Card::getFrontCard()
{
	return &FrontTex;
}

char Card::getType()
{
	return Type;
}

char Card::getPlace()
{
	return Place;
}




string Card::GetCardName()
{
	return Card_Name;
}




// A Function that return a bool to use it to check if the card is activate or not 
bool Card::GetActivate()
{
	return Activate;
}

Vector2<float> Card::getPosition()
{
	return Position;
}

Sprite Card::GetCardSprite()
{

	Sprite Card;
	if (Activate)
		Card.setTexture(FrontTex);
	else
		Card.setTexture(Card::BackTex);
	Card.setScale(0.3, 0.3);
	/*if (player == 2)
	{
		Card.setRotation(180);
		Card.setPosition(Position + Vector2<float>(Card.getGlobalBounds().width
			, Card.getGlobalBounds().height));
	}
	else*/
	Card.setPosition(Position);


	return Card;
}

int Card::getPlayer()
{
	return player;
}

bool* Card::TheSelect(string Message)
{
	static bool Activ = false;
	if (!Select)
	{
		Select = this;
		MessMenue.setMessage(Message);
		MessMenue.Show = true;
	}
	if (EventCatch(window) == Event::MouseButtonPressed)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (!Activ)
			{
				if (MessMenue.YesClicked(window))
				{
					Activ = true;
					MessMenue.Show = false;
				}
				else if (MessMenue.NoClicked(window))
				{
					Select = nullptr;
					MessMenue.Show = false;
				}
			}
			return &Activ;

		}
	}
	return nullptr;
}




Card::~Card()
{
}