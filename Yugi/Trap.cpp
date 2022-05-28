#include "Trap.h"
#include"Player.h"
#include"Global.h"
#include<SFML/Audio.hpp>



SoundBuffer buf;
Sound sud;

Trap::Trap()
{
	SetType('t');
}
void Trap::TrapCards(Player& player, Player& Enemy)
{
}
Torrential_Tribute::Torrential_Tribute(int player)
{
	SetType('t');
	SetPlayer(player);
	SetCardName("TorrentialTribute");
	SetFrontCard("Traps/Torrential Tribute.jpeg");
	Activate = false;
}
void Torrential_Tribute::TrapCards(Player& player, Player& Enemy)
{
	if (getPlace() == 'G')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Destory All in Field ?");
		}
		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (!Activate)
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
				}
			}
			if (Activate)
			{
				
				while (player.Ground.getSize() > 0)
				{
					player.Graveyard.AddCard(player.Ground.TakeCard(0));
				}
				while (Enemy.Ground.getSize() > 0)
				{
					Enemy.Graveyard.AddCard(Enemy.Ground.TakeCard(0));
				}

				buf.loadFromFile("Audio/AhNo.wav");
				sud.setBuffer(buf);
				sud.play();
				Activate = false;
				Select = nullptr;
			}
		}
	}
	else if (getPlace() == 'H')
	{
		SetActivate(false);
		player.Ground.AddCard(player.Hand.TakeCard(this));
		buf.loadFromFile("Audio/joey_EndTurn1.wav");
		sud.setBuffer(buf);
		sud.play();
	}
}
GravelStorm::GravelStorm(int player)
{
	SetType('t');
	SetPlayer(player);
	SetCardName("GravelStorm");
	SetFrontCard("Traps/GravlestStorm.jpg");
	Activate = false;
}
void GravelStorm::TrapCards(Player &player, Player &Enemy)
{
	if (Enemy.Ground.getCardSize() > 0 && getPlace() != 'T')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Choose one Card ?");

		}
		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (!Activate)
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
				}
			}
			if (Activate)
			{
				Card* tmp;
				if (getPlayer() == 1)
				{
					tmp = MousePos(window, player, Enemy, true);
				}
				else
					tmp = MousePos(window, Enemy, player, true);

				if (tmp)
				{
					if (player.Hand.AddCard(Enemy.Ground.TakeCard(tmp)))
					{
						Select = nullptr;
						Activate = false;
						tmp->SetActivate(true);
						tmp->SetPlayer(getPlayer());
						if (!player.Graveyard.AddCard(player.Hand.TakeCard(this)))
							player.Graveyard.AddCard(player.Ground.TakeCard(this));
					}
				}

			}
		}

	}
	else if (getPlace() != 'T')
	{
		SetActivate(false);
		player.Ground.AddCard(player.Hand.TakeCard(this));
	}
}
GiftCard::GiftCard(int player)
{
	SetPlayer(player);
	SetType('t');
	SetCardName("Gift_Card");
	SetFrontCard("Traps/GiftCard.jpg");
	Activate = false;

}
void GiftCard::TrapCards(Player &player, Player &Enemy)
{
	if (getPlace() == 'G')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Activate Gift Card ?");
		}
		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (!Activate)
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
				}
			}
			if (Activate)
			{
				Enemy.IncreaseLifePoints(3000);
				player.Graveyard.AddCard(player.Ground.TakeCard(this));
				Activate = false;
				Select = nullptr;
			}
		}
	}
	else if (getPlace() == 'H')
	{
		SetActivate(false);
		player.Hand.TakeCard(this);
		player.Ground.AddCard(this);
	}
}
Heavy_Slump::Heavy_Slump(int player)
{
	SetPlayer(player);
	SetCardName("Heavy_Slump");
	SetFrontCard("Traps/Heavy Slump.jpg");
	SetType('t');
	Activate = false;
}

void Heavy_Slump::TrapCards(Player& player, Player& Enemy)
{
	if (Enemy.Hand.getSize() >= 8 && getPlace() != 'T')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Activate Card ?");
		}

		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (!Activate)
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
				}
			}
			if (Activate)
			{
				Card *tmp;
				while (Enemy.Hand.getSize() > 0)
				{
					Enemy.Deck.AddCard(Enemy.Hand.TakeCard(0));
				}
				Enemy.Deck.Shuffle();
				while (Enemy.Hand.getSize() < 2)
				{
					tmp = Enemy.Deck.TakeCard();
					tmp->SetActivate(false);
					Enemy.Hand.AddCard(tmp);
				}
				player.Graveyard.AddCard(player.Hand.TakeCard(this));
				Enemy.DecreaseLifePoints(8000);
				Select = nullptr;
				Activate = false;
			}
		}
	}
	else if (getPlace() == 'H')
	{
		SetActivate(false);
		player.Hand.TakeCard(this);
		player.Ground.AddCard(this);
	}
}
Graceful_Tear::Graceful_Tear(int player)
{
	SetPlayer(player);
	SetType('t');
	SetCardName("Graceful Tear");
	Activate = false;
	SetFrontCard("Traps/Graceful Tear.jpg");
}

