#include "Spell.h"
#include"Player.h"
#include"Global.h"
#include<SFML/Audio.hpp>


SoundBuffer buff;
Sound snd;

parentspell::parentspell()
{
	SetType('s');
}

void parentspell::fn(Player& player, Player& enemy)
{
}

harpie_feather_duster::harpie_feather_duster(int x)
{
	SetFrontCard("Spells/harpie freather duster.JPG");
	SetCardName("harpie_feather_duster");
	SetPlayer(x);
}

void harpie_feather_duster::fn(Player & player, Player & enemy)
{
	if (getPlace() == 'H')
	{
		if (enemy.Ground.getCardSize() == 0)
		{
			SetActivate(false);
			player.Hand.TakeCard(this);
			player.Ground.AddCard(this);
		}
		else
		{
			while (enemy.Ground.getCardSize() > 0)
			{
				enemy.Graveyard.AddCard(enemy.Ground.TakeCard(enemy.Ground.getMonsterSize()));
			}
			player.Hand.TakeCard(this);
			player.Graveyard.AddCard(this);
		}
	}
	else if (getPlace() == 'G')
	{
		if (enemy.Ground.getCardSize() > 0)
		{
			while (enemy.Ground.getCardSize() > 0)
			{
				enemy.Graveyard.AddCard(enemy.Ground.TakeCard(enemy.Ground.getMonsterSize()));
			}
			SetActivate(true);
			player.Ground.TakeCard(this);
			player.Graveyard.AddCard(this);
		}
	}
}

Giant_turnado::Giant_turnado(int x)
{
	SetFrontCard("Spells/giant turande.JPG");
	SetCardName("Giant_turnado");
	SetPlayer(x);
}

void Giant_turnado::fn(Player & player, Player & enemy)
{
	if (getPlace() == 'H')
	{
		if (enemy.Ground.getCardSize() > 0)
		{
			player.Hand.TakeCard(this);
			player.Graveyard.AddCard(this);
			while (player.Ground.getCardSize() > 0)
			{
				Card* tmp = player.Ground.TakeCard(player.Ground.getMonsterSize());
				tmp->SetActivate(true);
				player.Hand.AddCard(tmp);
			}
			while (enemy.Ground.getCardSize() > 0)
			{
				Card* tmp = enemy.Ground.TakeCard(enemy.Ground.getMonsterSize());
				tmp->SetActivate(false);
				enemy.Hand.AddCard(tmp);
			}
		}
	}
}

RAIGEKI::RAIGEKI(int x)
{
	SetFrontCard("Spells/raigeki.JPG");
	SetCardName("raigeki");
	SetPlayer(x);
}

void RAIGEKI::fn(Player & player, Player & enemy)
{

	if (enemy.Ground.getMonsterSize() > 0 && getPlace() != 'T')
	{
		if (getPlace() == 'H')
		{
			player.Hand.TakeCard(this);
			player.Graveyard.AddCard(this);

		}
		else if (getPlace() == 'G')
		{
			SetActivate(true);
			player.Ground.TakeCard(this);
			player.Graveyard.AddCard(this);

		}
		while (enemy.Ground.getMonsterSize() > 0)
		{
			enemy.Graveyard.AddCard(enemy.Ground.TakeCard(0));
		}

	}
	else if (getPlace() == 'H')
	{
		SetActivate(false);
		player.Hand.TakeCard(this);
		player.Ground.AddCard(this);

	}
}


destruction::destruction(int x)
{
	SetFrontCard("Spells/destruction.JPG");
	SetCardName("destruction");
	SetPlayer(x);
}

void destruction::fn(Player & player, Player & enemy)
{
	if (getPlace() == 'H')
	{
		player.Hand.TakeCard(this);
		player.Graveyard.AddCard(this);
		int hand1 = player.Hand.getSize();
		int hand2 = enemy.Hand.getSize();

		while (player.Hand.getSize() > 0)
		{
			player.Graveyard.AddCard(player.Hand.TakeCard(0));
		}
		while (enemy.Hand.getSize() > 0)
		{
			enemy.Graveyard.AddCard(enemy.Hand.TakeCard(0));
		}
		for (int i = 0; i < hand1; i++)
		{
			player.Hand.AddCard(player.Deck.TakeCard());
		}
		for (int i = 0; i < hand2; i++)
		{
			Card* tmp = enemy.Deck.TakeCard();
			tmp->SetActivate(false);
			enemy.Hand.AddCard(tmp);


		}
	}
}
tribute_domed::tribute_domed(int x)
{
	SetFrontCard("Spells/tribute_domed.JPG");
	SetCardName("tribute_domed");
	SetPlayer(x);
	Activate = false;
}

