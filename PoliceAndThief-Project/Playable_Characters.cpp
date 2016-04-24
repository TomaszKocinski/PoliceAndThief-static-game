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
enum directions
{
	N = 1, E = 2, S = 3, W = 4
};
Playable_Characters::Playable_Characters(Graphics& graphics, MAP& game_board){
	thief = new Character(graphics, "images/thief.png", 0, 0, 40, 40, 26, 35, 0, 0, game_board);
	police = new Character(graphics, "images/police.png", 0, 0, 40, 40, 26, 35, 2, 2, game_board);
	police2 = new Character(graphics, "images/police2.png", 0, 0, 40, 40, 26, 35, 4, 4, game_board);
};
bool isNeightbor(Character* first, Character* second){
	if (first->pos_y == second->pos_y - 1 && first->pos_x == second->pos_x) {
		return true;
	}
	if (first->pos_x == second->pos_x + 1 && first->pos_y == second->pos_y) {
		return true;
	}
	if (first->pos_y == second->pos_y + 1 && first->pos_x == second->pos_x) {
		return true;
	}
	if (first->pos_x == second->pos_x - 1 && first->pos_y == second->pos_y) {
		return true;
	}
	return false;
}
int isNeighbor(pair<int, int> floatingcharacter, pair<int, int> centercharacter){
	if (centercharacter.second == floatingcharacter.second - 1 && centercharacter.first == floatingcharacter.first) {
		return 1;
	}
	if (centercharacter.first == floatingcharacter.first + 1 && centercharacter.second == floatingcharacter.second) {
		return 2;
	}
	if (centercharacter.second == floatingcharacter.second + 1 && centercharacter.first == floatingcharacter.first) {
		return 3;
	}
	if (centercharacter.first == floatingcharacter.first - 1 && centercharacter.second == floatingcharacter.second) {
		return 4;
	}
	return 0;
}
bool* Playable_Characters::GetAccessAbleNeighbors(MAP& map){
	bool* neighbors = new bool[4];
	if (thief->pos_y > 0 && map.map[thief->pos_y - 1][thief->pos_x].accessable() && map.cangetto(pair<int, int>(thief->pos_x, thief->pos_y-1))){
		neighbors[0] = true;
	}
	else neighbors[0] = false;
	if (thief->pos_y < map.max_y - 1 && map.map[thief->pos_y + 1][thief->pos_x].accessable() && map.cangetto(pair<int, int>(thief->pos_x, thief->pos_y+1))){
		neighbors[2] = true;
	}
	else neighbors[2] = false;
	if (thief->pos_x < map.max_x - 1 && map.map[thief->pos_y][thief->pos_x + 1].accessable() && map.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y ))){
		neighbors[1] = true;
	}
	else neighbors[1] = false;
	if (thief->pos_x > 0 && map.map[thief->pos_y][thief->pos_x - 1].accessable() && map.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y))){
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
		bool* neightbours = GetAccessAbleNeighbors(arg);
		if (neightbours[1] && neightbours[3]){// 1101 0111 0101
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police), arg);
			if (arg.map[thief->pos_y][thief->pos_x + 1].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
				police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police2), arg);
		}
		else if (neightbours[0] && neightbours[2]){// 1111 1110 1011 1010
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y-1)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police), arg);
			if (arg.map[thief->pos_y + 1][thief->pos_x].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y +1 )))
				police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police2), arg);
		}

		else if (neightbours[0] && neightbours[1]){//1100
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y -1)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police), arg);
			if (arg.map[thief->pos_y][thief->pos_x + 1].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
				police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police2), arg);
		}
		else if (neightbours[0] && neightbours[3]){//1001
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y -1)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police), arg);
			if (arg.map[thief->pos_y][thief->pos_x - 1].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
				police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police2), arg);
		}
		else if (neightbours[1] && neightbours[2]){//0110
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police), arg);
			if (arg.map[thief->pos_y + 1][thief->pos_x].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y+1)))
				police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police2), arg);
		}
		else if (neightbours[2] && neightbours[3]){//0011
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y +1)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police), arg);
			if (arg.map[thief->pos_y][thief->pos_x - 1].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
				police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police2), arg);
		}
		else if (neightbours[0]){
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x , thief->pos_y -1)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police), arg);
			if (arg.map[thief->pos_y - 1][thief->pos_x].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y -1)))
				police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y - 1)), this->police2), arg);
		}
		else if (neightbours[1]){
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police), arg);
			if (arg.map[thief->pos_y][thief->pos_x + 1].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x + 1, thief->pos_y)))
			police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x + 1, thief->pos_y)), this->police2), arg);
		}
		else if (neightbours[2]){
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y +1)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police), arg);
			if (arg.map[thief->pos_y + 1][thief->pos_x].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y +1)))
			police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y + 1)), this->police2), arg);
		}
		else if (neightbours[3]){
			if (!isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
				police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police), arg);
			if (arg.map[thief->pos_y][thief->pos_x - 1].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x - 1, thief->pos_y)))
			police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x - 1, thief->pos_y)), this->police2), arg);
		}
		else {
			cout << "all options exhauseted - didnt find possible spot for a star to travel, trying to launch a star regardres of that";
			if (arg.map[thief->pos_y][thief->pos_x].accessable() && !isNeightbor(police, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y)))
					police->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), this->police), arg);
			if (arg.map[thief->pos_y][thief->pos_x].accessable() && !isNeightbor(police2, thief) && arg.cangetto(pair<int, int>(thief->pos_x, thief->pos_y)))
			police2->move(reconstrut_path_from_A_star_algorithm(A_star_algorithm(arg, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), this->police2), arg);
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
		/*if (current.second == character->pos_y - 1 && current.first == character->pos_x) {
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
		}*/
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
		if (thief->pos_y > 0 && map.ispassable(pair<int, int>(thief->pos_x, thief->pos_y - 1))){
			if (thief->pos_y > map.max_y * 3 / 4) return N;
		}
		if (thief->pos_y<map.max_y - 1 && map.ispassable(pair<int, int>(thief->pos_x, thief->pos_y + 1))){
			if (thief->pos_y < map.max_y * 1 / 4) return S;
		}
		if (thief->pos_x<map.max_x - 1 && map.ispassable(pair<int, int>(thief->pos_x + 1, thief->pos_y))){
			if(thief->pos_x < map.max_x * 1 / 4) return E;
		}
		if (thief->pos_x > 0 && map.ispassable(pair<int, int>(thief->pos_x - 1, thief->pos_y))){
			if (thief->pos_y > map.max_y * 3 / 4) return W;
		}

	}
	
	pair<double, directions> bestscorewithdirection;
	double tempscore;
	if (thief->pos_y > 0 && map.ispassable(pair<int, int>(thief->pos_x, thief->pos_y - 1))){
		thief->move(N, map);
		bestscorewithdirection.first = ManhatanDinstance_points(map);
		bestscorewithdirection.first *= ManhatanDinstance_characterfactor(map);
		bestscorewithdirection.second = N;
		thief->move(S, map);
	}
	if (thief->pos_y<map.max_y - 1 && map.ispassable(pair<int, int>(thief->pos_x, thief->pos_y + 1))){
		thief->move(S, map);
		tempscore = ManhatanDinstance_points(map);
		tempscore *= ManhatanDinstance_characterfactor(map);
		if (tempscore>bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = S;
		}
		thief->move(N, map);
	}
	if (thief->pos_x<map.max_x - 1 && map.ispassable(pair<int, int>(thief->pos_x + 1, thief->pos_y))){
		thief->move(E, map);
		tempscore = ManhatanDinstance_points(map);
		tempscore *= ManhatanDinstance_characterfactor(map);
		if (tempscore>bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = E;
		}
		thief->move(W, map);
	}
	if (thief->pos_x > 0 && map.ispassable(pair<int, int>(thief->pos_x - 1, thief->pos_y))){
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

	//distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(0, 0));
	//distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(map.max_x - 1, map.max_y - 1));
	//distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(map.max_x - 1, 0));
	//distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(0, map.max_y - 1));
	//distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(police->pos_x, police->pos_y));
	//distance += heuristic_cost_estimate(pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(police2->pos_x, police2->pos_y));


	//distance += size_of_path_from_A_star_algorithm(A_star_algorithm(map, pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(0, 0)), pair<int, int>(thief->pos_x, thief->pos_y));
	//distance += size_of_path_from_A_star_algorithm(A_star_algorithm(map, pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(map.max_x - 1, map.max_y - 1)), pair<int, int>(thief->pos_x, thief->pos_y));
	//distance += size_of_path_from_A_star_algorithm(A_star_algorithm(map, pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(map.max_x - 1, 0)), pair<int, int>(thief->pos_x, thief->pos_y));
	//distance += size_of_path_from_A_star_algorithm(A_star_algorithm(map, pair<int, int>(thief->pos_x, thief->pos_y), pair<int, int>(0, map.max_y - 1)), pair<int, int>(thief->pos_x, thief->pos_y));

	distance += size_of_path_from_A_star_algorithm(A_star_algorithm(map, pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), pair<int, int>(police->pos_x, police->pos_y));
	distance += size_of_path_from_A_star_algorithm(A_star_algorithm(map, pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), pair<int, int>(police2->pos_x, police2->pos_y));

	return distance;
}
double Playable_Characters::ManhatanDinstance_characterfactor(MAP& map){
	double x = thief->pos_x;
	double y = thief->pos_y;
	if (x > map.max_x / 2) x = (x - (x-map.max_x / 2)*2);
	if (y > map.max_y / 2) x = (y - (y - map.max_y / 2) * 2);
	if (x == 0) x = 1;
	if (y == 0) y = 1;
	return (((2 * x - 1) / x) + ((2 * y - 1) / y) );
}