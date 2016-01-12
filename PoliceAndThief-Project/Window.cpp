
#include <SDL.h>

#include "window.h"


/* Graphics class
* Holds all information dealing with graphics for the game
*/

Window::Window() {
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Cavestory");
}

Window::~Window() {
	SDL_DestroyWindow(this->_window);
}