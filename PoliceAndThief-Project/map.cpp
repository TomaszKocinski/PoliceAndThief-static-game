#pragma once
#include "map.h"
#include "Playable_Characters.h"
void MAP::switchFree(pair<int,int>& arg){
	if(map[arg.second][arg.first].free==true){
		map[arg.second][arg.first].free=false;
	}
	else{
		map[arg.second][arg.first].free=true;
	}
}
MAP::MAP() :mov_x(88), mov_y(mov_x), max_x(29), max_y(20){ 

	for (int i = 1; i<max_y; i = i + 2){
		for (int j = 1; j<max_x; j = j + 2){
			map[i][j].passable = false;
		}
	}
	map[4][15].passable = false;
	map[6][5].passable = false;
	map[6][9].passable = false;
	map[6][21].passable = false;
	map[8][11].passable = false;
	map[10][15].passable = false;
	map[12][21].passable = false;
	map[12][5].passable = false;
	map[14][13].passable = false;
	map[16][5].passable = false;
	map[16][23].passable = false;
	map[18][15].passable = false;

	map[6][11].passable = false;
	map[5][10].passable = false;
	map[8][11].passable = false;

	map[9][14].passable = false;
	map[5][16].passable = false;
	map[5][22].passable = false;

	map[7][22].passable = false;
	map[17][22].passable = false;
	map[16][7].passable = false;

	map[17][8].passable = false;
	map[17][18].passable = false;
	map[9][24].passable = false;

	map[10][9].passable = false;
}
vector<pair<int, int>> MAP::neighbor(std::pair<int, int>& arg){
	vector<pair<int, int>> vec;
	if (arg.second>0 && map[arg.second - 1][arg.first].passable){
		vec.push_back(pair<int, int>(arg.first, arg.second - 1));
	}
	if (arg.second<max_y - 1 && map[arg.second + 1][arg.first].passable){
		vec.push_back(pair<int, int>(arg.first, arg.second + 1));
	}
	if (arg.first<max_x - 1 && map[arg.second][arg.first + 1].passable){
		vec.push_back(pair<int, int>(arg.first + 1, arg.second));
	}
	if (arg.first>0 && map[arg.second][arg.first - 1].passable){
		vec.push_back(pair<int, int>(arg.first - 1, arg.second));
	}
	return vec;
}
MAP& MAP::operator=(MAP& arg){
	 map = map;
	 return *this;
}
bool MAP::ispassable(std::pair<int, int>& arg){
	if (map[arg.second][arg.first].passable) return true;
	return false;
}
bool MAP::cangetto(std::pair<int, int>& to){
	if (to.second > 0 && map[to.second - 1][to.first].passable && map[to.second - 1][to.first].free){
		return cangettoforbay(pair<int, int>(to.first,to.second - 1 ), 1);
	}
	if (to.first > 0 && map[to.second][to.first - 1].passable && map[to.second][to.first - 1].free) {
		return cangettoforbay(pair<int, int>(to.first - 1,to.second), 4);
	}
	if (to.second < max_y - 1 && map[to.second + 1][to.first].passable && map[to.second + 1][to.first].free) {
		return cangettoforbay(pair<int, int>(to.first,to.second + 1), 3);
	}
	if (to.first < max_x - 1 && map[to.second][to.first + 1].passable && map[to.second][to.first + 1].free) {
		return cangettoforbay(pair<int, int>(to.first + 1,to.second ), 2);
	}
	return false;
}
bool MAP::cangettoforbay(std::pair<int, int>& to, int direction){
	if (direction != 3){
		if (to.second > 0 && map[to.second - 1][to.first].passable 
			&& map[to.second - 1][to.first].free
			)	return true;
	}
	if (direction != 2){
		if (to.first > 0 && map[to.second][to.first - 1].passable 
			&& map[to.second][to.first - 1].free
			) return true;
	}
	if (direction != 1){
		if (to.second < max_y - 1 && map[to.second + 1][to.first].passable
			&& map[to.second + 1][to.first].free
			) return true;
	}
	if (direction != 4){
		if (to.first < max_x - 1 && map[to.second][to.first + 1].passable 
			&& map[to.second][to.first + 1].free
			) return true;
	}
	return false;

}