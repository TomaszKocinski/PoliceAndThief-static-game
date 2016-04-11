#ifndef GAME_H
#define GAME_H

#include "Playable_Characters.h"
class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics,Playable_Characters&);
	void update(float elapsedTime);
	
	Sprite map;
	
};

#endif