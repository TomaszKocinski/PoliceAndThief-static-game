#pragma once
#include "Sprite.h"
#include "Graphics.h"
#include "map.h"
#include "Playable_Characters.h"
#include <random>
#include <iostream>
#include <map>

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
Playable_Characters::Playable_Characters(Graphics& graphics, MAP* game_board){
	map = game_board;
	thief = new Character(graphics, "images/thief.png", 0, 0, 40, 40, 26, 35, 0, 0, *game_board);
	police = new Character(graphics, "images/police.png", 0, 0, 40, 40, 26, 35, 2, 2, *game_board);
	police2 = new Character(graphics, "images/police2.png", 0, 0, 40, 40, 26, 35, 4, 4, *game_board);
};

int heuristic_cost_estimate(pair<int, int> start, pair<int, int> goal){

	int dest = 0,
		temp_x = goal.first,
		temp_y = goal.second;
	std::pair<int, int> dist = std::make_pair<int, int>(0, 0);
	while (start.first > temp_x){
		dest++;
		temp_x++;
	}
	while (start.first < temp_x){
		dest++;
		temp_x--;
	}
	while (start.second > temp_y){
		dest++;
		temp_y++;
	}
	while (start.second < temp_y){
		dest++;
		temp_y--;
	}

	return dest;
}
bool Playable_Characters::Can_character_move(Character* character){
	if (character->pos_y > 0 && map->map[character->pos_y - 1][character->pos_x].accessable()){
		return true;
	}
	else if (character->pos_x > 0 && map->map[character->pos_y][character->pos_x - 1].accessable()){
		return true;
	}
	else if (character->pos_y < map->max_y - 1 && map->map[character->pos_y + 1][character->pos_x].accessable()){
		return true;
	}
	else if (character->pos_x < map->max_x - 1 && map->map[character->pos_y][character->pos_x + 1].accessable()){
		return true;
	}
	return false;
}
void Playable_Characters::Automatic_move(bool police_turn){

	if (police_turn){
		police->move(Automatic_move_police(police),*map);
		police2->move(Automatic_move_police(police2), *map);
	}
	else{
		thief->move(Automatic_move_thief(), *map);
	}

}
int Playable_Characters::Automatic_move_police(Character* character){
	if (!Can_character_move(character)) return false;
	if (Are_police_neighbors_of_thief(character)){	
		return Automatic_move_police_random(character);
	}
	try{ 
		return reconstrut_path_from_A_star_algorithm(A_star_algorithm(pair<int, int>(character->pos_x, character->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), character);
	}
	catch (...){
		pair<int, int> target = Automatic_move_police_set_target(character);

		try{
			return reconstrut_path_from_A_star_algorithm(A_star_algorithm(pair<int, int>(character->pos_x, character->pos_y), target), character);
		}
		catch (...){
			return Automatic_move_police_random(character);
		}
	}
	
}
pair<int, int> Playable_Characters::Automatic_move_police_set_target(Character * character){
	pair<int, int> target;


	if (thief->pos_x < map->max_x / 2 && thief->pos_x < map->max_y / 2){//1
		if (character == police)
			target = pair<int, int>(thief->pos_x + 1, thief->pos_y);
		else if (character == police2)
			target = pair<int, int>(thief->pos_x, thief->pos_y - 1);
		else throw exception();
	}
	else if (thief->pos_x < map->max_x / 2 && thief->pos_x >= map->max_y / 2){//3
		if (character == police)
			target = pair<int, int>(thief->pos_x + 1, thief->pos_y);
		else if (character == police2)
			target = pair<int, int>(thief->pos_x, thief->pos_y + 1);
		else throw exception();
	}
	else if (thief->pos_x >= map->max_x / 2 && thief->pos_x < map->max_y / 2){//2
		if (character == police)
			target = pair<int, int>(thief->pos_x - 1, thief->pos_y);
		else if (character == police2)
			target = pair<int, int>(thief->pos_x, thief->pos_y + 1);
		else throw exception();
	}
	else if (thief->pos_x >= map->max_x / 2 && thief->pos_x >= map->max_y / 2){//4
		if (character == police)
			target = pair<int, int>(thief->pos_x - 1, thief->pos_y);
		else if (character == police2)
			target = pair<int, int>(thief->pos_x, thief->pos_y - 1);
		else throw exception();
	}

	for (int i = 0; !map->map[target.second][target.first].accessable();i++){
		
		if (i == 0 && target.second > 0 ){
			target.second -= 1;
			continue;
		}
		if (i == 1 && target.first < map->max_x - 1){
			target.second += 1;
			target.first += 1;
			continue;
		}
		if (i == 2 && target.second < map->max_y - 1 ){
			target.first -= 1;
			target.second += 1;
			continue;
		}
		if (i == 3 && target.first > 0 ){
			target.second -= 1;
			target.first -= 1;
			continue;
		}
		
		i = 0;
	}
	return target;
}
int Playable_Characters::Automatic_move_police_random(Character* police){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> d(1, 4);
	if (!Can_character_move(police)){
		return false;
	}
	int direction;
	while (true){
		direction = d(gen);

		if (direction == N &&  police->pos_y > 0 && map->map[police->pos_y - 1][police->pos_x].accessable()){
			return N;
		}
		else if (direction == E && police->pos_x < map->max_x - 1 && map->map[police->pos_y][police->pos_x + 1].accessable()){
			return E;
		}
		else if (direction == S && police->pos_y < map->max_y - 1 && map->map[police->pos_y + 1][police->pos_x].accessable()){
			return S;
		}
		else if (direction == W && police->pos_x > 0 && map->map[police->pos_y][police->pos_x - 1].accessable()){
			return W;
		}	
	}


}
bool Playable_Characters::Are_police_neighbors_of_thief(Character* arg){
	if (arg->pos_y -1 == thief->pos_y && arg->pos_x == thief->pos_x){
		return true;
	}
	else if (arg->pos_y +1 == thief->pos_y && arg->pos_x == thief->pos_x){
		return true;
	}
	else if (arg->pos_y == thief->pos_y && arg->pos_x - 1 == thief->pos_x){
		return true;
	}
	else if (arg->pos_y == thief->pos_y && arg->pos_x + 1 == thief->pos_x){
		return true;
	}
	return false;

}
pair<vector<vector<pint>>, pint> Playable_Characters::A_star_algorithm(pair<int, int>& from, pair<int, int>& to){
	vector<pint> open_nodes;
	vector<pint> closed_nodes;
	vector<vector<pint>> come_from;
	vector<vector<int>> fscore; //heurestic
	vector<vector<int>> gscore; //cost of best know path


	open_nodes.push_back(pint(from.first, from.second)); // start node
	for (int i = 0; i < map->max_y; i++){
		for (int j = 0; j < map->max_x; j++){
			if (!(map->map[i][j].accessable())){
				if (j == to.first && i == to.second);
				else
					closed_nodes.push_back(pint(j, i)); // impassable
			}
		}
	}
	for (int i = 0; i < map->max_y; i++){

		fscore.push_back(vector<int>());
		gscore.push_back(vector<int>());
		come_from.push_back(vector<pint>());
		for (int j = 0; j < map->max_x; j++){

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

		pint current; 
		vector<pint>::iterator smallest = open_nodes.begin();
		for (vector<pint>::iterator ite = open_nodes.begin(); ite != open_nodes.end(); ite++){
			if (fscore[ite->second][ite->first] < fscore[smallest->second][smallest->first])
				smallest = ite;
		}
		current = *smallest;
		if (current.first == to.first && current.second == to.second){
			return pair<vector<vector<pint>>, pint>(come_from, current);
		}
		open_nodes.erase(open_nodes.begin());
		closed_nodes.push_back(current);

		vector<pint> neighbor = map->neighbor(pint(current.first, current.second));
		for (vector<pint>::iterator ite = neighbor.begin(); ite != neighbor.end(); ite++){

			if (find(closed_nodes.begin(), closed_nodes.end(), *ite) != closed_nodes.end()){
				continue;
			}
			int temp_g_score;
			if (ite->second == police->pos_y - 1 && ite->first == police->pos_x || ite->second == police->pos_y && ite->first == police->pos_x + 1 || ite->second == police->pos_y + 1 && ite->first == police->pos_x || ite->second == police->pos_y && ite->first == police->pos_x - 1 || ite->second == police2->pos_y - 1 && ite->first == police2->pos_x || ite->second == police2->pos_y && ite->first == police2->pos_x + 1 || ite->second == police2->pos_y + 1 && ite->first == police2->pos_x || ite->second == police2->pos_y && ite->first == police2->pos_x - 1)
				temp_g_score = gscore[ite->second][ite->first] + 2;
			else 
				temp_g_score = gscore[ite->second][ite->first] + 1;
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
		//cout << current.first << "." << current.second << " ";
		last = current;
		current = arg.first[current.second][current.first];
		if (current.second == character->pos_y && current.first == character->pos_x) {
			if (current.second == last.second && current.first == last.first) return 0;
			if (current.second == last.second - 1) return S;
			if (current.first == last.first + 1) return W;
			if (current.second == last.second + 1) return N;
			if (current.first == last.first - 1) return E;
		}
	}
}
int Playable_Characters::size_of_path_from_A_star_algorithm(pair<vector<vector<pint>>, pint> arg, pair<int, int> goal){
	pint current = arg.second;
	int size = 0;
	while (true){
		current = arg.first[current.second][current.first];
		size++;
		if (current.second == goal.second && current.first == goal.first) {
			return size;
		}
	}

	return 0;
}
int Playable_Characters::Automatic_move_thief(){
	if (Automatic_move_thief_points() > 10){
		if (thief->pos_y > 0 && map->map[thief->pos_y - 1][thief->pos_x].accessable()){
			if (thief->pos_y >= 13) return N;
		}
		if (thief->pos_y < map->max_y - 1 && map->map[thief->pos_y + 1][thief->pos_x].accessable()){
			if (thief->pos_y < 8) return S;
		}
		if (thief->pos_x < map->max_x - 1 && map->map[thief->pos_y][thief->pos_x + 1].accessable()){
			if (thief->pos_x < 10) return E;
		}
		if (thief->pos_x > 0 && map->map[thief->pos_y][thief->pos_x - 1].accessable()){
			if (thief->pos_x > 20) return W;
		}

	}

	pair<double, directions> bestscorewithdirection;
	double tempscore;
	if (thief->pos_y > 0 && map->map[thief->pos_y - 1][thief->pos_x].accessable()){
		thief->move(N, *map);
		bestscorewithdirection.first = Automatic_move_thief_points();
		bestscorewithdirection.first *= Automatic_move_thief_characterfactor();
		bestscorewithdirection.second = N;
		thief->move(S, *map);
	}
	if (thief->pos_y<map->max_y - 1 && map->map[thief->pos_y + 1][thief->pos_x].accessable()){
		thief->move(S, *map);
		tempscore = Automatic_move_thief_points();
		tempscore *= Automatic_move_thief_characterfactor();
		if (tempscore>bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = S;
		}
		thief->move(N, *map);
	}
	if (thief->pos_x<map->max_x - 1 && map->map[thief->pos_y][thief->pos_x + 1].accessable()){
		thief->move(E, *map);
		tempscore = Automatic_move_thief_points();
		tempscore *= Automatic_move_thief_characterfactor();
		if (tempscore>bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = E;
		}
		thief->move(W, *map);
	}
	if (thief->pos_x > 0 && map->map[thief->pos_y][thief->pos_x - 1].accessable()){
		thief->move(W, *map);
		tempscore = Automatic_move_thief_points();
		tempscore *= Automatic_move_thief_characterfactor();
		if (tempscore > bestscorewithdirection.first){
			bestscorewithdirection.first = tempscore;
			bestscorewithdirection.second = W;
		}
		thief->move(E,*map);
	}
	return bestscorewithdirection.second;
}
int Playable_Characters::Automatic_move_thief_points(){
	int distance = 0;
	try{
		distance += size_of_path_from_A_star_algorithm(A_star_algorithm(pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), pair<int, int>(police->pos_x, police->pos_y));
	}
	catch (...){
		distance += heuristic_cost_estimate(pair<int, int>(police->pos_x, police->pos_y), pair<int, int>(thief->pos_x, thief->pos_y));
	}
	try{
	distance += size_of_path_from_A_star_algorithm(A_star_algorithm(pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y)), pair<int, int>(police2->pos_x, police2->pos_y));
	}
	catch (...){
		distance += heuristic_cost_estimate(pair<int, int>(police2->pos_x, police2->pos_y), pair<int, int>(thief->pos_x, thief->pos_y));
	}
	return distance;
}
double Playable_Characters::Automatic_move_thief_characterfactor(){
	double x = thief->pos_x;
	double y = thief->pos_y;
	if (x > map->max_x / 2) x = (x - (x - map->max_x / 2) * 2);
	if (y > map->max_y / 2) x = (y - (y - map->max_y / 2) * 2);
	if (x == 0) x = 1;
	if (y == 0) y = 1;
	return (((2 * x - 1) / x) + ((2 * y - 1) / y));
}
CheckWinEnum Playable_Characters::checkwincondition(int turns){
	if (turns<=0){
		cout << "lose police";
		return winthief;
	}
	else
	{
		if (thief->pos_y > 0 && map->map[thief->pos_y - 1][thief->pos_x].accessable()){
			return Nothing;
		}
		if (thief->pos_y < map->max_y - 1 && map->map[thief->pos_y + 1][thief->pos_x].accessable()){
			return Nothing;
		}
		if (thief->pos_x < map->max_x - 1 && map->map[thief->pos_y][thief->pos_x + 1].accessable()){
			return Nothing;
		}
		if (thief->pos_x > 0 && map->map[thief->pos_y][thief->pos_x - 1].accessable()){
			return Nothing;
		}
		cout << "win police";
		return winpolice;
	}
	return Nothing;
}
Playable_Characters Playable_Characters::operator=(Playable_Characters& other){
	map = other.map;
	thief= other.thief;
	police = other.police;
	police2 = other.police2;
	return *this;
}
