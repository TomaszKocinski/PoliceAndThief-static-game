#ifndef PLAYABLE_CHARACTERS_H
#define PLAYABLE_CHARACTERS_H
#pragma once
#include "Sprite.h"
#include "map.h"
class Graphics;
class Character;
class MAP;
enum CheckWinEnum;
class Playable_Characters{


public:
	Playable_Characters(Graphics& ,MAP*);

	Character* thief;
	Character* police;
	Character* police2;
	MAP* map;
	void Automatic_move(bool);
	pair<vector<vector<pair<int, int>>>, pair<int, int>> A_star_algorithm(pair<int, int>&, pair<int, int>&);
	bool* GetAccessAbleNeighbors();
	bool* GetNeighbors();
	int reconstrut_path_from_A_star_algorithm(pair<vector<vector<pair<int, int>>>, pair<int, int>>, Character*);
	int size_of_path_from_A_star_algorithm(pair<vector<vector<pair<int, int>>>, pair<int, int>> arg, pair<int, int>);
	int Automatic_move_police(Character*);
	int Automatic_move_police_random(Character*);
	int Automatic_move_police_single_entrance(bool* aan);
	pair<int, int> Automatic_move_police_set_target(Character *);
	int Automatic_move_thief();
	int Automatic_move_thief_points();
	
	bool Are_police_neighbors_of_thief(Character*);
	bool Can_character_move(Character*);
	double Playable_Characters::Automatic_move_thief_characterfactor();
	CheckWinEnum checkwincondition(int turns);
	Playable_Characters operator=(Playable_Characters& other);
	
};
#endif