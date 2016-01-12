#ifndef GAME_H
#define GAME_H

#include "Sprite.h"
#include "Playable_Characters.h"
class Graphics;

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	Sprite map;
	Playable_Characters PC;
};

#endif