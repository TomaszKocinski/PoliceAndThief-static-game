#pragma once
#include <SDL_image.h>
#include "Graphics.h"

#include <iostream>


Graphics::Graphics(int width_arg, int height_arg, double scale_arg) {
	this->height = height_arg;
	this->width = width_arg;
	this->scale = scale_arg;
	SDL_CreateWindowAndRenderer(width, height, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Policjanci i zlodzieje");
	SDL_RenderSetLogicalSize(_renderer, width*scale, height*scale);
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
SDL_Texture* Graphics::createTextureFromSurface(SDL_Surface* surface){
	return SDL_CreateTextureFromSurface(_renderer, surface);
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
