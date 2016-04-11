#include <SDL.h>
//#include <SDL_ttf.h>
#include "map.h"
#include "game.h"
#include "Graphics.h"
#include "input.h"
#include "Playable_Characters.h"
#include "Menu.h"
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
	Graphics graphics(960, 720, 2.66666);
	Input input;
	SDL_Event event;

	MAP game_board = MAP();
	map = Sprite(graphics, "images/map.png", 0, 0, 2560, 1920, 1, 1);
	Playable_Characters PC(graphics, game_board);

	Character* character = PC.thief;
	bool change_character = false;
	bool Player_play_police;
	Menu* menu = new Menu();
	int choice_from_menu = menu->showmenu(graphics);
	if (choice_from_menu == 0) return;
	if (choice_from_menu == 1) {
		
	}
	if (choice_from_menu == 2) {
		Player_play_police = true;
		character = PC.police;
	}
	if (choice_from_menu == 3){
		Player_play_police = false;
		
	}
	if (choice_from_menu == 4) return;
	delete menu;

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
				}
			}


			else if (event.type == SDL_QUIT) {
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			menu = new Menu();
			choice_from_menu = menu->showmenu(graphics);
			if (choice_from_menu == 0) return;
			if (choice_from_menu == 1) {

			}
			if (choice_from_menu == 2) {
				Player_play_police = true;
				game_board = MAP();
				PC = Playable_Characters(graphics, game_board);
				character = PC.police;
			}
			if (choice_from_menu == 3){
				Player_play_police = false;
				game_board = MAP();
				PC = Playable_Characters(graphics, game_board);
				character = PC.thief;
			}
			if (choice_from_menu == 4) return;
			delete menu;
		}

		if (input.wasKeyPressed(SDL_SCANCODE_DOWN)){
			if (character->pos_y < game_board.max_y - 1){
				if (game_board.map[character->pos_y + 1][character->pos_x].accessable()){

					character->move(3, game_board);

					change_character = true;
				}
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_RIGHT)){
			if (character->pos_x < game_board.max_x - 1){
				if (game_board.map[character->pos_y][character->pos_x + 1].accessable()){
					character->move(2, game_board);
					change_character = true;
				}
			}

		}
		if (input.wasKeyPressed(SDL_SCANCODE_UP)){
			if (character->pos_y > 0){
				if (game_board.map[character->pos_y - 1][character->pos_x].accessable()){


					character->move(1, game_board);

					change_character = true;
				}
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_LEFT)){
			if (character->pos_x > 0){
				if (event.key.repeat == 0) {
					if (game_board.map[character->pos_y][character->pos_x - 1].accessable()){

						character->move(4, game_board);

						change_character = true;
					}
				}
			}
		}
		if (change_character){
			if (!Player_play_police){
				PC.Automatic_move(game_board, true);
			}
			else {
				PC.Automatic_move(game_board, false);
				if (character == PC.police)
					character = PC.police2;
				else
				character = PC.police;
			}
			change_character = false;
		}
		draw(graphics, PC);
	}
}

void Game::draw(Graphics &graphics, Playable_Characters& PC) {
	graphics.clear();

	map.draw(graphics, 0, 0);
	PC.thief->draw(graphics, PC.thief->_x, PC.thief->_y);
	PC.police->draw(graphics, PC.police->_x, PC.police->_y);
	PC.police2->draw(graphics, PC.police2->_x, PC.police2->_y);

	graphics.flip();
}

void Game::update(float elapsedTime) {

}
