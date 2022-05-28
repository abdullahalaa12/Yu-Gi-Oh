#include"Player.h"
#include "List.h"
#include<SFML/Audio.hpp>

SoundBuffer b;
Sound s;

Card* Deck::newSpell(int player)
{
	int random = rand() % 12;
	switch (random)
	{
	case 0: return new harpie_feather_duster(player);
		break;

	case 1: return new Giant_turnado(player);
		break;

	case 2: return new RAIGEKI(player);
		break;

	case 3: return new destruction(player);
		break;

	case 4: return new tribute_domed(player);
		break;

	case 5: return new monsterReborn(player);
		break;

	case 6: return new space(player);
		break;

	case 7: return new potofgreed(player);
		break;

	case 8: return new graceful_charity(player);
		break;

	case 9: return new heavy_storm(player);
		break;

	case 10: return new Dark_hole(player);
		break;

	case 11: return new change_of_heart(player);
		break;

	default: return nullptr;
	}
	return nullptr;
}

Card* Deck::newTrap(int player)
{
	int random = rand() % 10;
	switch (random)
	{
	case 0: return new Heavy_Slump(player);
		break;
	case 1: return new Torrential_Tribute(player);
		break;
	case 2: return new GravelStorm(player);
		break;

	case 3: return new GiftCard(player);
		break;


	case 4: return new Destruct_Potion(player);
		break;

	case 5: return new Graceful_Tear(player);
		break;

	case 6: return new Blasting_The_Ruins(player);
		break;

	case 7: return new JarOfGreed(player);
		break;

	case 8: return new Gallantry(player);
		break;

	case 9: return new LocalizedTornado(player);
		break;

	default: return nullptr;
	}
	return nullptr;
}

Deck::Deck(int capacity, int player)
{
	
	this->capacity = capacity;
	Spr = new Sprite(Card::BackTex);
	Spr->scale(0.3, 0.3);
	if (player == 1)
		Spr->setPosition(windowX - 14 - handcardWIDTH, windowy - handcardHEIGHT - 10);
	else
		Spr->setPosition(windowX - 14 - handcardWIDTH, 10);

	deck.reserve(capacity);
	while (getSize() < capacity)
	{
		//Monsters
		AddCard(new monsterchild(player));

		//Spells
		AddCard(newSpell(player));

		//Monsters
		AddCard(new monsterchild(player));

		//Traps
		AddCard(newTrap(player));
	}
	for (int i = 0; i < 20; i++)
		Shuffle();
}

void Deck::Draw(RenderWindow& window)
{
	if (getSize() > 0)
		window.draw(*Spr);
}

Card* Deck::TakeCard()
{
	if (getSize() > 0)
	{
		b.loadFromFile("Audio/MoveCard.wav");
		s.setBuffer(b);
		Card* r = deck.back();
		deck.pop_back();
		s.play();
		return r;
	}
	else
		return nullptr;
}

void Deck::Shuffle()
{
	for (int i = 0; i < getSize(); i++)
		swap(deck[i], deck[((rand() % rand()) + rand()) % getSize()]);
}

void Deck::AddCard(Card* card)
{
	if (card)
		deck.push_back(card);
}

int Deck::getSize()
{
	return deck.size();
}

Deck::~Deck()
{
	delete Spr;
}



void Hand::Sort()
{
	for (int i = 0; i < getSize(); i++)
		DisplayCard(i)->SetPosition(Vector2<float>
		(((windowX / 2) - (handcardWIDTH * (getSize()) / 2) + (handcardWIDTH * i)), Y));
}

Hand::Hand(int capacity, int player, allmap* Map)
{
	setCapacity(capacity);
	this->Map = Map;
	if (player == 1)
		Y = windowy - (handcardHEIGHT / 2);
	else
		Y = 0 - (handcardHEIGHT / 2);
}

void Hand::Draw(RenderWindow& window)
{
	for (int i = 0; i < getSize(); i++)
		window.draw(DisplayCard(i)->GetCardSprite());
}

void Hand::setCapacity(int capacity)
{
	this->capacity = capacity;
}

int Hand::getCapacity()
{
	return capacity;
}

bool Hand::AddCard(Card* card)
{
	if (card && getSize() < getCapacity())
	{
		card->SetPlace('H');
		_list.push_back(card);
		Sort();
		return true;
	}
	return false;
}

Card* Hand::DisplayCard(int pos)
{
	if (pos < getSize())
		return *next(_list.begin(), pos);
	else
		return NULL;
}

