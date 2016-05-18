#pragma once
#include "map.h"
#include "game.h"
#include "Graphics.h"
#include "input.h"
#include "Playable_Characters.h"
#include "Menu.h"
#include <string>
#include <iostream>
#include <sstream>
#include <SDL.h>
enum CheckWinEnum
{
	Nothing, winpolice, losepolice, winthief, losethief
};
Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init() Failed: " << TTF_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}
	this->gameLoop();

}

Game::~Game() {

}
void Game::initGUI(){
	font = TTF_OpenFont("Verdana.ttf", 100);
	SDL_Color colors[4] = { { 0, 0, 0 }, { 255, 150, 150 }, { 0, 0, 0 }, { 0, 0, 0 } };
	color[0] = colors[0];
	color[1] = colors[1];
	color[2] = colors[2];
	color[3] = colors[3];
	pos[0].x = 20;
	pos[0].y = 1780;
	pos[1].x = 520;
	pos[1].y = 1780;
	pos[2].x = 700;
	pos[2].y = 1780;
	pos[3].x = 1500;
	pos[3].y = 1780;
	GUIsurface[0] = TTF_RenderText_Solid(font, "Turns left:", color[0]);
	std::ostringstream ss;
	ss << turns;
	string str = ss.str();
	GUIsurface[1] = TTF_RenderText_Solid(font, str.c_str(), color[1]);
	GUIsurface[2] = TTF_RenderText_Solid(font, "Player to move: ", color[2]);
	GUIsurface[3] = TTF_RenderText_Solid(font, "placeholder", color[3]);

}
void Game::gameLoop() {
	Graphics graphics(960, 720, 2.66666);
	Input input;
	SDL_Event event;

	MAP* game_board = new MAP();
	map = Sprite(graphics, "images/map.png", 0, 0, 2560, 1920, 1, 1);
	directionarrows[0] = Sprite(graphics, "images/up.png", 0, 0, 56, 64, 1, 1);
	directionarrows[1] = Sprite(graphics, "images/right.png", 0, 0, 64, 56, 1, 1);
	directionarrows[2] = Sprite(graphics, "images/down.png", 0, 0, 56, 64, 1, 1);
	directionarrows[3] = Sprite(graphics, "images/left.png", 0, 0, 64, 56, 1, 1);
	Playable_Characters PC(graphics, game_board);

	turns = MAXTURNS;
	Character* character = PC.thief;
	bool change_character = false;
	bool Player_play_police;
	Menu* menu;
	int choice_from_menu;
	CheckWinEnum state = losepolice; // must be anything other than nothing to enter menu
	while (true) {
		if (state != Nothing){
			menu = new Menu(false, state);
			choice_from_menu = menu->showmenu(graphics);
			if (choice_from_menu == 0) return;
			else if (choice_from_menu == 2) {
				Player_play_police = true;
				game_board = new MAP();
				PC = Playable_Characters(graphics, game_board);
				character = PC.thief;
				change_character = true;
				turns = MAXTURNS + 1;
				state = Nothing;
			}
			else if (choice_from_menu == 3){
				Player_play_police = false;
				game_board = new MAP();
				PC = Playable_Characters(graphics, game_board);
				character = PC.thief;
				turns = MAXTURNS + 1;
				state = Nothing;
			}
			else 
				return;
			delete menu;
			initGUI();
			updateGUI(character, PC, *game_board);
		}
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
				}
			}


			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			menu = new Menu(true, Nothing);
			choice_from_menu = menu->showmenu(graphics);
			if (choice_from_menu == 0) return;
			if (choice_from_menu == 1) {

			}
			if (choice_from_menu == 2) {
				Player_play_police = true;
				game_board = new MAP();
				PC = Playable_Characters(graphics, game_board);
				character = PC.thief;
				change_character = true;
				turns = MAXTURNS + 1;
				update(character, PC, *game_board);
				state = Nothing;
			}
			if (choice_from_menu == 3){
				Player_play_police = false;
				game_board = new MAP();
				PC = Playable_Characters(graphics, game_board);
				character = PC.thief;
				turns = MAXTURNS + 1;
				update(character, PC, *game_board);
				state = Nothing;
			}
			if (choice_from_menu == 4) return;
			delete menu;
		}

		if (input.wasKeyPressed(SDL_SCANCODE_DOWN)){
			if (character->pos_y < game_board->max_y - 1){
				if (game_board->map[character->pos_y + 1][character->pos_x].accessable()){
					character->move(3, *game_board);
					change_character = true;
				}
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_RIGHT)){
			if (character->pos_x < game_board->max_x - 1){
				if (game_board->map[character->pos_y][character->pos_x + 1].accessable()){
					character->move(2, *game_board);
					change_character = true;
				}
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_UP)){
			if (character->pos_y > 0){
				if (game_board->map[character->pos_y - 1][character->pos_x].accessable()){
					character->move(1, *game_board);
					change_character = true;
				}
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_LEFT)){
			if (character->pos_x > 0){
				if (event.key.repeat == 0) {
					if (game_board->map[character->pos_y][character->pos_x - 1].accessable()){
						character->move(4, *game_board);
						change_character = true;
					}
				}
			}
		}
		if (change_character){
			
			if (state == Nothing) state = PC.checkwincondition(turns);
			if (!Player_play_police){
				PC.Automatic_move(true);
				state = PC.checkwincondition(turns);
				update(character, PC, *game_board);
			}
			else {
				if (character == PC.police2 || character==PC.thief) {
					if (state == Nothing)state = PC.checkwincondition(turns);
					PC.Automatic_move(false);
					update(character, PC, *game_board);
					if (state == Nothing)state = PC.checkwincondition(turns);
					character = PC.police;
				}
				else if (character == PC.police)
					character = PC.police2;
				updateGUI(character, PC, *game_board);

			}
			change_character = false;

		}
		draw(graphics, PC);
	}
}

