#pragma once
#include "input.h"

void Input::beginNewFrame() {
	this->pressedKeys.clear();
	this->releasedKeys.clear();
}
void Input::keyDownEvent(const SDL_Event& event) {
	this->pressedKeys[event.key.keysym.scancode] = true;
}
void Input::keyUpEvent(const SDL_Event& event) {
	this->releasedKeys[event.key.keysym.scancode] = true;

}
bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->pressedKeys[key];
}