Card* Hand::DisplayCard(Vector2<float> pos)
{
	for (int i = 0; i < getSize(); i++)
		if (DisplayCard(i)->GetCardSprite().getGlobalBounds().contains(pos))
			return DisplayCard(i);
	return nullptr;
}

Card* Hand::TakeCard(int pos)
{
	if (pos < getSize())
	{
		list<Card*>::iterator it = next(_list.begin(), pos);
		Card* tmp = *it;
		_list.erase(it);
		Sort();
		return tmp;
	}
	else
		return NULL;
}

Card* Hand::TakeCard(Card* tmp)
{
	for (int i = 0; i < getSize(); i++)
		if (DisplayCard(i) == tmp) 			
			return TakeCard(i);
	return nullptr;
}

int Hand::getSize()
{
	return _list.size();
}

Hand::~Hand()
{
	//for (int i = 0; i < getSize(); i++)
		//delete DisplayCard(i);
}


Ground::Ground(int capacity, int Player, allmap* Map)
{
	
	this->capacity = capacity;
	this->Map = Map;
	MonsterSize = 0;
	CardSize = 0;
	if (Player == 1)
	{
		cRow = 0;
		mRow = 1;
	}
	else
	{
		mRow = 2;
		cRow = 3;
	}
}

void Ground::Draw(RenderWindow& window)
{
	for (int i = 0; i < getSize(); i++)
		window.draw(DisplayCard(i)->GetCardSprite());
}

bool Ground::AddCard(Card* Card)
{
	if (Card && getSize() < capacity)
	{
		b.loadFromFile("Audio/MoveCard.wav");
		s.setBuffer(b);
		int i = -1;
		int j = 0;
		int Row = 0;
		Card->SetPlace('G');

		if (Card->getType() == 'm')
		{
			if (getMonsterSize() < (capacity / 2))
			{
				i = 0;
				Row = mRow;
				MonsterSize++;
				s.play();
			}
		}
		else if (getCardSize() < (capacity / 2))
		{
			i = getMonsterSize();
			Row = cRow;
			CardSize++;
			s.play();
		}


		if (i != -1)
		{
			while (DisplayCard(i))
			{

				if (!(DisplayCard(i)->getPosition() == (Map->position[(Row * ColRec) + j])))
					break;
				i++;
				j++;
			}
			Card->SetPosition(Map->position[(Row * ColRec) + j]);
			if (Card->getType() == 'm')
			{
				monsterchild* tmp = static_cast<monsterchild*>(Card);
				tmp->Arrow.setPosition(Card->getPosition().x + (Card->GetCardSprite().getGlobalBounds().width / 2),
					Card->getPosition().y + (Card->GetCardSprite().getGlobalBounds().height / 2));
				if (tmp->getPlayer() == 1)
					tmp->Arrow.setRotation(0);
				else
					tmp->Arrow.setRotation(180);
			}
			_list.insert(next(_list.begin(), i), Card);
			return true;
		}
	}
	return false;
}

Card* Ground::DisplayCard(int pos)
{
	if (pos < getSize())
		return *next(_list.begin(), pos);
	else
		return NULL;
}

Card* Ground::DisplayCard(Vector2<float> pos)
{
	for (int i = 0; i < getSize(); i++)
		if (DisplayCard(i)->GetCardSprite().getGlobalBounds().contains(pos))
			return DisplayCard(i);
	return nullptr;
}

Card* Ground::TakeCard(int pos)
{
	if (pos < getSize())
	{
		list<Card*>::iterator it = next(_list.begin(), pos);
		Card* tmp = *it;
		_list.erase(it);
		if (tmp->getType() == 'm')
			MonsterSize--;
		else 
			CardSize--;
		return tmp;
	}
	else
		return NULL;
}

Card* Ground::TakeCard(Card* tmp)
{
	for (int i = 0; i < getSize(); i++)
		if (DisplayCard(i) == tmp)
			return TakeCard(i);
	return nullptr;
}

int Ground::getSize()
{
	return _list.size();
}

int Ground::getMonsterSize()
{
	return MonsterSize;
}

int Ground::getCardSize()
{
	return CardSize;
}

Ground::~Ground()
{
	//for (int i = 0; i < getSize(); i++)
		//delete DisplayCard(i);
}

void Graveyard::Sort(int pos)
{
	for (int i = pos; i < getSize(); i++)
		Grave[i]->SetPosition(Vector2f(25 + Container.getGlobalBounds().left + (i % 5) * handcardWIDTH
			, windowy / 2 - handcardHEIGHT / 2));

	if (getSize() > 0)
	{
		if (getSize() == Page * 5)
			Page--;
		Vector2f tmp = Spr->getPosition();
		*Spr = DisplayCard(getSize() - 1)->GetCardSprite();
		Spr->setPosition(tmp);
	}

}

