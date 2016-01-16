#pragma once
#include "map.h"
void MAP::switchBusy(pair<int,int> arg){
	if(map[arg.first][arg.second].busy){
		map[arg.first][arg.second].busy=false;
	}
	else{
		map[arg.first][arg.second].busy=true;
	}
}
vector<pair<int,int>> MAP::allocate_grey_vec(){
	vector<pair<int,int>> temp_of_grey;
	temp_of_grey.push_back(pair<int,int>(4,15));
	temp_of_grey.push_back(pair<int,int>(6,5));
	temp_of_grey.push_back(pair<int,int>(6,9));
	temp_of_grey.push_back(pair<int,int>(6,21));
	temp_of_grey.push_back(pair<int,int>(8,15));
	temp_of_grey.push_back(pair<int,int>(10,15));
	temp_of_grey.push_back(pair<int,int>(12,21));
	temp_of_grey.push_back(pair<int,int>(12,5));
	temp_of_grey.push_back(pair<int,int>(14,13));
	temp_of_grey.push_back(pair<int,int>(16,5));
	temp_of_grey.push_back(pair<int,int>(16,23));
	temp_of_grey.push_back(pair<int,int>(18,15));
	return temp_of_grey;
}