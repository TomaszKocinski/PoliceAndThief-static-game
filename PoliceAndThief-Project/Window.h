#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;

class Window {
public:
	Window();
	~Window();
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};
#endif