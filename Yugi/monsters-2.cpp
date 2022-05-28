#include"monsters-2.h"
#include"Player.h"
#include"Global.h"
#include<SFML/Audio.hpp>

SoundBuffer Attackbuffer;
Sound AttackSound;

monstersparent::monstersparent()
{
	attack = 0;
	deffence = 0;
	rarity = 0;
	specialtype = 0;
	attribute = 0;
	type = 0;
	level = 0;
	didattack = false;
}

void monstersparent::setmonster()
{
}

void monstersparent::SETattack(int attack)
{
	this->attack = attack;
}

void monstersparent::SETdefence(int deffence)

{
	this->deffence = deffence;
}

void monstersparent::SETlevel_rarity(int level)
{
	this->level = level;
	if (level < 5)
	{
		rarity = 'a'; // monster of such level require no tribute monsters
	}
	else if (level < 7)
	{
		rarity = 'b'; // monsters of such level require 1 tribute monster
		specialtype = SpecialMonstersummon::tribute;
	}
	else
	{
		rarity = 'c';//monsters of such level require 2 tribute monsters
		specialtype = SpecialMonstersummon::tribute;
	}
}

void monstersparent::SET_attribute(uint8_t attribute)
{
	this->attribute = attribute;
}

void monstersparent::SET_type(uint8_t type)
{
	this->type = type;
}

void monstersparent::SET_specialtype(uint8_t specialtype)
{
	this->specialtype = specialtype;
}

int monstersparent::get_attack()
{
	return attack;
}

int monstersparent::get_defence()
{
	return deffence;
}

int monstersparent::get_level()
{
	return level;
}

char monstersparent::get_rarity()
{
	return rarity;
}

uint8_t monstersparent::get_attribute()
{
	return attribute;
}

uint8_t monstersparent::get_type()
{
	return type;
}

uint8_t monstersparent::get_specialtype()
{
	return specialtype;
}

//void monsterchild::set_vector_THEcards(vector<returned> THEcards)
//{
//	for (int i = 0; i < THEcards.size(); i++)
//	{
//		this->THEcards.push_back(THEcards[i]);
//	}
//}

