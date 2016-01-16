#pragma once
#include "Sprite.h"
#include "map.h"
class Graphics;
class Character;
class Playable_Characters{


public:
	Playable_Characters(){};
	Playable_Characters(Graphics,MAP&);

	Character* thief;
	Character* police;
	Character* police2;

	std::pair<int,int> distance() const;
	void Automatic_move(MAP,bool);
	int A_star_algorithm(MAP,Character*,Character*);
	int reconstrut_path_from_A_star_algorithm(vector<vector<pair<int,int>>>,pair<int,int>,Character*);
};