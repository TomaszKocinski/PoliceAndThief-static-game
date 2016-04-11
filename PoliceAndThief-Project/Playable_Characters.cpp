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
typedef pair<int, pair<int, int>> dpint;
enum directions
{
	N = 1, E = 2, S = 3, W = 4
};
Playable_Characters::Playable_Characters(Graphics& graphics, MAP& game_board){
	thief = new Character(graphics, "images/thief.png", 0, 0, 40, 40, 26, 35, 0, 0, game_board);
	police = new Character(graphics, "images/police.png", 0, 0, 40, 40, 26, 35, 2, 2, game_board);
	police2 = new Character(graphics, "images/police2.png", 0, 0, 40, 40, 26, 35, 4, 4, game_board);
};
bool pint_compare(pair<int, int> arg_f, pair<int, int> arg_s){
	if (arg_f.first == arg_s.first && arg_f.second == arg_s.second) return true;
	return false;
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
		police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, police, thief), this->police), arg);
		police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, police2, thief), this->police2), arg);
	}
	else{
		thief->move(ManhatanDinstance(arg), arg);
	}

}
pair<vector<vector<pint>>, pint> Playable_Characters::A_star_algorithm(MAP& map, Character* from, Character* to){
	vector<pint> open_nodes;
	vector<pint> closed_nodes;
	vector<vector<pint>> come_from;
	vector<vector<int>> fscore; //heurestic
	vector<vector<int>> gscore; //cost of best know path

	int start_x = from->pos_x, start_y = from->pos_y;
	open_nodes.push_back(pint(start_x, start_y)); // start node
	for (int i = 0; i < map.max_y; i++){
		for (int j = 0; j < map.max_x; j++){
			if (!map.map[i][j].accessable()){
				if (j == to->pos_x && i == to->pos_y);
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
	fscore[start_y][start_x] = heuristic_cost_estimate(pint(start_x, start_y), pint(to->pos_x, to->pos_y));
	gscore[start_y][start_x] = 0;
	come_from[start_y][start_x] = pint(start_x, start_y);


	while (!open_nodes.empty()){
		pint current = *open_nodes.begin();
		if (current.first == to->pos_x && current.second == to->pos_y){
			return pair<vector<vector<pint>>, pint>(come_from,current);
		}
		open_nodes.erase(open_nodes.begin());
		closed_nodes.push_back(current);

		vector<pint> neighbor = map.neighbor(pint(current.first, current.second));
		for (vector<pint>::iterator ite = neighbor.begin(); ite != neighbor.end(); ite++){
			if (find(closed_nodes.begin(), closed_nodes.end(), *ite) != closed_nodes.end()){
				continue;
			}
			int temp_g_score = gscore[ite->second][ite->first] + 1;
			int temp_f_score = heuristic_cost_estimate(pint(ite->first, ite->second), pint(to->pos_x, to->pos_y));
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
	while (true){
		cout << current.first << "." << current.second << " ";
		current = arg.first[current.second][current.first];
		if (current.second == character->pos_y - 1 && current.first == character->pos_x) {
			cout << endl; return 1;
		}
		if (current.first == character->pos_x + 1 && current.second == character->pos_y) {
			cout << endl; return 2;
		}
		if (current.second == character->pos_y + 1 && current.first == character->pos_x) {
			cout << endl; return 3;
		}
		if (current.first == character->pos_x - 1 && current.second == character->pos_y) {
			cout << endl; return 4;
		}

	}
	cout << endl;
	return 0;
}
int Playable_Characters::ManhatanDinstance(MAP& map){
	pair<int, directions> bestscorewithdirection;
	int tempscore;
	if (thief->pos_y > 0 && map.ispassable(pair<int, int>(thief->pos_x, thief->pos_y - 1))){
		thief->pos_y -= 1;
		bestscorewithdirection.first = ManhatanDinstance_points(map);
		bestscorewithdirection.second = N;
		thief->pos_y += 1;
	}
	if (thief->pos_y<map.max_y - 1 && map.ispassable(pair<int, int>(thief->pos_x, thief->pos_y + 1))){
		thief->pos_y += 1;
		tempscore = ManhatanDinstance_points(map);
		if (tempscore>bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = S;
		}
		thief->pos_y -= 1;
	}
	if (thief->pos_x<map.max_x - 1 && map.ispassable(pair<int, int>(thief->pos_x + 1, thief->pos_y))){
		thief->pos_x += 1;
		tempscore = ManhatanDinstance_points(map);
		if (tempscore>bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = E;
		}
		thief->pos_x -= 1;
	}
	if (thief->pos_x > 0 && map.ispassable(pair<int, int>(thief->pos_x - 1, thief->pos_y))){
		thief->pos_x -= 1;
		tempscore = ManhatanDinstance_points(map);
		if (tempscore > bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = W;
		}
		thief->pos_x += 1;
	}
	return bestscorewithdirection.second;
}
int Playable_Characters::ManhatanDinstance_points(MAP& map){
	int distance = 0;
	distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(0, 0));
	distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(map.max_x - 1, map.max_y - 1));
	distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(map.max_x - 1, 0));
	distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(0, map.max_y - 1));
	//distance -= heuristic_cost_estimate(pair<int, int>(thief->_x, thief->_y), pair<int, int>(police->_x, police->_y));
	//distance -= heuristic_cost_estimate(pair<int, int>(thief->_x, thiefs->_y), pair<int, int>(police2->_x, police2->_y));

	distance -= A_star_algorithm(map, police, thief).first.size()*2;
	distance -= A_star_algorithm(map, police2, thief).first.size()*2;
	return distance;
}