#ifndef GAME_H
#define GAME_H

class Window;

class Game {
public:
	Game();
	~Game();
private:
	void gameLoop();
	void draw(Window &window);
	void update(float elapsedTime);
};

#endif