void Game::draw(Graphics &graphics, Playable_Characters& PC) {
	graphics.clear();

	map.draw(graphics, 0, 0);
	if (directionarrowsshow[0]) directionarrows[0].draw(graphics, 2030, 1766);
	if (directionarrowsshow[1]) directionarrows[1].draw(graphics, 2080, 1810);
	if (directionarrowsshow[2]) directionarrows[2].draw(graphics, 2030, 1857);
	if (directionarrowsshow[3]) directionarrows[3].draw(graphics, 1971, 1810);
	PC.thief->draw(graphics, PC.thief->_x, PC.thief->_y);
	PC.police->draw(graphics, PC.police->_x, PC.police->_y);
	PC.police2->draw(graphics, PC.police2->_x, PC.police2->_y);

	for (int i = 0; i < NUMGUI; i++){
		SDL_Texture *texture = graphics.createTextureFromSurface(GUIsurface[i]);
		SDL_QueryTexture(texture, NULL, NULL, &pos[i].w, &pos[i].h);
		graphics.blitSurface(texture, NULL, &pos[i]);
		SDL_DestroyTexture(texture);
	}

	graphics.flip();
}

void Game::update(Character* arg, Playable_Characters& PC, MAP& map) {
	turns--;
	updateGUI(arg, PC, map);
}
void Game::updateGUI(Character* arg, Playable_Characters& PC, MAP& map) {

	std::ostringstream ss;
	ss << turns;
	string str = ss.str();
	if (turns > 85){
		color[1].b = 255;
		color[1].g = 255;
	}
	else{
		color[1].b = turns * 3;
		color[1].g = turns * 3;
	}
	GUIsurface[1] = TTF_RenderText_Solid(font, str.c_str(), color[1]);
	SDL_Color colors[3] = { { 0, 255, 0 }, { 0, 0, 255 }, { 255, 0, 0 } };
	if (arg == PC.thief)		 GUIsurface[3] = TTF_RenderText_Solid(font, "Thief", colors[0]);
	else if (arg == PC.police)	 GUIsurface[3] = TTF_RenderText_Solid(font, "Police", colors[1]);
	else						 GUIsurface[3] = TTF_RenderText_Solid(font, "Police 2", colors[2]);
	if (arg->pos_y > 0 && map.map[arg->pos_y - 1][arg->pos_x].accessable()){
		directionarrowsshow[0] = true;
	}
	else
	{
		directionarrowsshow[0] = false;
	}
	if (arg->pos_y < 20 - 1 && map.map[arg->pos_y + 1][arg->pos_x].accessable()){
		directionarrowsshow[2] = true;
	}
	else
	{
		directionarrowsshow[2] = false;
	}
	if (arg->pos_x < 29 - 1 && map.map[arg->pos_y][arg->pos_x + 1].accessable()){
		directionarrowsshow[1] = true;
	}
	else
	{
		directionarrowsshow[1] = false;
	}
	if (arg->pos_x > 0 && map.map[arg->pos_y][arg->pos_x - 1].accessable()){
		directionarrowsshow[3] = true;
	}
	else
	{
		directionarrowsshow[3] = false;
	}
}
