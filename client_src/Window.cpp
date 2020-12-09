#include "Window.h"

Window::Window(const char* title, int width, int height) 
							: window(NULL), width(width), height(height) {
	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
																	SDL_WINDOWPOS_UNDEFINED, width,
																	height, SDL_WINDOW_SHOWN);
	if (this->window == NULL) throw WindowConstructorError(SDL_GetError());
}

Window::~Window() {
	SDL_DestroyWindow(this->window);
}

SDL_Renderer* Window::getRenderer() {
	return SDL_CreateRenderer(this->window, -1, 
														SDL_RENDERER_ACCELERATED);
}

WindowConstructorError::WindowConstructorError
								(const char *sdl_error) noexcept {
	snprintf(this->error_msg, ERROR_BUF_LEN, 
					 "Failed to initialize SDL_Window: %s", sdl_error);
}

WindowConstructorError::~WindowConstructorError() noexcept { }

const char* WindowConstructorError::what() const noexcept {
	return this->error_msg;
}