#pragma once
#include "Sprite.h"
#include "map.h"
class Graphics;
class Character;
class MAP;
class Playable_Characters{


public:
	Playable_Characters(Graphics& ,MAP&);

	Character* thief;
	Character* police;
	Character* police2;

	void Automatic_move(MAP&,bool);
	pair<vector<vector<pair<int, int>>>, pair<int, int>> A_star_algorithm(MAP&, pair<int, int>&, pair<int, int>&);
	bool* GetAccessAbleNeighbors(MAP&);
	int reconstrut_path_from_A_star_algorithm(pair<vector<vector<pair<int, int>>>, pair<int, int>>, Character*);
	int size_of_path_from_A_star_algorithm(pair<vector<vector<pair<int, int>>>, pair<int, int>> arg, pair<int, int>);
	int ManhatanDinstance(MAP& map);
	int ManhatanDinstance_points(MAP& map);
	double Playable_Characters::ManhatanDinstance_characterfactor(MAP& map);
};