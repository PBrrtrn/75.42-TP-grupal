#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <yaml-cpp/yaml.h>
#include <SDL2/SDL.h>
#include <exception>

class Window {
private:
  SDL_Window* window;
  int width;
  int height;
public:
  Window(YAML::Node config);
  ~Window();
  Window(const Window&) = delete;            // Saco el constructor por copia
  Window& operator=(const Window&) = delete; // Saco la asignacion por copia
  int getWidth();
  int getHeight();
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
