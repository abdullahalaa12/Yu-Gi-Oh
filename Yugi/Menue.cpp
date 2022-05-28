#include "Menue.h"
#include"Global.h"
#include<SFML/Audio.hpp>


MessageMenue MessMenue;
Card* Select = nullptr;
RenderWindow window(VideoMode(windowX, windowy), "Yu",Style::Fullscreen);
Card* MouseObj = nullptr;
Card* Animation = nullptr;

SoundBuffer buffe;
Sound sounde;

void Menue::set()
{
	if (*Phase == 3)
	{
		Message.setString("End your Battle Phase?");
		Button[0].setString("Proceed to Main Phase 2");
		Button[1].setString("Complete turn");
		Button[2].setString("Continue Battle Phase");
		Button[3].setString("Exit");
	}
	else
	{
		Message.setString("End your Main Phase?");
		Button[0].setString("Enter Battle Phase");
		Button[1].setString("Complete turn");
		Button[2].setString("Continue Main Phase");
		Button[3].setString("Exit");
	}

	Vector2f Pos(windowX / 2 - Message.getGlobalBounds().width / 2, Container.getGlobalBounds().top + 100);
	Message.setPosition(Pos.x, Pos.y - 80);

	for (int i = 0; i < 4; i++)
		Button[i].setPosition(Pos.x, Pos.y + (50 * i));
}

int Menue::Mouse(RenderWindow& window)
{
	Vector2f pos = static_cast<Vector2f>(Mouse::getPosition(window));

	for (int i = 0; i < 4; i++)
	{
		if (Button[i].getGlobalBounds().contains(pos))
		{
			Button[i].setFillColor(Color(140, 160, 255));
			for (int j = i + 1; j < 4; j++)
				Button[j].setFillColor(Color::White);
			return i;
		}
		else
		{
			Button[i].setFillColor(Color::White);
		}
	}
	return -1;
}

void Menue::Open()
{
	if (Show || MessMenue.Show)
	{
		Show = false;
		MessMenue.Show = false;
	}
	else if (*Phase == 4)
	{
		MessMenue.Show = true;
		MessMenue.setMessage("End Your Turn ?");
	}
	else
	{
		set();
		Show = true;
	}
}

bool Menue::getShow()
{
	return Show || MessMenue.Show;
}

Menue::Menue(int* P)
{
	Phase = P;
	Show = false;

	Container.setSize(Vector2f(400.f, 300.f));
	Container.setFillColor(Color(1, 1, 1, 450));
	Container.setOutlineThickness(2.f);
	Container.setOutlineColor(Color(200, 120, 120, 100));
	Container.setPosition((windowX / 2 - Container.getGlobalBounds().width / 2)
		, (windowy / 2 - Container.getGlobalBounds().height / 2));

	Message.setFont(MessMenue.font);
	Message.setFillColor(Color::White);

	for (int i = 0; i < 4; i++)
	{
		Button[i].setFont(MessMenue.font);
		Button[i].setCharacterSize(25);
	}

	set();
}

void Menue::Draw(RenderWindow& window)
{
	if (Show)
	{
		Mouse(window);
		window.draw(Container);
		window.draw(Message);
		for (int i = 0; i < 4; i++)
			window.draw(Button[i]);
	}
}

void Menue::Click(RenderWindow& window)
{
	if (Show)
	{
		Vector2f pos = static_cast<Vector2f>(Mouse::getPosition(window));
		int Clicked = Mouse(window);
		if (Clicked != -1)
		{
			if (Clicked == 0)
			{
				(*Phase)++;
				set();
			}
			else if (Clicked == 1)
			{
				MessMenue.Show = true;
				MessMenue.setMessage("End Your Turn ?");
			}
			else if (Clicked == 3)
			{
				window.close();
			}
			Show = false;
		}
	}
	else if (MessMenue.Show)
	{
		if (MessMenue.YesClicked(window))
		{
			buffe.loadFromFile("Audio/joey_EndTurn2.wav");
			sounde.setBuffer(buffe);
			sounde.play();
			(*Phase) = 5;
			set();
			MessMenue.Show = false;
		}
		else if (MessMenue.NoClicked(window))
			MessMenue.Show = false;

	}
}

Menue::~Menue()
{
}

MessageMenue::MessageMenue()
{
	font.loadFromFile("Balonku-Regular.ttf");
	Show = false;

	Menue.setSize(Vector2f(400.f, 250.f));
	Menue.setFillColor(Color(1, 1, 1, 450));
	Menue.setOutlineThickness(2.f);
	Menue.setOutlineColor(Color(200, 120, 120, 100));
	Menue.setPosition((windowX / 2 - Menue.getGlobalBounds().width / 2)
		, (windowy / 2 - Menue.getGlobalBounds().height / 2));

	Message.setFont(font);
	Message.setString(" ");
	Message.setCharacterSize(20);
	Message.setFillColor(Color::White);

	Yes.setFont(font);
	Yes.setString("Yes");
	Yes.setCharacterSize(20);
	Yes.setPosition(windowX / 2 - Yes.getGlobalBounds().width / 2, Menue.getGlobalBounds().top + 100);

	No.setFont(font);
	No.setString("No");
	No.setCharacterSize(20);
	No.setPosition(windowX / 2 - No.getGlobalBounds().width / 2, Menue.getGlobalBounds().top + 150);
}

void MessageMenue::setMessage(string m)
{
	Message.setString(m);
	Message.setPosition(windowX / 2 - Message.getGlobalBounds().width / 2, Menue.getGlobalBounds().top + 20);
}

bool MessageMenue::YesClicked(RenderWindow& window)
{
	Vector2f pos = static_cast<Vector2f>(Mouse::getPosition(window));
	return Yes.getGlobalBounds().contains(pos);
}

bool MessageMenue::NoClicked(RenderWindow& window)
{
	Vector2f pos = static_cast<Vector2f>(Mouse::getPosition(window));
	return No.getGlobalBounds().contains(pos);
}

void MessageMenue::Draw(RenderWindow& window)
{
	if (Show)
	{
		Vector2f pos = static_cast<Vector2f>(Mouse::getPosition(window));
		if (Yes.getGlobalBounds().contains(pos))
			Yes.setFillColor(Color(140, 160, 255));
		else if (No.getGlobalBounds().contains(pos))
			No.setFillColor(Color(140, 160, 255));
		else
		{
			Yes.setFillColor(Color::White);
			No.setFillColor(Color::White);
		}
		window.draw(Menue);
		window.draw(Message);
		window.draw(Yes);
		window.draw(No);
	}
}

MessageMenue::~MessageMenue()
{
}
