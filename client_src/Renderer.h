#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL.h>

#include "Thread.h"
#include "GameStatusMonitor.h"
#include "Window.h"

enum Event { START, QUIT, CONTINUE };

class Renderer : public Thread {
private:
  SDL_Renderer* renderer;
  Window window;
  GameStatusMonitor& game_status_monitor;
public:
  Renderer(const char *title, int width, int height, 
           GameStatusMonitor& status_monitor);
  ~Renderer();
  void run();
};

#define ERROR_BUF_LEN 256

class RendererConstructorError : public std::exception {
private:
  char error_msg[ERROR_BUF_LEN];
public:
  explicit RendererConstructorError(const char* sdl_error) noexcept;
  virtual const char* what() const noexcept;
  virtual ~RendererConstructorError() noexcept;
};

#endif
