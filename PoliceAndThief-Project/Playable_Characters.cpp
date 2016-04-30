#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "map.h"
#include "Playable_Characters.h"

#include <iostream>
#include <map>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;
typedef pair<int, int> pint;
enum CheckWinEnum
{
	Nothing, winpolice, losepolice, winthief, losethief
};
enum directions
{
	N = 1, E = 2, S = 3, W = 4
};
Playable_Characters::Playable_Characters(Graphics& graphics, MAP& game_board){
	thief = new Character(graphics, "images/thief.png", 0, 0, 40, 40, 26, 35, 0, 0, game_board);
	police = new Character(graphics, "images/police.png", 0, 0, 40, 40, 26, 35, 2, 2, game_board);
	police2 = new Character(graphics, "images/police2.png", 0, 0, 40, 40, 26, 35, 4, 4, game_board);
};

bool* Playable_Characters::GetAccessAbleNeighbors(MAP& map){
	bool* neighbors = new bool[4];
	if (thief->pos_y > 0 && map.map[thief->pos_y - 1][thief->pos_x].accessable() && map.cangetto(pair<int, int>(thief->pos_x, thief->pos_y - 1))){
		neighbors[0] = true;
	}
	else neighbors[0] = false;
	if (thief->pos_y < map.max_y - 1 && map.map[thief->pos_y + 1][thief->pos_x].accessable() && map.cangetto(pair<int, int>(thief->pos_x, thief->pos_y + 1))){
		neighbors[2] = true;
	}
	else neighbors[2] = false;
	if (thief->pos_x < map.max_x - 1 && map.map[thief->pos_y][thief->pos_x + 1].accessable() && map.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y))){
		neighbors[1] = true;
	}
	else neighbors[1] = false;
	if (thief->pos_x > 0 && map.map[thief->pos_y][thief->pos_x - 1].accessable() && map.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y))){
		neighbors[3] = true;
	}
	else neighbors[3] = false;
	return neighbors;
}
bool* Playable_Characters::GetNeighbors(MAP& map){
	bool* neighbors = new bool[4];
	if (thief->pos_y > 0 && map.map[thief->pos_y - 1][thief->pos_x].accessable()){
		neighbors[0] = true;
	}
	else neighbors[0] = false;
	if (thief->pos_y < map.max_y  && map.map[thief->pos_y + 1][thief->pos_x].accessable()){
		neighbors[2] = true;
	}
	else neighbors[2] = false;
	if (thief->pos_x < map.max_x  && map.map[thief->pos_y][thief->pos_x + 1].accessable()){
		neighbors[1] = true;
	}
	else neighbors[1] = false;
	if (thief->pos_x > 0 && map.map[thief->pos_y][thief->pos_x - 1].accessable()){
		neighbors[3] = true;
	}
	else neighbors[3] = false;
	return neighbors;
}
int heuristic_cost_estimate(pair<int, int> start, pair<int, int> goal){

	int dest = 0,
		temp_x = goal.first,
		temp_y = goal.second;
	std::pair<int, int> dist = std::make_pair<int, int>(0, 0);
	while (start.second > temp_x){
		dest++;
		temp_x++;
	}
	while (start.second < temp_x){
		dest++;
		temp_x--;
	}
	while (start.first > temp_y){
		dest++;
		temp_y++;
	}
	while (start.first < temp_y){
		dest++;
		temp_y--;
	}

	return dest;
}