monsterchild::monsterchild(int player)
{
	Pos = Vector2f(0,0);
	Arrow.setTexture(ArrowTex);	
	Arrow.setOrigin(Arrow.getGlobalBounds().width / 2, Arrow.getGlobalBounds().height / 2);
	Arrow.setScale(0.17, 0.17);
	SetType('m'); //card class
	SetPlayer(player); //card class
	int r = rand() % 28;
	
	switch (r)
	{
	case 0:
		SetCardName("Penguin Soldier");//card class
		SetFrontCard("Monsters/Penguin Soldier.jpg");//card class
		set(750, 500, 2, water, aqua);
		break;
	case 1:
		SetCardName("Giant Soldier");//card class
		SetFrontCard("Monsters/Giant Soldier.jpeg");//card class
		set(1300, 2000, 3, earth, rock);
		break;
	case 2:
		SetCardName("Baby Dragon");//card class
		SetFrontCard("Monsters/Baby Dragon.jpg");//card class
		set(1200, 700, 3, wind, dragon);
		break;
	case 3:
		SetCardName("Spherous Lady");//card class
		SetFrontCard("Monsters/Spherous Lady.jpg");//card class
		set(400, 1400, 3, earth, rock);
		break;
	case 4:
		SetCardName("Morphing Jar #2");//card class
		SetFrontCard("Monsters/Morphing Jar #2.jpg");//card class
		set(800, 700, 3, earth, rock);
		break;
	case 5:
		SetCardName("Sangan");//card class
		SetFrontCard("Monsters/Sangan.jpg");//card class
		set(1000, 600, 3, dark, fiend);
		break;
	case 6:
		SetCardName("Kaibaman");//card class
		SetFrontCard("Monsters/Kaibaman.jpg");//card class
		set(200, 700, 3, light, warrior);
		break;
	case 7:
		SetCardName("The Gross Ghost Of Fled Dreams");//card class
		SetFrontCard("Monsters/The Gross Ghost Of Fled Dreams.jpg");//card class
		set(1300, 1800, 3, dark, fiend);
		break;
	case 8:
		SetCardName("Tiger AXE");//card class
		SetFrontCard("Monsters/Tiger AXE.jpg");//card class
		set(1300, 1100, 4, earth, beast_warrior);
		break;
	case 9:
		SetCardName("Gemini Elf");//card class
		SetFrontCard("Monsters/Gemini Elf.jpg");//card class
		set(1900, 900, 4, earth, spellcaster);
		break;
	case 10:
		SetCardName("Gradius");//card class
		SetFrontCard("Monsters/Gradius.jpg");//card class
		set(1200, 800, 4, light, machine);
		break;
	case 11:
		SetCardName("Island Turtle");//card class
		SetFrontCard("Monsters/Island Turtle.jpg");//card class
		set(1100, 2000, 4, water, aqua);
		break;
	case 12:
		SetCardName("Goblin Attack Force");//card class
		SetFrontCard("Monsters/Goblin Attack Force.jpg");//card class
		set(2300, 0, 4, earth, warrior);
		break;
	case 13:
		SetCardName("Zombyra the Dark");//card class
		SetFrontCard("Monsters/Zombyra the Dark.jpg");//card class
		set(2100, 500, 4, dark, warrior);
		break;
	case 14:
		SetCardName("AXE Raider");//card class
		SetFrontCard("Monsters/AXE Raider.jpg");//card class
		set(1700, 1150, 4, earth, warrior);
		break;
	case 15:
		SetCardName("Alligator's Sword");//card class
		SetFrontCard("Monsters/Alligator's Sword.jpg");//card class
		set(1500, 1200, 4, earth, beast);
		break;
	case 16:
		SetCardName("Gamma The Magent Warrior");//card class
		SetFrontCard("Monsters/Gamma The Magent Warrior.jpg");//card class
		set(1500, 1800, 4, earth, rock);
		break;
	case 17:
		SetCardName("Alpha The Magent Warrior");//card class
		SetFrontCard("Monsters/Alpha The Magent Warrior.jpg");//card class
		set(1400, 1700, 4, earth, beast);
		break;
	case 18:
		SetCardName("Witch of the Black Forest");//card class
		SetFrontCard("Monsters/Witch of the Black Forest.jpg");//card class
		set(1100, 1200, 4, dark, spellcaster);
		break;
	case 19:
		SetCardName("Headless Knight");//card class
		SetFrontCard("Monsters/Headless Knight.jpg");//card class
		set(1450, 1700, 4, earth, fiend);
		break;
	case 20:
		SetCardName("Gadget Soldier");//card class
		SetFrontCard("Monsters/Gadget Soldier.jpg");//card class
		set(1800, 2000, 6, fire, machine);
		break;
	case 21:
		SetCardName("Jinzo");//card class
		SetFrontCard("Monsters/Jinzo.jpg");//card class
		set(2400, 1500, 6, dark, machine);
		break;
	case 22:
		SetCardName("Flame Cerebrus");//card class
		SetFrontCard("Monsters/Flame Cerebrus.jpg");//card class
		set(2100, 1800, 6, fire, pyro);
		break;
	case 23:
		SetCardName("Dark magician");//card class
		SetFrontCard("Monsters/Dark magician.jpg");//card class
		set(2500, 2100, 7, dark, spellcaster);
		break;
	case 24:
		SetCardName("Garnecia Elefantis");//card class
		SetFrontCard("Monsters/Garnecia Elefantis.jpg");//card class
		set(2400, 2000, 7, earth, beast_warrior);
		break;
	case 25:
		SetCardName("Buster Blader");//card class
		SetFrontCard("Monsters/Buster Blader.jpg");//card class
		set(2600, 2300, 7, earth, warrior);
		break;
	case 26:
		SetCardName("Slot Machine");//card class
		SetFrontCard("Monsters/Slot Machine.jpg");//card class
		set(2000, 2300, 7, dark, machine);
		break;
	case 27:
		SetCardName("Red-Eyes B. Dragon");//card class
		SetFrontCard("Monsters/Red-Eyes B. Dragon.jpg");//card class
		set(2400, 2000, 7, dark, dragon);
		break;
	
	
	}
 
}

void monsterchild::set(int attack, int deffence, int level, uint8_t attribute, uint8_t type)
{
	SETattack(attack);
	SETdefence(deffence);
	SETlevel_rarity(level);
	SET_attribute(attribute);
	SET_type(type);
}

bool monsterchild::summontype(Player& player, bool summon)
{
	if (getPlace() == 'H' && player.Ground.getMonsterSize() < 5)
	{
		char getrar = get_rarity();
		switch (getrar)
		{
		case 'b':
			return find(player,1);
			break;
		case 'c':
			return find(player,2);
			break;
		default:
			if (!summon)
			{
				int attack = get_attack();
				SETattack(get_defence());
				SETdefence(attack);
				SetActivate(false); //card class
			}
			player.Ground.AddCard(player.Hand.TakeCard(this));
			return true;

		}
	}
	return false;
}