Graveyard::Graveyard(int player, allmap* Map)
{

	MonsterSize = CardSize = 0;
	Spr = new Sprite;
	if (player == 1)
		Spr->setPosition(windowX - 14 - handcardWIDTH, windowy - 2 * handcardHEIGHT - 20);
	else
		Spr->setPosition(windowX - 14 - handcardWIDTH, 20 + handcardHEIGHT);

	Page = 0;
	Show = false;

	Container.setSize(Vector2f((handcardWIDTH * 5) + 50, handcardHEIGHT + 100));
	Container.setFillColor(Color(1, 1, 1, 450));
	Container.setOutlineThickness(2.f);
	Container.setOutlineColor(Color(200, 120, 120, 100));
	Container.setPosition((windowX / 2 - Container.getGlobalBounds().width / 2)
		, 25 + (windowy / 2 - Container.getGlobalBounds().height / 2));

	N.loadFromFile("Images/Next.png");  P.loadFromFile("Images/Prev.png");
	Next = new Sprite(N);
	Next->setPosition(Container.getPosition().x + Container.getSize().x - 130
		, Container.getPosition().y + Container.getSize().y - 85);

	Prev = new Sprite(P);
	Prev->setPosition(Container.getPosition().x + 30
		, Container.getPosition().y + Container.getSize().y - 85);
}

void Graveyard::Draw(RenderWindow& window)
{
	if (getSize() > 0)
		window.draw(*Spr);
	else
		Show = false;
	if (Show)
	{
		window.draw(Container);
		if (getSize() > (Page + 1) * 5)
			window.draw(*Next);
		if (Page > 0)
			window.draw(*Prev);
		for (int i = Page * 5; i < getSize(); i++)
		{
			if (i == (Page + 1) * 5)
				break;
			window.draw(DisplayCard(i)->GetCardSprite());
		}
	}
}

void Graveyard::Click(RenderWindow& window)
{
	if (Show)
	{
		if (Next->getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
		{
			if (getSize() > (Page + 1) * 5)
			{
				Page++;

				b.loadFromFile("Audio/MENU.wav");
				s.setBuffer(b);
				s.play();
			}
		}
		else if (Prev->getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
		{
			if (Page > 0)
			{
				Page--;
				b.loadFromFile("Audio/MENU.wav");
				s.setBuffer(b);
				s.play();
			}
		}
	}
	else
	{
		Page = 0;
		if (DisplayCard(0))
			if (Spr->getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
				Show = true;
	}
}

bool Graveyard::AddCard(Card* card)
{
	if (card)
	{
		card->SetPlace('T');
		if (card->getType() == 'm') 
			MonsterSize++;
		else
			CardSize++;
		card->SetActivate(true);
		Grave.push_back(card);
		Sort(getSize() - 1);
		return true;
	}
	return false;
}

Card* Graveyard::DisplayCard(int pos)
{
	if (pos < getSize() && pos >= 0)
		return Grave[pos];
	else
		return nullptr;
}

Card* Graveyard::DisplayCard(Vector2<float> pos)
{
	if (Show)
		for (int i = Page * 5; i < getSize(); i++)
		{
			if (i == (Page + 1) * 5)
				break;
			else if (DisplayCard(i)->GetCardSprite().getGlobalBounds().contains(pos))
				return DisplayCard(i);
		}
	else if (Spr->getGlobalBounds().contains(pos))
		return DisplayCard(getSize() - 1);

	return nullptr;
}

Card* Graveyard::TakeCard(int pos)
{
	if (pos < getSize())
	{

		vector<Card*>::iterator it = Grave.begin();
		it += pos;
		Card* tmp = *it;
		if (tmp->getType() == 'm')
			MonsterSize--;
		else
			CardSize--;
		Grave.erase(it);
		Sort(pos);
		return tmp;
	}
	else
		return NULL;
}

Card* Graveyard::TakeCard(Card* tmp)
{
	if (Show)
		for (int i = 0; i < getSize(); i++)
			if (DisplayCard(i) == tmp)
				return TakeCard(i);
	return nullptr;
}

int Graveyard::getSize()
{
	return Grave.size();
}

Graveyard::~Graveyard()
{
	//for (int i = 0; i < getSize(); i++)
		//delete Grave[i];
	delete Next;
	delete Prev;
	delete Spr;
}