void Playable_Characters::Automatic_move(MAP& arg, bool police_turn){

	if (police_turn){

		pair<bool, bool> alreadymoved = pair<bool, bool>(false, false);
		if (police->pos_x < arg.max_x - 1 && police->pos_x + 1 == thief->pos_x && police->pos_y == thief->pos_y){
			if (police->pos_x > 0 && arg.map[police->pos_y][police->pos_x - 1].accessable()){
				police->move(4, arg); alreadymoved.first = true;
			}
			else if (police->pos_y > 0 && arg.map[police->pos_y - 1][police->pos_x].accessable()){
				police->move(1, arg); alreadymoved.first = true;
			}
			else if (police->pos_y < arg.max_y - 1 && arg.map[police->pos_y + 1][police->pos_x].accessable()){
				police->move(3, arg); alreadymoved.first = true;
			}
		}
		else if (police->pos_x > 0 && police->pos_x - 1 == thief->pos_x && police->pos_y == thief->pos_y){
			if (police->pos_x < arg.max_x - 1 && arg.map[police->pos_y][police->pos_x + 1].accessable()){
				police->move(2, arg); alreadymoved.first = true;
			}
			else if (police->pos_y > 0 && arg.map[police->pos_y - 1][police->pos_x].accessable())
			{
				police->move(1, arg); alreadymoved.first = true;
			}
			else if (police->pos_y < arg.max_y - 1 && arg.map[police->pos_y + 1][police->pos_x].accessable()){
				police->move(3, arg); alreadymoved.first = true;
			}

		}
		else if (police->pos_y > 0 && police->pos_x == thief->pos_x && police->pos_y - 1 == thief->pos_y){
			if (police->pos_y < arg.max_y - 1 && arg.map[police->pos_y + 1][police->pos_x].accessable()){
				police->move(3, arg); alreadymoved.first = true;
			}
			else if (police->pos_x > 0 && arg.map[police->pos_y][police->pos_x - 1].accessable())
			{
				police->move(2, arg); alreadymoved.first = true;
			}
			else if (police->pos_x < arg.max_x - 1 && arg.map[police->pos_y][police->pos_x + 1].accessable()){
				police->move(4, arg); alreadymoved.first = true;
			}

		}
		else if (police->pos_y < arg.max_y - 1 && police->pos_x == thief->pos_x && police->pos_y + 1 == thief->pos_y){
			if (police->pos_y > 0 && arg.map[police->pos_y - 1][police->pos_x].accessable()){
				police->move(1, arg); alreadymoved.first = true;
			}
			else if (police->pos_x < arg.max_x - 1 && arg.map[police->pos_y][police->pos_x + 1].accessable()){
				police->move(2, arg); alreadymoved.first = true;
			}
			else if (police->pos_x > 0 && arg.map[police->pos_y][police->pos_x - 1].accessable()){
				police->move(4, arg); alreadymoved.first = true;
			}

		}

		if (police2->pos_x < arg.max_x - 1 && police2->pos_x + 1 == thief->pos_x  && police2->pos_y == thief->pos_y){
			if (police2->pos_x > 0 && arg.map[police2->pos_y][police2->pos_x - 1].accessable()){
				police2->move(4, arg); alreadymoved.second = true;
			}
			else if (police2->pos_y > 0 && arg.map[police2->pos_y - 1][police2->pos_x].accessable()){
				police2->move(1, arg); alreadymoved.second = true;
			}
			else if (police2->pos_y < arg.max_y - 1 && arg.map[police2->pos_y + 1][police2->pos_x].accessable()){
				police2->move(3, arg); alreadymoved.second = true;
			}

		}
		else if (police2->pos_x > 0 && police2->pos_x - 1 == thief->pos_x  && police2->pos_y == thief->pos_y){
			if (police2->pos_x < arg.max_x - 1 && arg.map[police2->pos_y][police2->pos_x + 1].accessable()){
				police2->move(2, arg); alreadymoved.second = true;
			}
			else if (police2->pos_y > 0 && arg.map[police2->pos_y - 1][police2->pos_x].accessable())
			{
				police2->move(1, arg); alreadymoved.second = true;
			}
			else if (police2->pos_y < arg.max_y - 1 && arg.map[police2->pos_y + 1][police2->pos_x].accessable()){
				police2->move(3, arg); alreadymoved.second = true;
			}

		}
		else if (police2->pos_y > 0 && police2->pos_x == thief->pos_x && police2->pos_y - 1 == thief->pos_y){
			if (police2->pos_y < arg.max_y - 1 && arg.map[police2->pos_y + 1][police2->pos_x].accessable()){
				police2->move(3, arg); alreadymoved.second = true;
			}
			else if (police2->pos_x > 0 && arg.map[police2->pos_y][police2->pos_x - 1].accessable())
			{
				police2->move(2, arg); alreadymoved.second = true;
			}
			else if (police2->pos_x < arg.max_x - 1 && arg.map[police2->pos_y][police2->pos_x + 1].accessable()){
				police2->move(4, arg); alreadymoved.second = true;
			}

		}
		else if (police2->pos_y < arg.max_y - 1 && police2->pos_x == thief->pos_x && police2->pos_y + 1 == thief->pos_y){
			if (police2->pos_y > 0 && arg.map[police2->pos_y - 1][police2->pos_x].accessable()){
				police2->move(1, arg); alreadymoved.second = true;
			}
			else if (police2->pos_x < arg.max_x - 1 && arg.map[police2->pos_y][police2->pos_x + 1].accessable()){
				police2->move(2, arg); alreadymoved.second = true;
			}
			else if (police2->pos_y > 0 && arg.map[police2->pos_y][police2->pos_x - 1].accessable()){
				police2->move(4, arg); alreadymoved.second = true;
			}

		}

		try{
			if (!alreadymoved.first && heuristic_cost_estimate(pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)) > 3){
				alreadymoved.first = true;
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), this->police), arg);
			}
			if (!alreadymoved.second && heuristic_cost_estimate(pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)) > 3){
				alreadymoved.second = true;
				police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), this->police2), arg);
			}
			if (alreadymoved.first && alreadymoved.second)return;
			bool* neightbours = GetAccessAbleNeighbors(arg);
			if (neightbours[1] && neightbours[3]){// 1101 0111 0101
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y][thief->pos_x + 1].accessable() && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police2), arg);
			}
			else if (neightbours[0] && neightbours[2]){// 1111 1110 1011 1010
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y - 1)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y + 1][thief->pos_x].accessable() && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y + 1)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police2), arg);
			}
			else if (neightbours[0] && neightbours[1]){//1100
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y - 1)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y][thief->pos_x + 1].accessable() && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police2), arg);
			}
			else if (neightbours[0] && neightbours[3]){//1001
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y - 1)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y][thief->pos_x - 1].accessable() && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police2), arg);
			}
			else if (neightbours[1] && neightbours[2]){//0110
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y + 1][thief->pos_x].accessable() && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y + 1)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police2), arg);
			}
			else if (neightbours[2] && neightbours[3]){//0011
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y + 1)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y][thief->pos_x - 1].accessable() && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police2), arg);
			}
			else if (neightbours[0]){
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y - 1)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y - 1][thief->pos_x].accessable() && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y - 1)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police2), arg);
			}
			else if (neightbours[1]){
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y][thief->pos_x + 1].accessable() && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police2), arg);
			}
			else if (neightbours[2]){
				if (!alreadymoved.first &&  arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y + 1)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y + 1][thief->pos_x].accessable() && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y + 1)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police2), arg);
			}
			else if (neightbours[3]){
				if (!alreadymoved.first  && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police), arg);
				if (!alreadymoved.second && arg.map[thief->pos_y][thief->pos_x - 1].accessable() && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police2), arg);
			}
			else {
				cout << "all options exhauseted - didnt find possible spot for a star to travel, trying to launch a star regardres of that";
				if (!alreadymoved.first && arg.map[thief->pos_y][thief->pos_x].accessable() && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), this->police), arg);
				else{
					if (!alreadymoved.first){
						if (police->pos_x > 0 && arg.map[police->pos_y][police->pos_x - 1].accessable()){
							police->move(4, arg); alreadymoved.first = true;
						}
						else if (police->pos_y > 0 && arg.map[police->pos_y - 1][police->pos_x].accessable()){
							police->move(1, arg); alreadymoved.first = true;
						}
						else if (police->pos_y < arg.max_y - 1 && arg.map[police->pos_y + 1][police->pos_x].accessable()){
							police->move(3, arg); alreadymoved.first = true;
						}
						else if (police->pos_x < arg.max_x - 1 && arg.map[police->pos_y][police->pos_x + 1].accessable()){
							police->move(2, arg); alreadymoved.first = true;
						}
					}
				}
				if (!alreadymoved.second && arg.map[thief->pos_y][thief->pos_x].accessable() && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y)))
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), this->police2), arg);
				else{
					if (!alreadymoved.second){
						if (police2->pos_x > 0 && arg.map[police2->pos_y][police2->pos_x - 1].accessable()){
							police2->move(4, arg); alreadymoved.second = true;
						}
						else if (police2->pos_y > 0 && arg.map[police2->pos_y - 1][police2->pos_x].accessable()){
							police2->move(1, arg); alreadymoved.second = true;
						}
						else if (police2->pos_y < arg.max_y - 1 && arg.map[police2->pos_y + 1][police2->pos_x].accessable()){
							police2->move(3, arg); alreadymoved.second = true;
						}
						else if (police2->pos_x < arg.max_x - 1 && arg.map[police2->pos_y][police2->pos_x + 1].accessable()){
							police2->move(2, arg); alreadymoved.second = true;
						}
					}
				}
			}
		}
		catch (...){
			int tab[6] = { -3, -4, -5, 3, 4, 5 };
			for (int i = 0; i < 6; i++)

			{
				if (!alreadymoved.first && arg.map[thief->pos_y + tab[i]][thief->pos_x].accessable()){
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + tab[i])), this->police), arg);
					alreadymoved.first = true;
					break;
				}
				if (!alreadymoved.second && arg.map[thief->pos_y][thief->pos_x + tab[i]].accessable()){
					police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x + tab[i], thief->pos_y)), this->police2), arg);
					alreadymoved.first = true;
					break;
				}
			}
		}
	}
	else{
		thief->move(ManhatanDinstance(arg), arg);
	}

}

