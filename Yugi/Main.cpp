#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include"Player.h"
#include"Global.h"
#include"monsters-2.h"
#include"Trap.h"
#include"spell.h"
#include<iostream>
#include<cmath>
using namespace std;
using namespace sf;


//static members of Card
int Card::Count = 0;
Texture monsterchild::ArrowTex;
Texture Card::BackTex;
allmap* obj = new allmap;

void play(Music& m, bool p)
{
	if (p)
		m.play();
}

void main()
{
	srand(time(0));
	Card::BackTex.loadFromFile("Images/BackCard.png");
	monsterchild::ArrowTex.loadFromFile("Images/Sword.png");
	Player* Player1 = new Player(1, obj);
	Player* Player2 = new Player(2, obj);

	Sprite* ViewCard = new Sprite;
	int Phase = 0; int Turn = 1;
	Menue Menue(&Phase);
	bool isSummon = false;
	bool FirstAttack = false;
	bool PlayMusic = false;
	int vol = 80;
	RectangleShape Loadingbar;
	int Load = 0;

	Font LoadingFont;
	LoadingFont.loadFromFile("Holiday.ttf");

	Text LoadingText;
	LoadingText.setFont(LoadingFont);
	LoadingText.setString("Loading");
	LoadingText.setFillColor(Color(204, 255, 255));
	LoadingText.setCharacterSize(40);
	LoadingText.setPosition(Vector2f((500 / 2) + 50, (750 / 2) + 120));

	//Game Window//
	//RenderWindow window(VideoMode(1250, 710), "YuGi");
	Texture SplashTex[3], buttonsTex[4], StartTex, CardsTex, LogoTex, OptionTex[2];
	//Splash Textures//
	SplashTex[0].loadFromFile("Images/yugiSplash.jpg");
	SplashTex[1].loadFromFile("Images/yy.jpg");
	SplashTex[2].loadFromFile("Images/splash3.jpeg");
	//Start Menu Buttons Textures//
	buttonsTex[0].loadFromFile("Images/Duel.png");
	buttonsTex[1].loadFromFile("Images/List.png");
	buttonsTex[2].loadFromFile("Images/Options.png");
	buttonsTex[3].loadFromFile("Images/Quit.png");
	LogoTex.loadFromFile("Images/yugiohduellinks (2).png");
	OptionTex[0].loadFromFile("Images/Play.png");
	OptionTex[1].loadFromFile("Images/Silent.png");
	//Start Menu Background Textures//
	StartTex.loadFromFile("Images/yu-gi-oh_banner.jpg");
	//Splashs & StartMenu & Buttons Sprites//
	Sprite SplashSpr, Start(StartTex), buttonsSpr[4], CardsSpr, LogoSpr, OptionSpr[2];
	SplashSpr.setTexture(SplashTex[0]);

	buttonsSpr[0].setPosition(Vector2f((1000 / 2) - 350, (750 / 2) + 20));
	buttonsSpr[1].setPosition(Vector2f((1000 / 2) - 350, (750 / 2) + 90));
	buttonsSpr[2].setPosition(Vector2f((1000 / 2) - 350, (750 / 2) + 160));
	buttonsSpr[3].setPosition(Vector2f((1000 / 2) - 350, (750 / 2) + 230));
	LogoSpr.setPosition(Vector2f((1000 / 2) - 420, (750 / 3) - 200));

	OptionSpr[0].setPosition(Vector2f((1000 / 2) - 500, 750 - 20));
	OptionSpr[1].setPosition(Vector2f((1000 / 2) - 450, 750 - 20));
	for (int i = 0; i < 4; i++)
	{
		buttonsSpr[i].setTexture(buttonsTex[i]);
	}
	LogoSpr.setTexture(LogoTex);
	for (int i = 0; i < 2; i++)
	{
		OptionSpr[i].setTexture(OptionTex[i]);
	}

	Music music, music2;
	music.openFromFile("Audio/Imagine Dragons - Bad Liar (Lyrics).wav");
	music.setLoop(true);
	music.setVolume(0);



	music2.openFromFile("Audio/m_duel1.wav");
	music2.setLoop(true);
	music2.setVolume(30);
	if (PlayMusic)
		music2.play();


	SoundBuffer buffer;
	Sound sound;

	SoundBuffer Attackbuffer;
	Attackbuffer.loadFromFile("Audio/yugiattack.wav");
	Sound AttackSound(Attackbuffer);

	float bright = 0;
	float brightbtn = 20;
	float posxb1 = 0-50;
	float posyb1 = 750 / 2;
	float posxb2 = 1000+50;
	float posyb2 = (750 / 2) + 40;
	float CardMovex = 1050;
	float CardMoveY = 650;
	bool stop = false;
	int page = 1;
	int i = 0;
	const float PI = 3.14159265;
	while (window.isOpen())
	{
		if (page < 7)
		{
			Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					window.close();
					break;
				default:
					break;
				}

			}
			window.clear();
			if (page < 4)
			{
				if (bright < 255)
					SplashSpr.setColor(Color(bright, bright, bright));
				else
					SplashSpr.setColor(Color(255 - (bright - 255), 255 - (bright - 255), 255 - (bright - 255)));

				window.draw(SplashSpr);

				bright += 0.2;
				if (bright > 500)
				{
					if (page < 3)
						SplashSpr.setTexture(SplashTex[page]);
					page++;
					bright = 0;
				}
			}
			else if (page == 4)
			{
				if (bright < 255)
					Start.setColor(Color(bright - 255, bright - 255, bright - 255));
				else
					Start.setColor(Color(255 - (bright - 255), 255 - (bright - 255), 255 - (bright - 255)));

				window.draw(Start);

				bright += 0.2;
				if (bright > 250)
				{
					page++;
					bright = 250;
					buffer.loadFromFile("Audio/MENU.wav");
					sound.setBuffer(buffer);
					music.play();
				}
			}
			else if (page == 5)
			{

				window.draw(Start);
				music.setVolume(vol);

				for (int i = 0; i < 4; i++)
				{
					buttonsSpr[i].setColor(Color(brightbtn, brightbtn, brightbtn));
				}
				for (int i = 0; i < 2; i++)
					window.draw(OptionSpr[i]);

				window.draw(LogoSpr);
				LogoSpr.setColor(Color(255, 255, 255));

				if (!stop)
				{
					brightbtn += 0.1;
				}
				if (brightbtn > 150.0)
				{
					stop = true;
				}

				Vector2f pos = static_cast<Vector2f>(Mouse::getPosition(window));

				if (buttonsSpr[0].getGlobalBounds().contains(pos))
				{
					buttonsSpr[0].setColor(Color(1000, 1000, 1000));
				}
				else if (buttonsSpr[1].getGlobalBounds().contains(pos))
				{
					buttonsSpr[1].setColor(Color(1000, 1000, 1000));
				}
				else if (buttonsSpr[2].getGlobalBounds().contains(pos))
				{
					buttonsSpr[2].setColor(Color(1000, 1000, 1000));
				}
				else if (buttonsSpr[3].getGlobalBounds().contains(pos))
				{
					buttonsSpr[3].setColor(Color(1000, 1000, 1000));
				}

				for (int i = 0; i < 4; i++)
				{
					window.draw(buttonsSpr[i]);
				}
				window.draw(LogoSpr);
				if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
				{

					if (buttonsSpr[0].getGlobalBounds().contains(pos))
					{
						sound.play();
						page++;

					}
					if (buttonsSpr[1].getGlobalBounds().contains(pos))
					{
						sound.play();

					}
					if (buttonsSpr[2].getGlobalBounds().contains(pos))
					{
						sound.play();

					}
					if (buttonsSpr[3].getGlobalBounds().contains(pos))
					{
						sound.play();
						window.close();
					}
					else if (OptionSpr[0].getGlobalBounds().contains(pos))
					{

						if (Mouse::isButtonPressed(Mouse::Left))
						{

							vol = 60;
						}
					}
					else if (OptionSpr[1].getGlobalBounds().contains(pos))
					{
						if (Mouse::isButtonPressed(Mouse::Left))
						{
							vol = 0;

						}
					}
				}
			}
			else if (page == 6)
			{

			window.draw(Start);
			Loadingbar.setPosition(Vector2f(Vector2f((1000 / 2) - 400, (750 / 2) + 200)));
			Loadingbar.setFillColor(Color(51, 153, 255));
			Loadingbar.setSize(Vector2f(Load, 10));
			Load += 1;
			window.draw(Loadingbar);
			window.draw(LoadingText);
			if (Load > 500)
			{
				music.stop();
				PlayMusic = true;
				play(music2, PlayMusic);
				buffer.loadFromFile("Audio/joey_start1.wav");
				sound.setBuffer(buffer);
				sound.play();
				page++;
			}
			}

		}
		//Start Game
		else
		{
			if (Select)
			{
				if (Select->getType() == 's')
				{

					static_cast<parentspell*>(Select)
						->fn(*Player1, *Player2);
				}
				else if (Select->getType() == 'm')
				{

					if (Phase == 3)
					{
						static_cast<monsterchild*>(Select)
							->killem(*Player1, *Player2);
					}
					else
					{
						if (static_cast<monsterchild*>(Select)
							->summontype(*Player1, true))
							isSummon = true;
					}
				}
				else if(Select->getType() == 't')
				{
					static_cast<Trap*>(Select)
						->TrapCards(*Player1, *Player2);
				}
			}
			if (Turn == 1)
				MouseObj = MousePos(window, *Player1, *Player2, !(Menue.getShow()));
			else
				MouseObj = MousePos(window, *Player2, *Player1, !(Menue.getShow()));

			
			if (MouseObj)
			{
				(*ViewCard) = MouseObj->GetCardSprite();
				if (MouseObj->getPlayer() == Turn)
					(*ViewCard).setTexture(*MouseObj->getFrontCard());
				ViewCard->setScale(1, 1);
				ViewCard->setPosition(obj->viewground.getPosition());
				ViewCard->setRotation(0);
			}

			window.clear();
			//Map
			obj->Draw(window,Turn);
			window.draw(*ViewCard);

			Player1->Draw(window);
			Player2->Draw(window);

			//Hands
			Player1->Hand.Draw(window);
			Player2->Hand.Draw(window);

			//Ground
			Player1->Ground.Draw(window);
			Player2->Ground.Draw(window);

			//Deck
			Player1->Deck.Draw(window);
			Player2->Deck.Draw(window);

			if (Phase == 3 && FirstAttack)
			{
				for (int i = 0; i < Player1->Ground.getMonsterSize(); i++)
				{
					monsterchild* tmp = static_cast<monsterchild*>(Player1->Ground.DisplayCard(i));
					if (!tmp->get_didattack() && tmp->GetActivate())
						window.draw(tmp->Arrow);
				}
			}

			//Grave
			Player1->Graveyard.Draw(window);
			Player2->Graveyard.Draw(window);

			//Menue
			Menue.Draw(window);
			MessMenue.Draw(window);

			//Prepare Phase
			if (!Select)
			{
				if (Player1->Deck.getSize() == 0 || Player1->LifePoints == 0 ||
					Player2->Deck.getSize() == 0 || Player2->LifePoints == 0)
				{
					MessMenue.setMessage("GAME  END !!");
					MessMenue.Show = true;
					if (EventCatch(window) == Event::MouseButtonPressed)
						if (MessMenue.YesClicked(window) || MessMenue.NoClicked(window))
							window.close();
				}

				else if (Phase == 0)
				{
					for (int i = 0; i < 4; i++)
					{
						Player1->Hand.AddCard(Player1->Deck.TakeCard());
						Player2->Hand.AddCard(Player2->Deck.TakeCard());
					}
					Phase++;
				}


				//Draw Phase

				else if (Phase == 1)
				{
					Player1->Hand.AddCard(Player1->Deck.TakeCard());
					for (int i = 0; i < Player2->Hand.getSize(); i++)
						Player2->Hand.DisplayCard(i)->SetActivate(false);
					for (int i = 0; i < Player1->Hand.getSize(); i++)
						Player1->Hand.DisplayCard(i)->SetActivate(true);
					Phase++;
				}


				//Main Phases
				else if (Phase == 2 || Phase == 4)
				{
					if (EventCatch(window) == Event::MouseButtonPressed)
					{
						if (Mouse::isButtonPressed(Mouse::Left))
						{
							Menue.Click(window);

							if (MouseObj && MouseObj->getPlayer() == Turn)
							{
								if (MouseObj->getType() == 's')
								{
									static_cast<parentspell*>(MouseObj)->fn(*Player1, *Player2);
								}
								else if (MouseObj->getType() == 'm' && !isSummon)
								{
									cout << "CALLLLLL" << endl;
									if (static_cast<monsterchild*>(MouseObj)->summontype(*Player1, true))
										isSummon = true;
								}
								else if (MouseObj->getType() == 't')
								{
									static_cast<Trap*>(MouseObj)->TrapCards(*Player1, *Player2);
								}
							}

							if (!Player2->Graveyard.Show)
								Player1->Graveyard.Click(window);
							if (!Player1->Graveyard.Show)
								Player2->Graveyard.Click(window);
						}
						else
						{
							if ((!(Player1->Graveyard.Show || Player2->Graveyard.Show)) && !MouseObj)
								Menue.Open();

							if (MouseObj && MouseObj->getPlayer() == Turn)
							{
								if (MouseObj->getType() == 'm' && !isSummon)
									if (static_cast<monsterchild*>(MouseObj)->summontype(*Player1, false))
										isSummon = true;
							}

							Player1->Graveyard.Show = false;
							Player2->Graveyard.Show = false;
						}
					}
				}


				//Battle Phase
				else if (Phase == 3)
				{
					if (EventCatch(window) == Event::MouseButtonPressed)
					{
						if (Mouse::isButtonPressed(Mouse::Left))
						{
							Menue.Click(window);

							if (FirstAttack && MouseObj && MouseObj->getPlayer() == Turn)
							{
								if (MouseObj->getType() == 'm')
									static_cast<monsterchild*>(MouseObj)->killem(*Player1, *Player2);

							}

							if (!Player2->Graveyard.Show)
								Player1->Graveyard.Click(window);
							if (!Player1->Graveyard.Show)
								Player2->Graveyard.Click(window);
						}
						else
						{
							if ((!(Player1->Graveyard.Show || Player2->Graveyard.Show)) && !MouseObj)
								Menue.Open();
							Player1->Graveyard.Show = false;
							Player2->Graveyard.Show = false;
						}
					}
				}


				//End Phase
				else if (Phase == 5)
				{
					FirstAttack = true;
					if (Turn == 1)
						Turn = 2;
					else
						Turn = 1;

					for (int i = 0; i < Player1->Ground.getMonsterSize(); i++)
						static_cast<monsterchild*>(Player1->Ground.DisplayCard(i))->set_didattack(false);

					isSummon = false;
					Phase = 1;
					swap(Player1, Player2);
				}
			}
			
			
		}
		window.display();
	}
	
	delete obj;
	delete ViewCard;
	delete Player1;
	delete Player2;
}

