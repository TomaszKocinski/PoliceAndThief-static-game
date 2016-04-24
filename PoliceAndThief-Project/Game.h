#ifndef GAME_H
#define GAME_H
#include <SDL_ttf.h>
#include "Playable_Characters.h"
class Graphics;
class Character;
int isNeighbor(pair<int, int> floatingcharacter, pair<int, int> centercharacter);
enum CheckWinEnum
{
	Nothing, winpolice, losepolice, winthief, losethief
};
class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics,Playable_Characters&);
	void update(Character* arg, Playable_Characters& PC, MAP& map);
	void updateGUI(Character* arg, Playable_Characters& PC, MAP& map);
	CheckWinEnum checkwinconditionPolice(Playable_Characters&);
	CheckWinEnum checkwinconditionThief(Playable_Characters&);
	
	void initGUI();
	Sprite map;
	Sprite directionarrows[4];
	bool directionarrowsshow[4];

	static const int MAXTURNS = 85; // maks 255/3=85
	int turns;

	static const int NUMGUI = 4;
	SDL_Surface* GUIsurface[NUMGUI];
	SDL_Rect pos[NUMGUI];
	SDL_Color color[NUMGUI];
	TTF_Font *font;
	};

#endif