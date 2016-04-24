#ifndef MAP_H
#define MAP_H
#include<array>
#include<vector>
using namespace std;
class Playable_Characters;
class PassableandFree{
	bool passable;
	bool free;
	friend class MAP;
public:
	PassableandFree(){
		passable=true;
		free=true;
	}
	bool accessable(){
		if (!passable) return false;
		if (!free) return false;
		return true;
		/*if (passable && free) {
			return true;
		}
		return false;*/

	} 
};
class MAP{
public: 
	const int max_x;
	const int max_y;
	int mov_x;
	int mov_y;
	std::array<std::array<PassableandFree,29>,20> map;
	MAP();
	vector<pair<int, int>> neighbor(std::pair<int, int>& arg);
	void switchFree(pair<int,int>&);
	MAP& operator=(MAP&);
	bool ispassable(std::pair<int, int>& arg);
	bool cangetto(std::pair<int, int>&);
	bool cangettoforbay(std::pair<int, int>& arg, int direction);
};
#endif