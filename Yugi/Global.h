#pragma once

#include"Rec.h"
#include"Player.h"
#include"Menue.h"

extern Card* Select;
extern MessageMenue MessMenue;
extern RenderWindow window;
extern Card* MouseObj;
extern Card* Animation;

Card* MousePos
(RenderWindow& window, Player& Player1, Player& Player2, bool Act);

Event::EventType EventCatch(RenderWindow& window);