void tribute_domed::fn(Player& player, Player& enemy)
{
	if (enemy.Ground.getMonsterSize() > 0 && getPlace() != 'T')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("choose enemy Monster ?");
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
					tmp = MousePos(window, player, enemy, true);
				}
				else
					tmp = MousePos(window, enemy, player, true);

				if (tmp)
				{
					if (tmp->getType() == 'm'&&enemy.Graveyard.AddCard(enemy.Ground.TakeCard(tmp)))
					{
						Select = nullptr;
						Activate = false;
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
		buff.loadFromFile("Audio/joey_EndTurn1.wav");
		snd.setBuffer(buff);
		snd.play();
	}
}

monsterReborn::monsterReborn(int x)
{
	SetFrontCard("Spells/monster reborn.JPG");
	SetCardName("monster reborn");
	SetPlayer(x);
	Activate = false;
}

void monsterReborn::fn(Player& player, Player& enemy)
{
	if (player.Graveyard.MonsterSize > 0 && getPlace() != 'T')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("Open Garve ?");

		}
		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			if (player.Graveyard.Show)
				player.Graveyard.Click(window);
			if (Activate)
			{
				Card* tmp;
				if (getPlayer() == 1)
				{
					tmp = MousePos(window, player, enemy, true);
				}
				else
					tmp = MousePos(window, enemy, player, true);

				if (tmp)
				{
					if (tmp->getType() == 'm' && player.Ground.AddCard(player.Graveyard.TakeCard(tmp)))
					{
						Select = nullptr;
						Activate = false;
						player.Graveyard.Show = false;
						if (!player.Graveyard.AddCard(player.Hand.TakeCard(this)))
							player.Graveyard.AddCard(player.Ground.TakeCard(this));
					}
				}

			}
			else
			{
				if (MessMenue.YesClicked(window))
				{
					MessMenue.Show = false;
					Activate = true;
					player.Graveyard.Show = true;
				}
				else if (MessMenue.NoClicked(window))
				{
					MessMenue.Show = false;
					Select = nullptr;
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

space::space(int x)
{
	SetFrontCard("Spells/mystical space typhoon.JPG");
	SetCardName("mystical space typhoon");
	SetPlayer(x);
	Activate = false;
}

void space::fn(Player& player, Player& enemy)
{
	if (enemy.Ground.getCardSize() > 0 && getPlace() != 'T')
	{
		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("destroy spell ?");
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
					tmp = MousePos(window, player, enemy, true);
				}
				else
					tmp = MousePos(window, enemy, player, true);

				if (tmp)
				{
					if (tmp->getType() != 'm' && enemy.Graveyard.AddCard(enemy.Ground.TakeCard(tmp)))
					{
						Select = nullptr;
						Activate = false;
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

potofgreed::potofgreed(int x)
{
	SetFrontCard("Spells/pot of greed.JPG");
	SetCardName("pot of greed");
	SetPlayer(x);
}

void potofgreed::fn(Player& player, Player& enemy)
{
	if (getPlace() == 'H')
	{
		int cards = 2;
		player.Hand.TakeCard(this);
		player.Graveyard.AddCard(this);
		while (cards-- > 0)
		{
			player.Hand.AddCard(player.Deck.TakeCard());
		}
	}

}

graceful_charity::graceful_charity(int x)
{
	SetFrontCard("Spells/graceful charity.JPG");
	SetCardName("graceful charity");
	SetPlayer(x);
}

void graceful_charity::fn(Player& player, Player& enemy)
{

	if (getPlace() == 'H')
	{


		if (!Select)
		{
			int card = 3;
			while (card-- > 0)
			{
				player.Hand.AddCard(player.Deck.TakeCard());
			}

			Select = this;
			MessMenue.setMessage("Discard 2 card");
			MessMenue.Show = true;
		}

		if (EventCatch(window) == Event::MouseButtonPressed)
		{

			if (MessMenue.YesClicked(window))
			{
				MessMenue.Show = false;
			}


			Card* tmp;
			if (getPlayer() == 1)
			{
				tmp = MousePos(window, player, enemy, true);
			}
			else
				tmp = MousePos(window, enemy, player, true);

			if (tmp)
			{

				if (tmp->getPlace() == 'H' && tmp != this)
				{
					vec.push_back(tmp);
					player.Hand.TakeCard(tmp);
				}
				if (vec.size() == 2)
				{
					for (int i = 0; i < vec.size(); i++)
					{
						player.Graveyard.AddCard(vec[i]);
					}

					Select = nullptr;
					player.Graveyard.AddCard(this);
					player.Hand.TakeCard(this);
				}


			}

		}
	}
}


Dark_hole::Dark_hole(int x)
{
	SetFrontCard("Spells/Dark hole.JPG");
	SetCardName("Dark hole");
	SetPlayer(x);
}

void Dark_hole::fn(Player& player, Player& enemy)
{

	if (getPlace() == 'H')
	{
		if (enemy.Ground.getMonsterSize() == 0)
		{
			SetActivate(false);
			player.Hand.TakeCard(this);
			player.Ground.AddCard(this);
		}
		else
		{
			player.Graveyard.AddCard(player.Hand.TakeCard(this));
			while (player.Ground.getMonsterSize() > 0)
			{
				player.Graveyard.AddCard(player.Ground.TakeCard(0));
			}
			while (enemy.Ground.getMonsterSize() > 0)
			{
				enemy.Graveyard.AddCard(enemy.Ground.TakeCard(0));
			}
		}
	}
	else if (getPlace() == 'G' && enemy.Ground.getMonsterSize() > 0)
	{
		while (player.Ground.getMonsterSize() > 0)
		{
			player.Graveyard.AddCard(player.Ground.TakeCard(0));
		}
		while (enemy.Ground.getMonsterSize() > 0)
		{
			enemy.Graveyard.AddCard(enemy.Ground.TakeCard(0));
		}
		SetActivate(true);
		player.Ground.TakeCard(this);
		player.Graveyard.AddCard(this);
	}
}


heavy_storm::heavy_storm(int x)
{
	SetFrontCard("Spells/heavy storm.JPG");
	SetCardName("heavy storm");
	SetPlayer(x);
}


void heavy_storm::fn(Player& player, Player& enemy)
{
	if (getPlace() == 'H')
	{
		if (enemy.Ground.getCardSize() == 0)
		{
			SetActivate(false);
			player.Hand.TakeCard(this);
			player.Ground.AddCard(this);
		}
		else
		{
			player.Graveyard.AddCard(player.Hand.TakeCard(this));
			while (player.Ground.getCardSize() > 0)
			{
				player.Graveyard.AddCard(player.Ground.TakeCard(player.Ground.getMonsterSize()));
			}
			while (enemy.Ground.getCardSize() > 0)
			{
				enemy.Graveyard.AddCard(enemy.Ground.TakeCard(enemy.Ground.getMonsterSize()));
			}
		}
	}
	else if (getPlace() == 'G' && enemy.Ground.getCardSize() > 0)
	{
		while (player.Ground.getCardSize() > 0)
		{
			player.Graveyard.AddCard(player.Ground.TakeCard(player.Ground.getMonsterSize()));
		}
		while (enemy.Ground.getCardSize() > 0)
		{
			enemy.Graveyard.AddCard(enemy.Ground.TakeCard(enemy.Ground.getMonsterSize()));
		}
		SetActivate(true);
		player.Ground.TakeCard(this);
		player.Graveyard.AddCard(this);
	}
}

change_of_heart::change_of_heart(int x)
{
	SetFrontCard("Spells/change of heart.JPG");
	SetCardName("change of heart hole");
	SetPlayer(x);
	Activate = false;
}

void change_of_heart::fn(Player& player, Player& enemy)
{
	if (getPlace() != 'T'&& enemy.Ground.getMonsterSize() > 0)
	{

		if (!Select)
		{
			Select = this;
			MessMenue.Show = true;
			MessMenue.setMessage("seleect 1 monster ..!");
		}
		if (EventCatch(window) == Event::MouseButtonPressed)
		{
			cout << "LOOP" << endl;
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
					tmp = MousePos(window, player, enemy, true);
				}
				else
					tmp = MousePos(window, enemy, player, true);

				if (tmp)
				{
					if (tmp->getType() == 'm' && player.Ground.AddCard(enemy.Ground.TakeCard(tmp)))
					{
						monsterchild* mon = static_cast<monsterchild*>(tmp);
						mon->SetPlayer(getPlayer());
						if (mon->getPlayer() == 1)
							mon->Arrow.setRotation(0);
						else
							mon->Arrow.setRotation(180);
						if (!player.Graveyard.AddCard(player.Hand.TakeCard(this)))
							player.Graveyard.AddCard(player.Ground.TakeCard(this));
						Select = nullptr;
						Activate = false;
					}
				}
			}

		}

	}
	else if (getPlace() != 'T')
	{
		SetActivate(false);
		player.Ground.AddCard(player.Hand.TakeCard(this));
		Select = nullptr;
	}

}