#pragma once

#include"Card.h"

class Player;


class Trap : public Card
{
public:
	Trap();
	virtual void TrapCards(Player& player, Player& Enemy) = 0;
};

class Torrential_Tribute : public Trap
{
	bool Activate;
public:
	Torrential_Tribute(int);
	void TrapCards(Player& player, Player& Enemy) override;
};
class GravelStorm :public Trap
{
	bool Activate;
public:
	GravelStorm(int);
	void TrapCards(Player& player, Player& Enemy) override;
};
class GiftCard :public Trap
{
	bool Activate;
public:
	GiftCard(int);
	void TrapCards(Player& player, Player& Enemy) override;
};
class Heavy_Slump :public Trap
{
	bool Activate;
public:
	Heavy_Slump(int);
	void TrapCards(Player& player, Player& Enemy) override;
};
class Graceful_Tear :public Trap
{
	bool Activate;
public:
	Graceful_Tear(int);
	void TrapCards(Player& player, Player& Enemy) override;
};
class Destruct_Potion :public Trap
{
	bool Activate;
public:
	Destruct_Potion(int);
	void TrapCards(Player& player, Player& Enemy) override;
};
class Blasting_The_Ruins :public Trap
{
	bool Activate;
public:
	Blasting_The_Ruins(int);
	void TrapCards(Player& player, Player& Enemy) override;
};
class JarOfGreed :public Trap
{
	bool Activate;
public:
	JarOfGreed(int player);
	void TrapCards(Player& player, Player& Enemy) override;
};
class Gallantry :public Trap
{
public:
	Gallantry(int player);
	void TrapCards(Player& player, Player& Enemy) override;
};
class LocalizedTornado :public Trap
{
public:
	LocalizedTornado(int player);
	void TrapCards(Player& player, Player& Enemy) override;
};