Card* MousePos(RenderWindow& window, Player& Player1, Player& Player2, bool Act)
{
	if (Act)
	{
		Card* ret = nullptr;
		Vector2f pos = static_cast<Vector2f>(Mouse::getPosition(window));
		if (Player1.Graveyard.Show)
			ret = Player1.Graveyard.DisplayCard(pos);
		else if (Player2.Graveyard.Show)
			ret = Player2.Graveyard.DisplayCard(pos);
		else if (Mouse::getPosition(window).y < (float)windowy / 2)
		{
			ret = Player2.Graveyard.DisplayCard(pos);
			if (!ret)
			{
				if (Mouse::getPosition(window).y < handcardHEIGHT / 2)
					ret = Player2.Hand.DisplayCard(pos);
				else
					ret = Player2.Ground.DisplayCard(pos);
			}

		}
		else
		{
			ret = Player1.Graveyard.DisplayCard(pos);
			if (!ret)
			{
				if (Mouse::getPosition(window).y > windowy - (handcardHEIGHT / 2))
					ret = Player1.Hand.DisplayCard(pos);
				else
					ret = Player1.Ground.DisplayCard(pos);
			}
		}
		return ret;
	}
	else
		return nullptr;
}

Event::EventType EventCatch(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window.close();
			break;
		case Event::KeyPressed:
			if (Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}
	}
	return event.type;
}

