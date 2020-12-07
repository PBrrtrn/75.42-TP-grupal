#include "Window.h"

Window::Window(const char* title, int width, int height) 
							: window(NULL), width(width), height(height) {
	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
																	SDL_WINDOWPOS_UNDEFINED, width,
																	height, SDL_WINDOW_SHOWN)
	if (this->window == NULL) throw 1; // TODO: Definir mejores errores
}

Window::~Window() {
	SDL_DestroyWindow(this->window);
}

SDL_Renderer* Window::createRenderer() {
	return SDL_CreateRenderer(this->window, -1, 
														SDL_RENDERER_ACCELERATED | 
														SDL_RENDERER_PRESENTVSYNC);
}
