#include "Sprite.h"
#include "Graphics.h"
#include <iostream>
#include <vector>
#include <random>
#include "map.h"
using namespace std;
Sprite::Sprite(){}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, int posX, int posY):_x(posX),_y(posY)
{
	_sourceRect.x=sourceX;
	_sourceRect.y = sourceY;
	_sourceRect.h = height;
	_sourceRect.w = width;

	_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRender(), graphics.loadImage(filePath));
	if(_spriteSheet== NULL){
		std::cout << "\n Error: unable to load image \n";
	}

}

void Sprite::draw(Graphics &Graphics, int x, int y) {
	SDL_Rect destinationRectangle={x,y, _sourceRect.w, _sourceRect.h};
	Graphics.blitSurface(_spriteSheet, &_sourceRect, &destinationRectangle);
}

Character::Character(){}
Character::Character(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, int posX, int posY, int pos_x_arg, int pos_y_arg, MAP& map):
Sprite(graphics,filePath,sourceX,sourceY,width,height,posX,posY),pos_x(pos_x_arg), pos_y(pos_y_arg){

	vector<vector<bool>> temp_vec;
	for(int i=0;i<map.max_y;i++){
		temp_vec.push_back(vector<bool>());
		for(int j=0;j<map.max_x;j++){
			if(map.map[i][j].busy && map.map[i][j].impassable)
				temp_vec[i].push_back(false);
			temp_vec[i].push_back(true);
		}
	}
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> d(0, map.max_x-1);
	int y=d(gen)%(map.max_y-1),x=d(gen);
    while(map.map[y][x].busy || map.map[y][x].impassable){
		y=d(gen)%(map.max_y-1);
		x=d(gen);
	}
	map.map[y][x].busy=true;
	pos_x=x;
	pos_y=y;
	_x=posX+x*map.mov_x;
	_y=posY+y*map.mov_y;
}
void Character::move(int where_move,MAP map){
	int mov=88;
	if(where_move==1) {
		if(map.map[pos_y-1][pos_x].impassable) cout<<"ERROR IMPASSABLE 3 N"<<endl;
		_y-=mov;
		pos_y--;
	}
	if(where_move==2) {
		if(map.map[pos_y][pos_x+1].impassable) cout<<"ERROR IMPASSABLE 3 E"<<endl;
		_x+=mov;
		pos_x++;
	}
	if(where_move==3) {
		if(map.map[pos_y+1][pos_x].impassable) cout<<"ERROR IMPASSABLE 3 S"<<endl;
		_y+=mov;
		pos_y++;
	}
	if(where_move==4) {
		if(map.map[pos_y][pos_x-1].impassable) cout<<"ERROR IMPASSABLE 3 W"<<endl;
		_x-=mov;
		pos_x--;
	}

}