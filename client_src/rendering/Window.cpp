#include "Window.h"

Window::Window(YAML::Node config) : 
	window(NULL), 
	width(config["width"].as<int>()), 
	height(config["height"].as<int>()),
	fullscreen(false) 
	{
  	this->window = SDL_CreateWindow(config["title"].as<std::string>().c_str(), 
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, 
                                  this->width, this->height,
                                  SDL_WINDOW_SHOWN);
  	if (this->window == NULL) throw WindowConstructorError(SDL_GetError());
}

Window::~Window() {
  SDL_DestroyWindow(this->window);
}

void Window::toggleFullScreen() {
	if (this->fullscreen) {
		SDL_RestoreWindow(this->window);
		this->fullscreen = false;
	} else {
  		SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN);
		this->fullscreen = true;
	}
}

int Window::getWidth() {
  return this->width;
}

int Window::getHeight() {
  return this->height;
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