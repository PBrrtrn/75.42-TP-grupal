#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>

class Window {
private:
	SDL_Window* window;
	int height;
	int width;
public:
	Window(const char* title, int height, int width);
	~Window();
	SDL_Renderer* getRenderer();
};

#endif
