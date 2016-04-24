#include "Menu.h"
#include "Graphics.h"
#include <SDL_ttf.h>
#include <iostream>
const char* Menu::labels[NUMMENU] = { "1: Continue", "2: New Game - as Police", "3: New Game - as Thief", "4: Exit" };
Menu::Menu(bool arg)
{
	Continute = arg;
	if (TTF_Init() != 0)
	{
		std::cout << "TTF_Init() Failed: " << TTF_GetError() << std::endl;
		SDL_Quit();
		exit(1);
	}

	SDL_Color colors[4] = { { 200, 200, 0 }, { 0, 0, 220 }, { 200, 0, 0 }, { 0, 200, 0 } };
	SDL_Color colors_sele[4] = { { 250, 250, 0 }, { 0, 0, 255 }, { 255, 0, 0 }, { 0, 255, 0 } };
	font = TTF_OpenFont("Verdana.ttf", 100);

	for (int i = 0; i < NUMMENU; i++){
		color[i] = colors[i];
		color_sel[i] = colors_sele[i];
		menus[i] = TTF_RenderText_Solid(font, labels[i], color[i]);
		pos[i].x = 100;
		pos[i].y = 200 * (i + 1);

	}
	if (!Continute) menus[0] = NULL;

}

Menu::~Menu()
{
}
int Menu::showmenu(Graphics &graphics){
	int x, y;
	bool selected[NUMMENU] = { 0, 0 };
	
	SDL_Event event;
	while (true)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < NUMMENU; i++){
					SDL_FreeSurface(menus[i]);
				}
				return 4;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < NUMMENU; i += 1) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = 1;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, labels[i], color_sel[i]);
						}
					}
					else
					{
						if (selected[i])
						{
							selected[i] = 0;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, labels[i], color[i]);
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < NUMMENU; i += 1) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						for (int j = 0; j < NUMMENU; j++){
							SDL_FreeSurface(menus[j]);
						}
						if (i == 4) return 5;
						else return (i+1);
					}
				}
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					for (int i = 0; i < NUMMENU; i++){
						SDL_FreeSurface(menus[i]);
					}
					return 4;
				}
				if (event.key.keysym.sym == SDLK_1 && Continute){
					return 1;
				}
				if (event.key.keysym.sym == SDLK_2){
					return 2;
				}
				if (event.key.keysym.sym == SDLK_3){
					return 3;
				}
				if (event.key.keysym.sym == SDLK_4){
					return 4;
				}
				if (event.key.keysym.sym == SDLK_5){
					return 0;
				}
			}
			draw(graphics);
		}
	}
	return 0;
}
void Menu::draw(Graphics &graphics){
	graphics.clear();
	for (int i = 0; i < NUMMENU; i++){
		SDL_Texture *texture = graphics.createTextureFromSurface(menus[i]);
		SDL_QueryTexture(texture, NULL, NULL, &pos[i].w, &pos[i].h);
		graphics.blitSurface(texture, NULL, &pos[i]);
		SDL_DestroyTexture(texture);
	}
	graphics.flip();
}