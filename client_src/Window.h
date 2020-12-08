#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>
#include <exception>

class Window {
private:
	SDL_Window* window;
	int width;
	int height;
public:
	Window(const char* title, int height, int width);
	~Window();
	SDL_Renderer* getRenderer();
};

#define ERROR_BUF_LEN 256

class WindowConstructorError : public std::exception {
private:
	char error_msg[ERROR_BUF_LEN];
public:
	explicit WindowConstructorError(const char* sdl_error) noexcept;
	virtual const char* what() const noexcept;
	virtual ~WindowConstructorError() noexcept;
};

#endif
