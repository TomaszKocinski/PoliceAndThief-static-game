
#include <SDL.h>
#include <SDL_image.h>

#include "Graphics.h"


/* Graphics class
* Holds all information dealing with graphics for the game
*/

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(960, 720, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Police and Thief");
	SDL_RenderSetLogicalSize(_renderer,2560,1920);
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath){
	if(_spriteSheets.count(filePath)==0){
		_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return _spriteSheets[filePath];
}
void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle){
	SDL_RenderCopy(_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip(){
	SDL_RenderPresent(_renderer);
}

void Graphics::clear(){
	SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRender() const {
	return _renderer;
}