#pragma once
#include "Sprite.h"
#include "map.h"
class Graphics;
class Playable_Characters{


public:
	Playable_Characters(){};
	Playable_Characters(Graphics);

	Character* thief;
	Character* police;
	Character* police2;

	std::pair<int,int> distance() const;
	void Automatic_move(MAP);
	int A_star_algorithm(MAP,Character*,Character*);
};