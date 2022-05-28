#include "Player.h"
#include<SFML/Audio.hpp>


SoundBuffer bu;
Sound su;

Player::Player(int player, allmap* Map) :
	Deck(DeckCapacity, player), Hand(HandCapacity, player, Map)
	, Graveyard(player, Map), Ground(GroundCapacity, player, Map)
{
	LifePoints = 8000;
	lf = to_string(LifePoints);
	font.loadFromFile("Font.ttf");
	PointsText.setFont(font);
	PointsText.setString(lf);
	PointsText.setFillColor(Color::White);
	PointsText.setCharacterSize(60);

	HealthContainer.setSize(Vector2f(viewgroundcardsX-40, 50.f));
	HealthContainer.setFillColor(Color(1, 1, 1, 450));
	HealthContainer.setOutlineThickness(2.f);
	//HealthContainer.setOutlineColor(Color(200, 120, 120, 100));
	HealthContainer.setOutlineColor(Color::White);
	HealthBar.setSize(Vector2f(viewgroundcardsX - 40, 50.f));
	HealthBar.setFillColor(Color::Green);
	if (player == 1)
	{
		PointsText.setPosition((viewgroundcardsX / 2) - (PointsText.getGlobalBounds().width / 2), windowy - 155);
		HealthContainer.setPosition(20, PointsText.getPosition().y + 90);
	}
	else
	{
		PointsText.setPosition((viewgroundcardsX / 2) - (PointsText.getGlobalBounds().width / 2), 80.f);
		HealthContainer.setPosition(20, PointsText.getPosition().y - 60);
	}
	HealthBar.setPosition(HealthContainer.getPosition());
}
void Player::DecreaseLifePoints(int Decrease)
{
	bu.loadFromFile("Audio/joey_Uw.wav");
	su.setBuffer(bu);
	su.play();
	this->LifePoints -= Decrease;
	if (LifePoints < 0)
		LifePoints = 0;
	lf = to_string(LifePoints);
	PointsText.setString(lf);
	PointsText.setPosition((viewgroundcardsX / 2) - (PointsText.getGlobalBounds().width / 2), PointsText.getPosition().y);

	int tmp;
	if (LifePoints > 8000)
		tmp = 251.f;
	else
		tmp = (251.f * LifePoints) / (float)8000;
	Uint8 Red;
	Uint8 Green;
	if (LifePoints > 4000)
		Red = (255 * (8000 - LifePoints)) / (float)4000;
	else
		Red = 255;
	if (LifePoints < 4000)
		Green = (255.f * (LifePoints)) / (float)4000;
	else
		Green = 255;
	HealthBar.setSize(Vector2f(tmp, HealthBar.getSize().y));
	HealthBar.setFillColor(Color(Red, Green, 0));
}
void Player::IncreaseLifePoints(int Increase)
{
	bu.loadFromFile("Audio/joey_Eat1.wav");
	su.setBuffer(bu);
	su.play();
	this->LifePoints += Increase;
	lf = to_string(LifePoints);
	PointsText.setString(lf);
	PointsText.setPosition((viewgroundcardsX / 2) - (PointsText.getGlobalBounds().width / 2), PointsText.getPosition().y);

	int tmp;
	if (LifePoints > 8000)
	{
		tmp = 251.f;
	}
	else
		tmp = (251.f * LifePoints) / (float)8000;
	Uint8 Red;
	Uint8 Green;
	if (LifePoints <= 8000)
	{
		if (LifePoints > 4000)
			Red = (255.f * (8000 - LifePoints)) / (float)4000;
		else
			Red = 255;
		if (LifePoints < 4000)
			Green = (255.f * (LifePoints)) / (float)4000;
		else
			Green = 255;
	}
	else
	{
		Red = 0;
		Green = 255;
	}
	HealthBar.setSize(Vector2f(tmp, HealthBar.getSize().y));
	HealthBar.setFillColor(Color(Red, Green, 0));
}
void Player::Draw(RenderWindow& window)
{
	window.draw(PointsText);
	window.draw(HealthContainer);
	window.draw(HealthBar);
}
Player::~Player()
{
}
