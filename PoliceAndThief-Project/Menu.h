class Graphics;
#include <SDL.h>
#include <SDL_ttf.h>
class Menu
{
public:
	bool Continute;
	Menu(bool);
	~Menu();
	int showmenu(Graphics &);
	void draw(Graphics &);
private:
	static const int NUMMENU = 4;
	static const char* labels[NUMMENU];
	SDL_Surface* menus[NUMMENU];
	SDL_Rect pos[NUMMENU];
	TTF_Font *font;
	SDL_Color color[NUMMENU];
	SDL_Color color_sel[NUMMENU];
};

