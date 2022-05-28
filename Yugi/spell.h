#pragma once

#include<set>
#include "Card.h"


class Player;

class parentspell :public Card
{
public:
	parentspell();
	virtual void fn(Player& player, Player& enemy) = 0;
};
class harpie_feather_duster :public parentspell
{
public:
	harpie_feather_duster(int);
	void fn(Player & player, Player & enemy) override;

};

class Giant_turnado :public parentspell
{
public:
	Giant_turnado(int);
	void fn(Player & player, Player & enemy) override;
};


class RAIGEKI :public parentspell
{
public:
	RAIGEKI(int);
	void fn(Player & player, Player & enemy) override;
};


class destruction : public parentspell
{
public:
	destruction(int);
	void fn(Player & player, Player & enemy) override;
};

class tribute_domed : public parentspell
{
	bool Activate;
public:
	tribute_domed(int);
	void fn(Player& player, Player& enemy) override;
};

class monsterReborn :public parentspell
{
	bool Activate;
public:
	monsterReborn(int);
	void fn(Player& player, Player& enemy) override;
};
class space : public parentspell
{
	bool Activate;
public:
	space(int);
	void fn(Player& player, Player& enemy) override;

};
class potofgreed :public parentspell
{
public:
	potofgreed(int);
	void fn(Player& player, Player& enemy) override;
};

class graceful_charity : public parentspell
{
	vector< Card* > vec;

public:
	graceful_charity(int);
	void fn(Player& player, Player& enemy) override;
};

class heavy_storm : public parentspell
{
public:
	heavy_storm(int);
	void fn(Player& player, Player& enemy) override;
};
class Dark_hole : public parentspell
{
public:
	Dark_hole(int);
	void fn(Player& player, Player& enemy) override;
};
class change_of_heart :public parentspell
{
	bool Activate;
public:
	change_of_heart(int x);


	void fn(Player& player, Player& enemy) override;
};
