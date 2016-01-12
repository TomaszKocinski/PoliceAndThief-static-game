#include <SDL.h>
//#include <SDL_ttf.h>
#include "map.h"
#include "game.h"
#include "Graphics.h"
#include "input.h"
#include "Playable_Characters.h"
#include <algorithm>
#include <string>
#include <iostream>


Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;
	MAP game_board=MAP();
	map = Sprite(graphics, "images/map.png",0,0, 2560,1920,1,1);

	PC.thief = new Character(graphics, "images/thief.png",0,0, 40, 40,26,35,0,0);
	PC.police = new Character(graphics, "images/police.png",0,0, 40, 40,202,208,2,2);
	PC.police2 = new Character(graphics, "images/police2.png",0,0, 40, 40,386,400,4,4);
	Character* character=PC.thief;
	bool change_character=false;
	
	//Start the game loop
	while (true) {

		input.beginNewFrame();

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYUP) {
				if (event.key.repeat == 0) {
					input.keyUpEvent(event);
					
				}
			}
			else if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
					PC.distance();
				}
			}


			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		
		if(input.wasKeyPressed(SDL_SCANCODE_DOWN)){
			if(game_board.map[character->pos_y][character->pos_x].Can_S){

				if(character->pos_y>game_board.max_y-1);
				else{
					character->_y=character->_y+game_board.mov_y;
					character->pos_y++;
					change_character=true;
				}
			}
		}
		if(input.wasKeyPressed(SDL_SCANCODE_RIGHT)){

			if(game_board.map[character->pos_y][character->pos_x].Can_E){
				if(character->pos_x>game_board.max_x-1);
				else{
					character->_x=character->_x+game_board.mov_x;
					character->pos_x++;
					change_character=true;
				}
			}

		}
		if(input.wasKeyPressed(SDL_SCANCODE_UP)){
			if(game_board.map[character->pos_y][character->pos_x].Can_N){
				if(character->pos_y<0);
				else{
					character->_y=character->_y-game_board.mov_y;
					character->pos_y--;
					change_character=true;
				}
			}
		}
		if(input.wasKeyPressed(SDL_SCANCODE_LEFT)){

			if (event.key.repeat == 0) {
				if(game_board.map[character->pos_y][character->pos_x].Can_W){

					if(character->pos_x<0);
					else{
						character->_x=character->_x-game_board.mov_x;
						character->pos_x--;
						change_character=true;
					}
				}
			}
		}
		if(change_character){
			if(character==PC.thief) character=PC.police;
			else if(character==PC.police) character=PC.police2;
			else if(character==PC.police2) character=PC.thief;
			change_character=false;
		}
		draw(graphics);
	}
}

void Game::draw(Graphics &graphics) {
	graphics.clear();

	map.draw(graphics,0,0);
	PC.thief->draw(graphics,PC.thief->_x,PC.thief->_y);
	PC.police->draw(graphics,PC.police->_x,PC.police->_y);
	PC.police2->draw(graphics,PC.police2->_x,PC.police2->_y);
	graphics.flip();
}

void Game::update(float elapsedTime) {

}