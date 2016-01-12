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
typedef pair<int,int> pint;
//class pair_of_int{
//public:
//	int first;
//	int second;
//	pair_of_int(int arg_f,int arg_s){
//		first=arg_f;
//		second=arg_s;
//	}
//	bool operator==(pair_of_int arg_f){
//		if(arg_f.first==first && arg_f.second==second) return true;
//		return false;
//	}
//	bool operator==(pair_of_int arg_f){
//		if(arg_f.first==first && arg_f.second==second) return true;
//		return false;
//	}
//};
typedef pair<int,pair<int,int>> dpint;
bool pint_compare(pair<int,int> arg_f, pair<int,int> arg_s){
	if(arg_f.first==arg_s.first && arg_f.second==arg_s.second) return true;
	return false;
}
int heuristic_cost_estimate(pair<int,int> start, pair<int,int> goal){
	if(start.first==goal.first && start.second==goal.second){
		std::cout << "positon of thief and police is indentical";
		return -1;
	}
	if(start.first==goal.first && start.second==goal.second) {
		std::cout << "positon of thief and police2 is indentical";
		return -1;
	}
	
	int dest=0,
		temp_x=goal.first,
		temp_y=goal.second;
	std::pair<int,int> dist=std::make_pair<int,int>(0,0);
	while(start.first>temp_x){
		dest++;
		temp_x++;
	}
	while(start.first<temp_x){
		dest++;
		temp_x--;
	}
	while(start.second>temp_y){
		dest++;
		temp_y++;
	}
	while(start.second<temp_y){
		dest++;
		temp_y--;
	}

	return dest;
}
Playable_Characters::Playable_Characters(Graphics graphics){
	thief=NULL;
	police=NULL;
	police2=NULL;
	thief	= new Character(graphics, "images/thief.png",0,0, 40, 40,26,35,0,0);
	police	= new Character(graphics, "images/police.png",0,0, 40, 40,202,208,2,2);
	police2	= new Character(graphics, "images/police2.png",0,0, 40, 40,386,400,4,4);
}
std::pair<int,int> Playable_Characters::distance() const {
	if(thief->pos_x==police->pos_x && thief->pos_y==police->pos_y){
		std::cout << "positon of thief and police is indentical";
		return std::pair<int,int>(-1,-1);
	}
	if(thief->pos_x==police2->pos_x && thief->pos_y==police2->pos_y) {
		std::cout << "positon of thief and police2 is indentical";
		return std::pair<int,int>(-1,-1);
	}
	
	int temp_dest=0,
		temp_x=police->pos_x,
		temp_y=police->pos_y;
	std::pair<int,int> dist=std::make_pair<int,int>(0,0);
	while(thief->pos_x>temp_x){
		temp_dest++;
		temp_x++;
	}
	while(thief->pos_x<temp_x){
		temp_dest++;
		temp_x--;
	}
	while(thief->pos_y>temp_y){
		temp_dest++;
		temp_y++;
	}
	while(thief->pos_y<temp_y){
		temp_dest++;
		temp_y--;
	}

	dist.first=temp_dest;
	std::cout<<dist.first;
	temp_dest=0;
	temp_x=police2->pos_x;
	temp_y=police2->pos_y;

	while(thief->pos_x>temp_x){
		temp_dest++;
		temp_x++;
	}
	while(thief->pos_x<temp_x){
		temp_dest++;
		temp_x--;
	}
	while(thief->pos_y>temp_y){
		temp_dest++;
		temp_y++;
	}
	while(thief->pos_y<temp_y){
		temp_dest++;
		temp_y--;
	}
	dist.second=temp_dest;
	std::cout<<dist.second<< ' ';
	return dist;
}
void Playable_Characters::Automatic_move(MAP arg){
	A_star_algorithm(arg,thief,police);
}
int Playable_Characters::A_star_algorithm(MAP map, Character* from, Character* to){
	vector<pint> open_nodes;
	vector<pint> closed_nodes;
	map<pint,pint> come_from;
	vector<vector<int>> fscore; //heurestic
	vector<vector<int>> gscore; //cost of best know path
	
	{
		int start_x=from->pos_x, start_y=from->pos_y;
		open_nodes.push_back(pint(start_x,start_y)); // start node

		for (int i=0;i<map.max_y;i++){
			for (int j=0;j<map.max_x;j++){
				if(map.map[i][j].impassable){
					closed_nodes.push_back(pint(i,j)); // impassable
				}
			}
		}

		for(int i=0;i<map.max_y;i++){
			fscore.push_back(vector<int>());
			gscore.push_back(vector<int>());
			for(int j=0;j<map.max_x;j++){
				fscore[i][j]=INT_MAX;
				gscore[i][j]=INT_MAX;
			}
		}
		fscore[start_x][start_y]=heuristic_cost_estimate(pint(start_x,start_y),pint(to->pos_x,to->pos_y));
		gscore[start_x][start_y]=0;
	}

	while(!open_nodes.empty()){
		pint current=*open_nodes.begin();
		if(current.first==to->pos_x && current.second==to->pos_y){
			return 7;
		}
		open_nodes.erase(open_nodes.begin());
		closed_nodes.push_back(current);
		
		vector<pint> neighbor=map.neighbor(pint(from->pos_x,from->pos_y));
		for(vector<pint>::iterator ite=neighbor.begin();ite!=neighbor.end();ite++){
			if(find(closed_nodes.begin(),closed_nodes.end(),*ite)!=closed_nodes.end()){
				continue;
			}
			int temp_g_score=gscore[current.first][current.second]+1;
			int temp_f_score=heuristic_cost_estimate(pint(ite->first,ite->second),pint(to->pos_x,to->pos_y));
			if(find(open_nodes.begin(),open_nodes.end(),*ite)==open_nodes.end()){
				open_nodes.push_back(*ite);
			}
			else if(temp_g_score >= gscore[ite->first][ite->second]){
				continue;
			}
			//come_from[*ite]=current;
			gscore[ite->first][ite->second]=temp_g_score;
			fscore[ite->first][ite->second]=temp_g_score +temp_f_score;
		}
	}
	throw exception();
}

