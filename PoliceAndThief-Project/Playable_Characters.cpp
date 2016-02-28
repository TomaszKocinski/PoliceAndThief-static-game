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
typedef pair<int,pair<int,int>> dpint;
bool pint_compare(pair<int,int> arg_f, pair<int,int> arg_s){
	if(arg_f.first==arg_s.first && arg_f.second==arg_s.second) return true;
	return false;
}
int heuristic_cost_estimate(pair<int,int> start, pair<int,int> goal){
	/*if(start.first==goal.first && start.second==goal.second){
		std::cout << "positon of thief and police is indentical";
		return -1;
	}
	if(start.first==goal.first && start.second==goal.second) {
		std::cout << "positon of thief and police2 is indentical";
		return -1;
	}*/
	
	int dest=0,
		temp_x=goal.first,
		temp_y=goal.second;
	std::pair<int,int> dist=std::make_pair<int,int>(0,0);
	while(start.second>temp_x){
		dest++;
		temp_x++;
	}
	while(start.second<temp_x){
		dest++;
		temp_x--;
	}
	while(start.first>temp_y){
		dest++;
		temp_y++;
	}
	while(start.first<temp_y){
		dest++;
		temp_y--;
	}

	return dest;
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
void Playable_Characters::Automatic_move(MAP arg,bool police_turn){
	if(police_turn)
		police->move(A_star_algorithm(arg,police,thief),arg);
	police2->move(A_star_algorithm(arg,police2,thief),arg);

}
int Playable_Characters::A_star_algorithm(MAP map, Character* from, Character* to){
	vector<pint> open_nodes;
	vector<pint> closed_nodes;
	vector<vector<pint>> come_from;
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
			come_from.push_back(vector<pint>());
			for(int j=0;j<map.max_x;j++){

				fscore[i].push_back(INT_MAX);
				gscore[i].push_back(INT_MAX);
				come_from[i].push_back(pint(-1,-1));
			}
		}
		fscore[start_y][start_x]=heuristic_cost_estimate(pint(start_x,start_y),pint(to->pos_x,to->pos_y));
		gscore[start_y][start_x]=0;\
		come_from[start_y][start_x]=pint(start_x,start_y);
	}

	while(!open_nodes.empty()){
		pint current=*open_nodes.begin();
		//if(map.map[current.second][current.first].impassable) cout<<"ERROR IMPASABLE 2"<<endl;
		if(current.first==to->pos_x && current.second==to->pos_y){
			/*for each(vector<pint> upperele in come_from){
				for each(pint ele in upperele){
					if(ele.first==-1 && ele.second==-1) continue;
					if(map.map[ele.second][ele.first].impassable){
						cout<<"ERROR IMPASSABLE";
					}
				}

			}*/
			return reconstrut_path_from_A_star_algorithm(come_from,current,from);
		} 
		open_nodes.erase(open_nodes.begin());
		closed_nodes.push_back(current);
		
		vector<pint> neighbor=map.neighbor(pint(current.first,current.second));
		for(vector<pint>::iterator ite=neighbor.begin();ite!=neighbor.end();ite++){
			if(find(closed_nodes.begin(),closed_nodes.end(),*ite)!=closed_nodes.end()){
				continue;
			}
			int temp_g_score=gscore[ite->second][ite->first]+1;
			int temp_f_score=heuristic_cost_estimate(pint(ite->first,ite->second),pint(to->pos_x,to->pos_y));
			if(find(open_nodes.begin(),open_nodes.end(),*ite)==open_nodes.end()){
				open_nodes.push_back(*ite);
			}
			else if(temp_g_score >= gscore[ite->second][ite->first]){
				continue;
			}
			//if(map.map[current.second][current.first].impassable) cout<<"ERROR IMPASABLE 4"<<endl;
			come_from[ite->second][ite->first]=current;
			gscore[ite->second][ite->first]=temp_g_score;
			fscore[ite->second][ite->first]=temp_g_score +temp_f_score;
		}
	}
	throw exception();
}
int Playable_Characters::reconstrut_path_from_A_star_algorithm(vector<vector<pint>> arg, pint current, Character* character){
	
	while(true){
		cout<<current.first<<"." <<current.second<<" ";

		current=arg[current.second][current.first];
		
		/*if(current.second==character->pos_y-1 && current.first==character->pos_x) cout<<endl;return 1;
		if(current.first==character->pos_x+1 && current.second==character->pos_y) cout<<endl;return 2;
		if(current.second==character->pos_y+1 && current.first==character->pos_x) cout<<endl;return 3;
		if(current.first==character->pos_x-1 && current.second==character->pos_y) cout<<endl;return 4;*/
		if(current.second==character->pos_y-1 && current.first==character->pos_x) {cout<<endl;return 1;}
		if(current.first==character->pos_x+1 && current.second==character->pos_y) {cout<<endl;return 2;}
		if(current.second==character->pos_y+1 && current.first==character->pos_x) {cout<<endl;return 3;}
		if(current.first==character->pos_x-1 && current.second==character->pos_y) {cout<<endl;return 4;}
		
	}
	cout<<endl;
	return 0;
}
