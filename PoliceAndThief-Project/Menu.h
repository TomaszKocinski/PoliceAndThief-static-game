#ifndef MENU_H
#define MENU_H

class Graphics;
#include <SDL.h>
#include <SDL_ttf.h>
enum CheckWinEnum;
class Menu
{
public:
	bool Continute;
	Menu(bool,CheckWinEnum);
	~Menu();
	int showmenu(Graphics &);
	void draw(Graphics &);
private:
	CheckWinEnum state;
	static const int NUMMENU = 6;
	static const char* labels[NUMMENU];
	SDL_Surface* menus[NUMMENU];
	SDL_Rect pos[NUMMENU];
	TTF_Font *font;
	SDL_Color color[NUMMENU];
	SDL_Color color_sel[NUMMENU];
};
#endif