bool monsterchild::find(Player& player,int number)
{
	if (player.Ground.getMonsterSize() > (number - 1))
	{
		bool* tmp = TheSelect("wanna tribute ?");
		if (tmp && *tmp)
		{
			if (MouseObj)
			{
				if (MouseObj->getPlace() == 'G' && MouseObj->getType() == 'm' && MouseObj->getPlayer() == getPlayer())
				{
					for (int i = 0; i < THEcards.size(); i++)
						if (THEcards[i] == MouseObj)
							return false;
					THEcards.push_back(MouseObj);
				}
			}

			if (THEcards.size() == number)
			{
				while (THEcards.size() > 0)
				{
					player.Graveyard.AddCard(player.Ground.TakeCard(THEcards.back()));
					THEcards.pop_back();
				}
				player.Ground.AddCard(player.Hand.TakeCard(this));
				Select = nullptr;
				*(tmp) = false;
				return true;
			}
		}
	}
	return false;

}
void  monstersparent::set_didattack(bool didattack)
{
	this->didattack = didattack;
}
bool  monstersparent::get_didattack()
{
	return didattack;
}
void  monsterchild::killem(Player& me, Player& enemy)
{
	if (getPlace() == 'G' && !get_didattack() && GetActivate())
	{
		static Vector2f total;
		if (Animation)
		{
			EventCatch(window);
			if ((Arrow.getPosition().x > Pos.x - 5) && (Arrow.getPosition().x < Pos.x + 5)
				&& (Arrow.getPosition().y > Pos.y - 5) && (Arrow.getPosition().y < Pos.y + 5))
			{
				if (Animation != this)
				{
					monsterchild* tmp = static_cast<monsterchild*>(Animation);
					if (get_attack() > tmp->get_attack())
					{
						enemy.Graveyard.AddCard(enemy.Ground.TakeCard(tmp));
						enemy.DecreaseLifePoints(get_attack() - tmp->get_attack());
					}
					else if (get_attack() < tmp->get_attack())
					{
						me.Graveyard.AddCard(me.Ground.TakeCard(this));
						me.DecreaseLifePoints(tmp->get_attack() - get_attack());
					}
					else
					{
						me.Graveyard.AddCard(me.Ground.TakeCard(this));
						enemy.Graveyard.AddCard(enemy.Ground.TakeCard(tmp));
					}
				}
				else
				{
					enemy.DecreaseLifePoints(get_attack());
				}
				set_didattack(true);
				Animation = nullptr;
				Select = nullptr;
				Arrow.setPosition(getPosition().x + (GetCardSprite().getGlobalBounds().width / 2),
					getPosition().y + (GetCardSprite().getGlobalBounds().height / 2));
				if (getPlayer() == 1)
					Arrow.setRotation(0);
				else
					Arrow.setRotation(180);
				return;
			}
			else
			{
				Arrow.move(total * ((float)1 / 200));
			}
		}
		else 
		{
			if (!Select)
				Select = this;
			float rot;
			float dy, dx;
			if (enemy.Ground.getMonsterSize() > 0)
			{
				dy = ((float)Mouse::getPosition(window).y - Arrow.getPosition().y);
				dx = ((float)Mouse::getPosition(window).x - Arrow.getPosition().x);
				if (EventCatch(window) == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
				{
					if (MouseObj)
					{
						if (MouseObj->getPlayer() != getPlayer() && MouseObj->getPlace() == 'G' && MouseObj->getType() == 'm')
						{
							Attackbuffer.loadFromFile("Audio/yugiattack.wav");
							AttackSound.setBuffer(Attackbuffer);
							AttackSound.play();
							Animation = MouseObj;
							Pos = (Vector2f)Mouse::getPosition(window);
							total = Pos - Arrow.getPosition();
						}

					}
				}


			}
			else
			{
				Attackbuffer.loadFromFile("Audio/yugiattack.wav");
				AttackSound.setBuffer(Attackbuffer);
				AttackSound.play();
				Animation = this;
				Pos.x = windowX / 2;
				if (getPlayer() == 1)
					Pos.y = 0;
				else
					Pos.y = windowy;
				dy = Pos.y - Arrow.getPosition().y;
				dx = Pos.x - Arrow.getPosition().x;
				total = Pos - Arrow.getPosition();
			}

			rot = (atan2(dy, dx)) * (180 / 3.14159265);
			rot += 90;
			Arrow.setRotation(rot);
		}
	}
}