void Graceful_Tear::TrapCards(Player& player, Player& Enemy)
{
	if (player.Hand.getSize() > 1 && getPlace() != 'T')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Choose one Card ?");

		}
		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (!Activate)
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
				}
			}
			if (Activate)
			{
				Card* tmp;
				if (getPlayer() == 1)
				{
					tmp = MousePos(window, player, Enemy, true);
				}
				else
					tmp = MousePos(window, Enemy, player, true);

				if (tmp)
				{
					if (Enemy.Hand.AddCard(player.Hand.TakeCard(tmp)))
					{
						Select = nullptr;
						Activate = false;
						tmp->SetActivate(false);
						if (getPlayer() == 1)
							tmp->SetPlayer(2);
						else
							tmp->SetPlayer(1);
						if (!player.Graveyard.AddCard(player.Hand.TakeCard(this)))
							player.Graveyard.AddCard(player.Ground.TakeCard(this));
						player.IncreaseLifePoints(2000);
					}
				}

			}
		}

	}
	else if (getPlace() != 'T')
	{
		SetActivate(false);
		player.Ground.AddCard(player.Hand.TakeCard(this));
	}
}

Blasting_The_Ruins::Blasting_The_Ruins(int player)
{
	SetType('t');
	SetCardName("Blasting The Ruins");
	SetPlayer(player);
	SetFrontCard("Traps/BlastingTheRuins.jpg");
	Activate = false;
}

void Blasting_The_Ruins::TrapCards(Player & player, Player & Enemy)
{
	if (player.Graveyard.getSize() >= 5 && getPlace() != 'T')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Activate Card ?");
		}

		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (!Activate)
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
				}
			}
			else
			{
				Enemy.DecreaseLifePoints(3000);
				if (getPlace() == 'H')
					player.Graveyard.AddCard(player.Hand.TakeCard(this));
				else if (getPlace() == 'G')
					player.Graveyard.AddCard(player.Ground.TakeCard(this));
				Select = nullptr;
				Activate = false;
			}
		}
	}
	else if (getPlace() == 'H')
	{
		SetActivate(false);
		player.Hand.TakeCard(this);
		player.Ground.AddCard(this);
	}
}

Destruct_Potion::Destruct_Potion(int player)
{
	SetPlayer(player);
	SetCardName("Destruct Potion");
	SetFrontCard("Traps/DestructPotion.jpg");
	SetType('t');
	Activate = false;
}

void Destruct_Potion::TrapCards(Player & player, Player & Enemy)
{
	if (player.Ground.getMonsterSize() > 0 && getPlace() != 'T')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Choose one Monster  ?");

		}
		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (!Activate)
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
				}
			}
			if (Activate)
			{
				Card* tmp;
				if (getPlayer() == 1)
				{
					tmp = MousePos(window, player, Enemy, true);
				}
				else
					tmp = MousePos(window, Enemy, player, true);

				if (tmp)
				{
					if (tmp->getType()=='m' && player.Graveyard.AddCard(player.Ground.TakeCard(tmp)))
					{					 
						Select = nullptr;
						Activate = false;
						if (!player.Graveyard.AddCard(player.Hand.TakeCard(this)))
							player.Graveyard.AddCard(player.Ground.TakeCard(this));
						player.IncreaseLifePoints(static_cast<monstersparent*>(tmp)->get_attack());
						buf.loadFromFile("Audio/AhNo.wav");
						sud.setBuffer(buf);
						sud.play();
					}
				}

			}
		}

	}
	else if (getPlace() != 'T')
	{
		SetActivate(false);
		player.Ground.AddCard(player.Hand.TakeCard(this));
	}

}

JarOfGreed::JarOfGreed(int player)
{
	SetPlayer(player);
	SetCardName("Jar of Greed");
	SetFrontCard("Traps/Jar of Greed.jpg");
	SetType('t');
	Activate = false;
}

void JarOfGreed::TrapCards(Player & player, Player & Enemy)
{
	if (getPlace() == 'G')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Draw Card ?");
		}
		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (!Activate)
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
				}
			}
			if (Activate)
			{
				player.Graveyard.AddCard(player.Ground.TakeCard(this));
				player.Hand.AddCard(player.Deck.TakeCard());
				Activate = false;
				Select = nullptr;
			}
		}
	}
	else if (getPlace() == 'H')
	{
		SetActivate(false);
		player.Ground.AddCard(player.Hand.TakeCard(this));
	}
}

Gallantry::Gallantry(int player)
{
	SetPlayer(player);
	SetCardName("Gallantry");
	SetFrontCard("Traps/Gallantry.jpg");
	SetType('t');
}

void Gallantry::TrapCards(Player & player, Player & Enemy)
{
	if (getPlace() == 'H' && Enemy.Hand.getSize() >= 5)
	{
		Enemy.Graveyard.AddCard(Enemy.Hand.TakeCard(rand() % Enemy.Hand.getSize()));
		player.Graveyard.AddCard(player.Hand.TakeCard(this));
	}
}

LocalizedTornado::LocalizedTornado(int player)
{
	SetPlayer(player);
	SetCardName("Localized");
	SetFrontCard("Traps/Localized Tornado.jpg");
	SetType('t');
}

void LocalizedTornado::TrapCards(Player & player, Player & Enemy)
{
	Card* tmp;
	while (player.Hand.getSize() > 0)
	{
		player.Deck.AddCard(player.Hand.TakeCard(0));
	}
	while (player.Graveyard.getSize() > 0)
	{
		player.Deck.AddCard(player.Graveyard.TakeCard(0));
	}
	while (Enemy.Hand.getSize() > 0)
	{
		Enemy.Deck.AddCard(Enemy.Hand.TakeCard(0));
	}
	while (Enemy.Graveyard.getSize() > 0)
	{
		Enemy.Deck.AddCard(Enemy.Graveyard.TakeCard(0));
	}
	player.Deck.Shuffle();
	Enemy.Deck.Shuffle();
	player.Hand.AddCard(player.Deck.TakeCard());
	tmp = player.Deck.TakeCard();
	tmp->SetActivate(false);
	Enemy.Hand.AddCard(tmp);
	if (getPlayer() == 1)
		tmp->SetPlayer(2);
	else
		tmp->SetPlayer(1);
}
