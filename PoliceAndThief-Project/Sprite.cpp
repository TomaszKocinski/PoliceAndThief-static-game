#include "Sprite.h"
#include "Graphics.h"
#include <iostream>

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
Character::Character(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, int posX, int posY, int pos_x_arg, int pos_y_arg):
		Sprite(graphics,filePath,sourceX,sourceY,width,height,posX,posY),pos_x(pos_x_arg), pos_y(pos_y_arg){}