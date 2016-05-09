#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL_image.h>
#include <map>
#include <string>
struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics(int,int,double);
	~Graphics();

	SDL_Surface* loadImage(const std::string &filePath);

	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
	SDL_Texture* createTextureFromSurface(SDL_Surface *);
	void flip();
	void clear();
	SDL_Renderer* getRender() const;
	int width, height;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	double scale;
	
	std::map<std::string, SDL_Surface*> _spriteSheets;
	
	
};
#endif