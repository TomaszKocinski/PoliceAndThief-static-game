#ifndef MAP_H
#define MAP_H
#include<array>
#include<vector>
using namespace std;
class element_of_map{
	public:
	bool impassable;
	bool busy;
	bool thief;
	bool police;

	bool Can_N;
	bool Can_E;
	bool Can_S;
	bool Can_W;

	element_of_map(bool N,bool E,bool S,bool W, bool arg_impassable){
		Can_N=N;
		Can_E=E;
		Can_S=S;
		Can_W=W;
		impassable =arg_impassable;
		busy=false;
	}
};

class MAP{
public: 
	const int max_x;
	const int max_y;
	int mov_x;
	int mov_y;
	std::vector<std::vector<element_of_map>> map;
	MAP():mov_x(88), mov_y(mov_x), max_x(29), max_y(19){
		map=std::vector<std::vector<element_of_map>>();
		vector<pair<int,int>> temp_of_grey=allocate_grey_vec();
		for(int i=0;i<max_y;i++){
			map.push_back(std::vector<element_of_map>());
			map.resize(max_y);
			for(int j=0;j<max_x;j++){	
				if((i%2==1) && (j%2==1))				map[i].push_back(element_of_map(false	,false	,false	,false	,true));
				else if(i==0 && j==0)					map[i].push_back(element_of_map(false	,true	,true	,false	,false));
				else if(i==0 && j==(max_x-1))			map[i].push_back(element_of_map(false	,false	,true	,true	,false));
				else if(i==(max_y-1) && j==0)			map[i].push_back(element_of_map(true	,false	,false	,false	,false));
				else if(i==(max_y-1) && j==(max_x-1))	map[i].push_back(element_of_map(true	,false	,false	,false	,false));
				else if(i==0 && j%2==0)					map[i].push_back(element_of_map(false	,true	,true	,true	,false));
				else if(i==0 && j%2==1)					map[i].push_back(element_of_map(false	,true	,false	,true	,false));
				else if(i==(max_y-1) && j%2==0)			map[i].push_back(element_of_map(true	,false	,false	,false	,false));
				else if(i==(max_y-1) && j%2==1)			map[i].push_back(element_of_map(true	,false	,false	,false	,false));
				else if(j==0 && i%2==0)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(j==0 && i%2==1)					map[i].push_back(element_of_map(true	,false	,true	,false	,false));
				else if(j==(max_x-1)&& i%2==0)			map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(j==(max_x-1)&& i%2==1)			map[i].push_back(element_of_map(true	,false	,true	,false	,false));

				else if(i==4 && j==14)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==4 && j==16)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==6 && j==4)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==6 && j==6)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==6 && j==8)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==6 && j==10)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==6 && j==20)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==6 && j==22)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==8 && j==10)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==8 && j==12)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==10 && j==14)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==10 && j==16)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==12 && j==20)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==12 && j==22)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==12 && j==4)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==12 && j==6)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==14 && j==12)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==14 && j==14)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==16 && j==4)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==16 && j==6)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==16 && j==22)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==16 && j==24)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));
				else if(i==18 && j==14)					map[i].push_back(element_of_map(true	,false	,true	,true	,false));
				else if(i==18 && j==16)					map[i].push_back(element_of_map(true	,true	,true	,false	,false));

				else if(j%2==1)							map[i].push_back(element_of_map(false	,true	,false	,true	,false));
				else if(i%2==1)							map[i].push_back(element_of_map(true	,false	,true	,false	,false));
				else									map[i].push_back(element_of_map(true	,true	,true	,true	,false));
			}
		}
		for each(pair<int,int> ele in temp_of_grey){
			map[ele.first][ele.second]=element_of_map(false	,false	,false	,false	,true);
		}
	}
	vector<pair<int,int>> neighbor(std::pair<int,int>& arg){
		vector<pair<int,int>> vec;
		if(arg.second>0 && !map[arg.second-1][arg.first].impassable){
			vec.push_back(pair<int,int>(arg.first,arg.second-1));
		}
		if(arg.second<max_y-1 && !map[arg.second+1][arg.first].impassable){
			vec.push_back(pair<int,int>(arg.first,arg.second+1));
		}
		if(arg.first<max_x-1 && !map[arg.second][arg.first+1].impassable){
			vec.push_back(pair<int,int>(arg.first+1,arg.second));
		}
		if(arg.first>0 && !map[arg.second][arg.first-1].impassable){
			vec.push_back(pair<int,int>(arg.first-1,arg.second));
		}
		return vec;
	}
	void switchBusy(pair<int,int>);
	vector<pair<int,int>> allocate_grey_vec();
};
#endif