pair<vector<vector<pint>>, pint> Playable_Characters::A_star_algorithm(MAP& map, pair<int, int>& from, pair<int, int>& to){
	vector<pint> open_nodes;
	vector<pint> closed_nodes;
	vector<vector<pint>> come_from;
	vector<vector<int>> fscore; //heurestic
	vector<vector<int>> gscore; //cost of best know path


	open_nodes.push_back(pint(from.first, from.second)); // start node
	for (int i = 0; i < map.max_y; i++){
		for (int j = 0; j < map.max_x; j++){
			if (!map.map[i][j].accessable()){
				if (j == to.first && i == to.second);
				else
					closed_nodes.push_back(pint(j, i)); // impassable
			}
		}
	}
	for (int i = 0; i < map.max_y; i++){

		fscore.push_back(vector<int>());
		gscore.push_back(vector<int>());
		come_from.push_back(vector<pint>());
		for (int j = 0; j < map.max_x; j++){

			fscore[i].push_back(INT_MAX);
			gscore[i].push_back(INT_MAX);
			come_from[i].push_back(pint(-1, -1));
		}
	}
	fscore[from.second][from.first] = heuristic_cost_estimate(pint(from.first, from.second), pint(to.first, to.second));
	gscore[from.second][from.first] = 0;
	come_from[from.second][from.first] = pint(from.first, from.second);

	if (from.first == to.first && from.second == to.second) return pair<vector<vector<pint>>, pint>(come_from, *open_nodes.begin());
	while (!open_nodes.empty()){
		pint current = *open_nodes.begin();
		if (current.first == to.first && current.second == to.second){
			return pair<vector<vector<pint>>, pint>(come_from, current);
		}
		open_nodes.erase(open_nodes.begin());
		closed_nodes.push_back(current);

		vector<pint> neighbor = map.neighbor(pint(current.first, current.second));
		for (vector<pint>::iterator ite = neighbor.begin(); ite != neighbor.end(); ite++){

			if (find(closed_nodes.begin(), closed_nodes.end(), *ite) != closed_nodes.end()){
				continue;
			}
			int temp_g_score = gscore[ite->second][ite->first] + 1;
			int temp_f_score = heuristic_cost_estimate(pint(ite->first, ite->second), pint(to.first, to.second));
			if (find(open_nodes.begin(), open_nodes.end(), *ite) == open_nodes.end()){
				open_nodes.push_back(*ite);
			}
			else if (temp_g_score >= gscore[ite->second][ite->first]){
				continue;
			}
			come_from[ite->second][ite->first] = current;
			gscore[ite->second][ite->first] = temp_g_score;
			fscore[ite->second][ite->first] = temp_g_score + temp_f_score;
		}
	}
	throw exception();
}
int Playable_Characters::reconstrut_path_from_A_star_algorithm(pair<vector<vector<pint>>, pint> arg, Character* character){
	pint current = arg.second;
	pint last;
	while (true){
		cout << current.first << "." << current.second << " ";
		last = current;
		current = arg.first[current.second][current.first];
		if (current.second == character->pos_y && current.first == character->pos_x) {
			if (current.second == last.second && current.first == last.first) return 0;
			if (current.second == last.second - 1) return 3;
			if (current.first == last.first + 1) return 4;
			if (current.second == last.second + 1) return 1;
			if (current.first == last.first - 1) return 2;
		}
	}
}
int Playable_Characters::size_of_path_from_A_star_algorithm(pair<vector<vector<pint>>, pint> arg, pair<int, int> goal){
	pint current = arg.second;
	int size = 0;
	while (true){
		//cout << current.first << "." << current.second << " ";
		current = arg.first[current.second][current.first];
		size++;
		if (current.second == goal.second && current.first == goal.first) {
			//	cout << endl; 
			return size;
		}

	}

	return 0;
}
int Playable_Characters::ManhatanDinstance(MAP& map){
	if (ManhatanDinstance_points(map) > 10){
		if (thief->pos_y > 0 && map.map[thief->pos_y - 1][thief->pos_x].accessable()){
			if (thief->pos_y >= 13) return N;
		}
		if (thief->pos_y < map.max_y - 1 && map.map[thief->pos_y + 1][thief->pos_x].accessable()){
			if (thief->pos_y < 8) return S;
		}
		if (thief->pos_x < map.max_x - 1 && map.map[thief->pos_y][thief->pos_x + 1].accessable()){
			if (thief->pos_x < 10) return E;
		}
		if (thief->pos_x > 0 && map.map[thief->pos_y][thief->pos_x - 1].accessable()){
			if (thief->pos_x > 20) return W;
		}

	}

	pair<double, directions> bestscorewithdirection;
	double tempscore;
	if (thief->pos_y > 0 && map.map[thief->pos_y - 1][thief->pos_x].accessable()){
		thief->move(N, map);
		bestscorewithdirection.first = ManhatanDinstance_points(map);
		bestscorewithdirection.first *= ManhatanDinstance_characterfactor(map);
		bestscorewithdirection.second = N;
		thief->move(S, map);
	}
	if (thief->pos_y<map.max_y - 1 && map.map[thief->pos_y + 1][thief->pos_x].accessable()){
		thief->move(S, map);
		tempscore = ManhatanDinstance_points(map);
		tempscore *= ManhatanDinstance_characterfactor(map);
		if (tempscore>bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = S;
		}
		thief->move(N, map);
	}
	if (thief->pos_x<map.max_x - 1 && map.map[thief->pos_y][thief->pos_x + 1].accessable()){
		thief->move(E, map);
		tempscore = ManhatanDinstance_points(map);
		tempscore *= ManhatanDinstance_characterfactor(map);
		if (tempscore>bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = E;
		}
		thief->move(W, map);
	}
	if (thief->pos_x > 0 && map.map[thief->pos_y][thief->pos_x - 1].accessable()){
		thief->move(W, map);
		tempscore = ManhatanDinstance_points(map);
		tempscore *= ManhatanDinstance_characterfactor(map);
		if (tempscore > bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = W;
		}
		thief->move(E, map);
	}
	return bestscorewithdirection.second;
}
int Playable_Characters::ManhatanDinstance_points(MAP& map){
	int distance = 0;

	distance += size_of_path_from_A_star_algorithm(A_star_algorithm(map, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), pair<int, int>(police->pos_x, police->pos_y));
	distance += size_of_path_from_A_star_algorithm(A_star_algorithm(map, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), pair<int, int>(police2->pos_x, police2->pos_y));

	return distance;
}
double Playable_Characters::ManhatanDinstance_characterfactor(MAP& map){
	double x = thief->pos_x;
	double y = thief->pos_y;
	if (x > map.max_x / 2) x = (x - (x - map.max_x / 2) * 2);
	if (y > map.max_y / 2) x = (y - (y - map.max_y / 2) * 2);
	if (x == 0) x = 1;
	if (y == 0) y = 1;
	return (((2 * x - 1) / x) + ((2 * y - 1) / y));
}
CheckWinEnum Playable_Characters::checkwincondition(int turns, MAP& map){
	if (turns<=0){
		cout << "lose police";
		return winthief;
	}
	else
	{
		if (thief->pos_y > 0 && map.map[thief->pos_y - 1][thief->pos_x].accessable()){
			return Nothing;
		}
		if (thief->pos_y < map.max_y - 1 && map.map[thief->pos_y + 1][thief->pos_x].accessable()){
			return Nothing;
		}
		if (thief->pos_x < map.max_x - 1 && map.map[thief->pos_y][thief->pos_x + 1].accessable()){
			return Nothing;
		}
		if (thief->pos_x > 0 && map.map[thief->pos_y][thief->pos_x - 1].accessable()){
			return Nothing;
		}
		cout << "win police";
		return winpolice;
	}
	return Nothing;
}
