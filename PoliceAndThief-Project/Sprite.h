#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include <SDL.h>
#include "map.h"
using namespace std;
class Graphics;
class Sprite{
public:
	int _x,_y;
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, int posX, int posY);

	//virtual ~Sprite();
	//virtual void update();

	void draw(Graphics &graphics, int x, int y);
private:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;

};
class Character: public Sprite{
public:
	int pos_x, pos_y;
	Character();
	Character(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, int posX, int posY, int pos_x_arg, int pos_y_arg, MAP&);
	void move(int,MAP&);
};
#endif